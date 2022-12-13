#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP_FlexyStepper.h>

// IO pin assignments
/*
const int MOTOR_STEP_PIN = 26;
const int MOTOR_DIRECTION_PIN = 27;
const int MOTOR2_STEP_PIN = 16;
const int MOTOR2_DIRECTION_PIN = 17;
*/
// create the stepper motor object
ESP_FlexyStepper Motor;

void beginMotor(const int MOTOR_STEP_PIN, const int MOTOR_DIRECTION_PIN)
{
    long valor = 2000;
    // connect and configure the stepper motor to its IO pins
    Motor.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

    Motor.setSpeedInStepsPerSecond(valor);
    Motor.setAccelerationInStepsPerSecondPerSecond(valor);
    Motor.setDecelerationInStepsPerSecondPerSecond(valor);
    
}

void giro_direita()
{
    Motor.moveRelativeInSteps(500);
    
}

void giro_esquerda()
{
    Motor.moveRelativeInSteps(-500);
   
}
