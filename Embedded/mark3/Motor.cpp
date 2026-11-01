#include "Motor.h"

/**
   @brief initialize Motor with Moteus and position command in pure velocity mode
   @param motor a Moteus motor controller
   @param motorCommand a position command to send to the Moteus
*/
Motor::Motor(Moteus *motor, PositionCommand *motorCommand) {
   this->motor = motor;
   this->motorCommand = motorCommand;
   
   this->motorCommand->position = VELOCITY_MODE;
   this->motorCommand->velocity = 0.0f;
}

void Motor::setStop() {
   motor->SetStop();
}

void Motor::setVelocity(float vel) {
   motorCommand->velocity = vel;
}

void Motor::sendCommand() {
   motor->SetPosition(*motorCommand);
}
