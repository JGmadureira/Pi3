#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP_FlexyStepper.h>
#include "Sensor.h"

// create the stepper motor object
ESP_FlexyStepper Motor_ETQ;
ESP_FlexyStepper Motor_CART;  
long PassosMotorETQ = 0;
long PassosMotorCART = 0;

// IO pin assignments
const int LIMIT_SWITCH_PIN_ETQ = 15;  
const int LIMIT_SWITCH_PIN_CART = 23;

//variables for software debouncing of the limit switches
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100; //the minimum delay in milliseconds to check for bouncing of the switch. Increase this slighlty if you switches tend to bounce a lot
byte limitSwitchState_ETQ = 0;
byte limitSwitchState_CART = 0;
byte oldConfirmedLimitSwitchState = 0;


///////////////////////////////////////////////////
        /* ++++  I M P O R T A N T E  ++++  
                  núcleos separados
    Motor_CART.startAsService(int coreNumber) */

//////////////////////////////////////////////////

void limitSwitchHandler_ETQ()
{
  limitSwitchState_ETQ = digitalRead(LIMIT_SWITCH_PIN_ETQ);
  //lastDebounceTime = millis();
}

void limitSwitchHandler_CART()
{
  limitSwitchState_CART = digitalRead(LIMIT_SWITCH_PIN_CART);
  //lastDebounceTime = millis();
}

void configMotores(){
    // connect and configure the stepper motor to its IO pins
    //Motor_CART.startAsService(1); // LIMIT_SWITCH_BEGIN
   // Motor_ETQ.startAsService(1); // LIMIT_SWITCH_BEGIN

    Motor_CART.connectToPins(26, 27);
    Motor_ETQ.connectToPins(16, 17);
    limitSwitchHandler_ETQ();
    limitSwitchHandler_CART();
    pinMode(LIMIT_SWITCH_PIN_ETQ, INPUT_PULLUP);
    pinMode(LIMIT_SWITCH_PIN_CART, INPUT_PULLUP);

    //attach an interrupt to the IO pin of the limit switch and specify the handler function
    attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_PIN_ETQ), limitSwitchHandler_ETQ, CHANGE);
    attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_PIN_CART), limitSwitchHandler_CART, CHANGE);
   
    
}

void MotorETQ(float vel, long Passos, float acel, float deacel ){
    
    Motor_ETQ.setSpeedInStepsPerSecond(vel); 
    Motor_ETQ.setAccelerationInStepsPerSecondPerSecond(acel);
    Motor_ETQ.setDecelerationInStepsPerSecondPerSecond(deacel);
    Motor_ETQ.setTargetPositionInSteps(Passos); //cofigura a quantidade de passos para o motor  
    Motor_ETQ.processMovement(); //realiza o movimento até o valor do setTarget
    
}

void MotorCART(float vel, long Passos, float acel, float deacel ){

    Motor_CART.setSpeedInStepsPerSecond(vel);
    Motor_CART.setAccelerationInStepsPerSecondPerSecond(acel);
    Motor_CART.setDecelerationInStepsPerSecondPerSecond(deacel);
    Motor_CART.setTargetPositionInSteps(Passos);  //cofigura a quantidade de passos para o motor 
    //Motor_CART.moveRelativeInSteps(Passos);  //cofigura a quantidade de passos para o motor 
    
    //Motor_CART.setTargetPositionInSteps(Passos);  //cofigura a quantidade de passos para o motor 
    Motor_CART.processMovement(); //realiza o movimento até o valor do setTarget
   
}

long getCurrentPositionMotorCART(){
    return Motor_CART.getCurrentPositionInSteps(); //retorna a quantidade de passos do motor
}
long getCurrentPositionMotorETQ(){
    return Motor_ETQ.getCurrentPositionInSteps(); //retorna a quantidade de passos do motor
}

long getCurrentVelocityInStepsPerSecondCART(){
    return Motor_CART.getCurrentVelocityInStepsPerSecond();
}
long getCurrentVelocityInStepsPerSecondETQ(){
    return Motor_ETQ.getCurrentVelocityInStepsPerSecond();
}
