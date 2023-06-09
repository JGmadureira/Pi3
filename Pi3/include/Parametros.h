#include <Arduino.h>
#include "IMEC_SPIFFS.h"
#include "Encoder.h"

int QTDslv = 0;
int VELslv = 0;
int NewValue = 0;
int OldValue = 0;

void beginIMEC(){
    
    QTDslv = readFile(SPIFFS, "/qtd.txt").toInt();
    VELslv = readFile(SPIFFS, "/vel.txt").toInt();

}

int newValue(int Valor){

    //tick_menu();
    if(tick == 1){
        Valor++;    
    }else if(tick == -1){
        Valor--;
    }
    if(Valor < 0){
        Valor = 0;
    }
    return Valor;
}

void save(String QTD, String VEL){
    writeFile(SPIFFS, "/qtd.txt", QTD);
    writeFile(SPIFFS, "/vel.txt", VEL);
    
}
