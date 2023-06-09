#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP_FlexyStepper.h>

// IO pin assignments
const int MOTOR_STEP_PIN = 26;
const int MOTOR_DIRECTION_PIN = 27;
const int MOTOR2_STEP_PIN = 16;
const int MOTOR2_DIRECTION_PIN = 17;

// create the stepper motor object
ESP_FlexyStepper Motor;
ESP_FlexyStepper Motor2;

void setup() 
{
  Serial.begin(115200);
  long valor = 2000;
  // connect and configure the stepper motor to its IO pins
  Motor.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  Motor2.connectToPins(MOTOR2_STEP_PIN, MOTOR2_DIRECTION_PIN);
  
  Motor.setSpeedInStepsPerSecond(valor);
  Motor.setAccelerationInStepsPerSecondPerSecond(valor);
  Motor.setDecelerationInStepsPerSecondPerSecond(valor);

  Motor2.setSpeedInStepsPerSecond(valor);
  Motor2.setAccelerationInStepsPerSecondPerSecond(valor);
  Motor2.setDecelerationInStepsPerSecondPerSecond(valor);
  
}

void loop() 
{
  Motor.moveRelativeInSteps(20000);
 // Motor2.moveRelativeInSteps(20000);
  delay(2000);
  //Motor.moveRelativeInSteps(-20000);
 // Motor2.moveRelativeInSteps(-20000);
  //delay(2000);


}
