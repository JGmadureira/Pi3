#include <Arduino.h>

#define pinLed 2
#define Sensor 15

void setup(){
    Serial.begin(115200);
    pinMode(Sensor, INPUT_PULLUP);
    pinMode(pinLed, OUTPUT);
    digitalWrite(pinLed, LOW);

}

void loop(){
    if(digitalRead(Sensor)==LOW){
        digitalWrite(pinLed, HIGH);
        
    }
    else{
        digitalWrite(pinLed, LOW);
    
    }
}