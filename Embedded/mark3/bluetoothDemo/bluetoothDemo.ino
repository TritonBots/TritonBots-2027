/**
 * @file bluetoothDemo.ino
 * @brief Bluetooth Low Energy (BLE) Holonomic 4-Wheel Drive Controller for TritonBots
 * 
 * Controls the 4 omniwheel drive motors (Front-Left, Front-Right, Back-Right, Back-Left)
 * using an Arduino UNO R4 WiFi and MCP2517FD CAN-FD controller with Moteus motor drivers.
 * No dribbler and no kicker actuators are energized.
 * 
 * Target Board: Arduino UNO R4 WiFi
 * Libraries Required: ArduinoBLE, ACAN2517FD, Moteus
 */

#include <ArduinoBLE.h>
#include <MoteusAcan2517fd.h>
#include <cmath>
#include <cstdlib>

// =============================================================================
// Pin Definitions & Hardware Configuration
// =============================================================================
static const byte MCP2517_CS  = 9;  // CAN-FD Controller Chip Select
static const byte MCP2517_INT = 7;  // CAN-FD Controller Interrupt

// Motor CAN IDs (Wheel motors only)
static const uint8_t FL_MOTOR_ID = 1; // Front-Left
static const uint8_t FR_MOTOR_ID = 2; // Front-Right
static const uint8_t BR_MOTOR_ID = 3; // Back-Right
static const uint8_t BL_MOTOR_ID = 4; // Back-Left
static const uint8_t NUM_WHEELS  = 4;

// 4-Wheel Omnidirectional Angles in Radians (~20 deg and ~60 deg offsets)
static const float WHEEL_ANGLES[NUM_WHEELS] = {
    0.349066f,  // Front-Left (~20 deg)
   -0.349066f,  // Front-Right (~-20 deg)
    1.0472f,    // Back-Right (~60 deg)
   -1.0472f     // Back-Left (~-60 deg)
};

// Maximum velocity limits (in motor revolutions per second - RPS)
static const float MAX_LINEAR_RPS    = 25.0f; // Max translation velocity in RPS
static const float MAX_ROTATION_RPS  = 15.0f; // Max rotational velocity in RPS

// Safety Watchdog: Auto-stop motors if no valid command received within this window
static const unsigned long WATCHDOG_TIMEOUT_MS = 500;

// =============================================================================
// BLE Service & Characteristic Definitions
// =============================================================================
// Custom 128-bit UUIDs for TritonBots Demo Control
static const char* BLE_SERVICE_UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";
static const char* BLE_CHAR_UUID    = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService driveService(BLE_SERVICE_UUID);
// Characteristic accepts up to 32-byte ASCII string commands (e.g. "V vx vy omega")
BLECharacteristic driveCharacteristic(
    BLE_CHAR_UUID,
    BLEWrite | BLEWriteWithoutResponse,
    32
);

// =============================================================================
// Hardware Drivers & Moteus Instances
// =============================================================================
ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);

static Moteus moteus1(can, []() {
    Moteus::Options options;
    options.id = FL_MOTOR_ID;
    return options;
}());

static Moteus moteus2(can, []() {
    Moteus::Options options;
    options.id = FR_MOTOR_ID;
    return options;
}());

static Moteus moteus3(can, []() {
    Moteus::Options options;
    options.id = BR_MOTOR_ID;
    return options;
}());

static Moteus moteus4(can, []() {
    Moteus::Options options;
    options.id = BL_MOTOR_ID;
    return options;
}());

static Moteus* motors[NUM_WHEELS] = {
    &moteus1,
    &moteus2,
    &moteus3,
    &moteus4
};

static Moteus::PositionMode::Command motorCmds[NUM_WHEELS];

// State Variables
static unsigned long lastPacketTime = 0;
static unsigned long lastControlLoopTime = 0;
static unsigned long lastTelemetryLogTime = 0;
static bool isWatchdogStopped = true;
static bool motorsCurrentlyStopped = true;

// Commanded Cartesian velocities (normalized from -100.0 to 100.0)
static float cmdVx = 0.0f;    // Forward (+) / Backward (-)
static float cmdVy = 0.0f;    // Strafe Left (+) / Strafe Right (-)
static float cmdOmega = 0.0f; // Rotate CCW (+) / Rotate CW (-)

// =============================================================================
// Motor Control Functions
// =============================================================================

/**
 * @brief Immediately de-energizes all 4 wheel motors using SetStop() and clears setpoints.
 *        In SetStop mode, the motor coils are unpowered so wheels spin freely by hand.
 */
void stopAllMotors() {
    for (int i = 0; i < NUM_WHEELS; i++) {
        motorCmds[i].velocity = 0.0f;
        motors[i]->SetStop();
    }
    cmdVx = 0.0f;
    cmdVy = 0.0f;
    cmdOmega = 0.0f;
    isWatchdogStopped = true;
    motorsCurrentlyStopped = true;
}

