#include <Arduino.h>

#define Sensor_1 15
#define Sensor_2 23

bool leitura_1 = false;
bool leitura_2 = false;

void begin_Sensores(){
    pinMode(Sensor_1, INPUT_PULLUP);
    pinMode(Sensor_2, INPUT_PULLUP);
}

bool read_Sensor_1(){
    if (digitalRead(Sensor_1) == true){
        leitura_1 = true;
    }else{
        leitura_1 = false;
    }
    Serial.println(leitura_1);
    return leitura_1;
}

bool read_Sensor_2(){
    if (digitalRead(Sensor_2) == true){
        leitura_2 = true;
    }else{
        leitura_2 = false;
    }
    //Serial.println(leitura_2);
    return leitura_2;
}