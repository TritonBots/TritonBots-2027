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