/**
 * @brief Computes individual wheel velocities from holonomic (Vx, Vy, Omega) setpoints
 *        and transmits CAN-FD velocity frames to the Moteus controllers.
 *        When stopped or idle, motors remain in SetStop mode (unpowered, no stiffness).
 */
void updateWheelKinematics() {
    bool inputIsZero = (fabs(cmdVx) < 0.01f && fabs(cmdVy) < 0.01f && fabs(cmdOmega) < 0.01f);

    // If watchdog tripped or user commanded zero movement, ensure motors are cleanly stopped
    if (isWatchdogStopped || inputIsZero) {
        if (!motorsCurrentlyStopped) {
            for (int i = 0; i < NUM_WHEELS; i++) {
                motorCmds[i].velocity = 0.0f;
                motors[i]->SetStop();
            }
            motorsCurrentlyStopped = true;
        }
        return;
    }

    // Active movement commanded: mark motors as energized
    motorsCurrentlyStopped = false;

    // Convert linear inputs (-100 to 100) into physical RPS
    float vxRPS = (cmdVx / 100.0f) * MAX_LINEAR_RPS;
    float vyRPS = (cmdVy / 100.0f) * MAX_LINEAR_RPS;

    // Rotational speed in RPS (+Omega = CCW, -Omega = CW)
    float omegaRPS = (cmdOmega / 100.0f) * MAX_ROTATION_RPS;

    float cosF = cosf(WHEEL_ANGLES[0]); // Front-Left / Front-Right (~20 deg)
    float sinF = sinf(WHEEL_ANGLES[0]);
    float cosB = cosf(WHEEL_ANGLES[2]); // Back-Right / Back-Left (~60 deg)
    float sinB = sinf(WHEEL_ANGLES[2]);

    // Apply omnidirectional kinematics for each wheel:
    // Left side (FL, BL) has opposite polarity from Right side (FR, BR) to produce forward drive.
    // All 4 motors receive +omegaRPS for CCW rotation, -omegaRPS for CW rotation.
    float wheelVels[NUM_WHEELS];
    wheelVels[0] = -vxRPS * cosF + vyRPS * sinF + omegaRPS; // Motor 1: Front-Left (FL)
    wheelVels[1] =  vxRPS * cosF + vyRPS * sinF + omegaRPS; // Motor 2: Front-Right (FR)
    wheelVels[2] =  vxRPS * cosB - vyRPS * sinB + omegaRPS; // Motor 3: Back-Right (BR)
    wheelVels[3] = -vxRPS * cosB - vyRPS * sinB + omegaRPS; // Motor 4: Back-Left (BL)

    // Clamp to maximum allowable motor RPS and transmit to Moteus
    const float maxTotalRPS = MAX_LINEAR_RPS + MAX_ROTATION_RPS;
    for (int i = 0; i < NUM_WHEELS; i++) {
        if (wheelVels[i] > maxTotalRPS) {
            wheelVels[i] = maxTotalRPS;
        } else if (wheelVels[i] < -maxTotalRPS) {
            wheelVels[i] = -maxTotalRPS;
        }

        motorCmds[i].position = NAN; // Pure velocity mode
        motorCmds[i].velocity = wheelVels[i];
        motors[i]->SetPosition(motorCmds[i]);
    }
}

// =============================================================================
// BLE Packet Parser
// =============================================================================

/**
 * @brief Parses incoming BLE commands.
 *        Supported formats:
 *          "V <vx> <vy> <omega>"  -> Holonomic velocity setpoint (-100 to 100)
 *          "S"                    -> Emergency Stop
 * 
 * Uses strtof instead of sscanf to guarantee 100% reliable float parsing on
 * ARM Cortex-M newlib-nano (which disables float sscanf by default).
 */
void handleBlePacket(const char* packet) {
    if (packet == nullptr) {
        return;
    }

    // Skip leading whitespace or newlines
    while (*packet == ' ' || *packet == '\t' || *packet == '\r' || *packet == '\n') {
        packet++;
    }
    if (*packet == '\0') {
        return;
    }

    if (*packet == 'V' || *packet == 'v') {
        const char* p = packet + 1;
        char* endPtr = nullptr;

        // Parse Vx
        float vx = strtof(p, &endPtr);
        if (endPtr == p) {
            return; // Failed to parse vx
        }
        p = endPtr;

        // Parse Vy
        float vy = strtof(p, &endPtr);
        if (endPtr == p) {
            return; // Failed to parse vy
        }
        p = endPtr;

        // Parse Omega (optional, defaults to 0.0)
        float omega = strtof(p, &endPtr);
        if (endPtr == p) {
            omega = 0.0f;
        }

        cmdVx = constrain(vx, -100.0f, 100.0f);
        cmdVy = constrain(vy, -100.0f, 100.0f);
        cmdOmega = constrain(omega, -100.0f, 100.0f);
        lastPacketTime = millis();
        isWatchdogStopped = false;

    } else if (*packet == 'S' || *packet == 's') {
        stopAllMotors();
        lastPacketTime = millis();
        Serial.println(F("[BLE] Emergency stop command received."));
    }
}

