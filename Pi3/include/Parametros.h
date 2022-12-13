#include <Arduino.h>
#include "IMEC_SPIFFS.h"
#include <RotaryEncoder.h>

RotaryEncoder KY_040(39, 34);
#define SW 35 // Configura os pinos CLK e DT do Codificador KY-040

bool BotaoSW = 0;
bool BotaoAnt = 1;

//===== Variaveis do encoder ====== //
int NovaPosicao = 0;
int PosicaoAnterior = 0;


int QTDslv = 0;
int VELslv = 0;
int NewValue = 0;
int OldValue = 0;

void beginIMEC(){
    
    QTDslv = readFile(SPIFFS, "/qtd.txt").toInt();
    VELslv = readFile(SPIFFS, "/vel.txt").toInt();

}

int newValue(int Valor){
    KY_040.tick(); // Verificar o estado do Codificador
    NewValue = KY_040.getPosition();

    if(NewValue < 0){
        NewValue = 0;
    }

    return NewValue;
    /*
    if(NewValue < OldValue){
        Valor--;
    }else if(NewValue > OldValue){
        Valor++;
    }else{
        Valor;
    }
    NewValue = OldValue;
    return Valor;
    */
}

void save(String QTD, String VEL){
    writeFile(SPIFFS, "/qtd.txt", QTD);
    writeFile(SPIFFS, "/vel.txt", VEL);
    beginIMEC();
}



