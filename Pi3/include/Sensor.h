#include <Arduino.h>

#define Sensor_ETQ 15
#define Sensor_CART 23

bool leitura_Etq = false;
bool leitura_Cart = false;

void begin_Sensores(){
    pinMode(Sensor_ETQ, INPUT_PULLUP);
    pinMode(Sensor_CART, INPUT_PULLUP);
}

bool read_Sensor_ETQ(){
    if (digitalRead(Sensor_ETQ) == true){
        leitura_Etq = true;
    }else{
        leitura_Etq = false;
    }
    //Serial.println(leitura_Etq);
    return leitura_Etq;
}

bool read_Sensor_CART(){
    if (digitalRead(Sensor_CART) == true){
        leitura_Cart = true;
    }else{
        leitura_Cart = false;
    }
    //Serial.println(leitura_Cart);
    return leitura_Cart;
}