// =============================================================================
// Setup
// =============================================================================
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(115200);
    // Allow up to 2 seconds for USB serial monitor connection if attached
    while (!Serial && millis() < 2000);

    Serial.println(F("========================================"));
    Serial.println(F("TritonBots BLE 4-Wheel Controller Demo"));
    Serial.println(F("Target: Wheel Motors Only (No Kicker/Dribbler)"));
    Serial.println(F("========================================"));

    // Initialize SPI and CAN-FD Driver
    SPI.begin();

    ACAN2517FDSettings settings(
        ACAN2517FDSettings::OSC_20MHz,
        1000ll * 1000ll,
        DataBitRateFactor::x1
    );
    settings.mArbitrationSJW = 2;
    settings.mDriverTransmitFIFOSize = 4;
    settings.mDriverReceiveFIFOSize = 4;

    const uint32_t errorCode = can.begin(settings, [] { can.isr(); });
    while (errorCode != 0) {
        Serial.print(F("CAN-FD Init Error: 0x"));
        Serial.println(errorCode, HEX);
        delay(1000);
    }
    Serial.println(F("CAN-FD bus initialized successfully."));

    // Ping all 4 wheel motors over CAN-FD and verify communication
    Serial.println(F("Pinging wheel motors over CAN-FD:"));
    for (int i = 0; i < NUM_WHEELS; i++) {
        motorCmds[i].position = NAN;
        motorCmds[i].velocity = 0.0f;
        bool motorResponded = motors[i]->SetStop();
        Serial.print(F("  Motor [ID "));
        Serial.print(i + 1);
        Serial.print(F("]: "));
        if (motorResponded) {
            Serial.print(F("ONLINE (Moteus Mode: "));
            Serial.print(static_cast<int>(motors[i]->last_result().values.mode));
            Serial.println(F(")"));
        } else {
            Serial.println(F("OFFLINE / NO RESPONSE (Check ID and CAN bus)"));
        }
    }
    motorsCurrentlyStopped = true;
    isWatchdogStopped = true;

    // Initialize BLE
    if (!BLE.begin()) {
        Serial.println(F("CRITICAL ERROR: Failed to initialize ArduinoBLE!"));
        while (1) {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            delay(200);
        }
    }

    BLE.setLocalName("TritonBot-Demo");
    BLE.setAdvertisedService(driveService);

    driveService.addCharacteristic(driveCharacteristic);
    BLE.addService(driveService);

    BLE.advertise();
    Serial.println(F("Bluetooth LE advertising started: 'TritonBot-Demo'"));
    Serial.println(F("Waiting for PS4 Controller Python bridge to connect..."));
}

// =============================================================================
// Main Loop
// =============================================================================
void loop() {
    BLE.poll();
    BLEDevice central = BLE.central();

    if (central) {
        digitalWrite(LED_BUILTIN, HIGH); // LED solid on when connected
        Serial.print(F("Central connected: "));
        Serial.println(central.address());

        while (central.connected()) {
            BLE.poll();

            // 1. Process incoming BLE packets
            if (driveCharacteristic.written()) {
                char buffer[33] = {0};
                int bytesRead = driveCharacteristic.readValue(buffer, sizeof(buffer) - 1);
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    handleBlePacket(buffer);
                }
            }

            // 2. Safety Watchdog Check
            if (!isWatchdogStopped && (millis() - lastPacketTime > WATCHDOG_TIMEOUT_MS)) {
                Serial.println(F("[SAFETY] Watchdog timeout: No BLE command received within 500ms. Stopping motors."));
                stopAllMotors();
            }

            // 3. Periodic Kinematic Motor Update (~50 Hz / every 20ms)
            unsigned long now = millis();
            if (now - lastControlLoopTime >= 20) {
                lastControlLoopTime = now;
                updateWheelKinematics();
            }

            // 4. Periodic Telemetry Logging (~1 Hz while moving)
            if (!motorsCurrentlyStopped && (now - lastTelemetryLogTime >= 1000)) {
                lastTelemetryLogTime = now;
                Serial.print(F("[DRIVE] Vx: "));
                Serial.print(cmdVx, 1);
                Serial.print(F(" | Vy: "));
                Serial.print(cmdVy, 1);
                Serial.print(F(" | Omega: "));
                Serial.print(cmdOmega, 1);
                Serial.print(F(" | FL: "));
                Serial.print(motorCmds[0].velocity, 1);
                Serial.print(F(" FR: "));
                Serial.print(motorCmds[1].velocity, 1);
                Serial.print(F(" BR: "));
                Serial.print(motorCmds[2].velocity, 1);
                Serial.print(F(" BL: "));
                Serial.println(motorCmds[3].velocity, 1);
            }
        }

        // Central disconnected
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println(F("Central disconnected. Emergency stopping motors."));
        stopAllMotors();
    } else {
        // Not connected: ensure motors stay stopped
        if (!motorsCurrentlyStopped) {
            stopAllMotors();
        }
    }
}
