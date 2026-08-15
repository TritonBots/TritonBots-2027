#include "Motor.h"

/**
   @brief initialize Motor with Moteus and position command
   @param motor a Moteus motor controller
   @param motorCommand a position command to send to the Moteus
*/
Motor::Motor(Moteus *motor, PositionCommand *motorCommand) {
   this->motor = motor;
   this->motorCommand = motorCommand;
}

void Motor::setStop() {
   motor->SetStop();
}