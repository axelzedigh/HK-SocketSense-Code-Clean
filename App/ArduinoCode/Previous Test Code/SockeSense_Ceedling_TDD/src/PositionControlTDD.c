// PositionControlTDD.h
#include "arduino.h"
#include "HX711.h"

void motorPositionRead(double motor_position_sensor[6]) {
  motor_position_sensor[0] = analogRead(A1);
  motor_position_sensor[1] = analogRead(A2);
  motor_position_sensor[2] = analogRead(A3);
  motor_position_sensor[3] = analogRead(A4);
  motor_position_sensor[4] = analogRead(A5);
  motor_position_sensor[5] = analogRead(A6);
}

void forceSensorRead() {
  force_sensor[0] = scale1.get_units();
  force_sensor[1] = scale2.get_units();
  force_sensor[2] = scale3.get_units();
  force_sensor[3] = scale4.get_units();
  force_sensor[4] = scale5.get_units();
  force_sensor[5] = scale6.get_units();
}
