#include <Arduino.h>

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Dwenguino.h>
#include <DwenguinoMotor.h> // the motor library

DCMotor dcMotor1(MOTOR_1_0, MOTOR_1_1);

void setup() {
  initDwenguino();
}

void loop() {
  // put your main code here, to run repeatedly:
  //dcMotor1.setSpeed(100);
  //delay(2500);
  //dcMotor1.setSpeed(-100);
  //delay(2500);


}
