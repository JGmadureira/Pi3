#include "Arduino.h"
#include <RotaryEncoder.h>

RotaryEncoder KY_040(39, 34);
#define SW 35 // Configura os pinos CLK e DT do Codificador KY-040

bool BotaoSW = 0;
bool BotaoAnt = 1;

//===== Variaveis do encoder ====== //
int NovaPosicao = 0;
int PosicaoAnterior = 0;


int verificaBot(){
    int BotaoOut = 0;
    BotaoSW = digitalRead(SW); // Lê o estado do Pino SW (Eixo do Codificador)
    if (BotaoSW > BotaoAnt){
        BotaoOut = 1;
    }else
    {
        BotaoOut = 0;
    }
    BotaoAnt = BotaoSW;
    return BotaoOut;
}

void tick_menu()
{
    int tick =0;
    KY_040.tick(); // Verificar o estado do Codificador
    NovaPosicao = KY_040.getPosition();

    if (PosicaoAnterior > NovaPosicao){
        tick = 1;
    }
    else if (PosicaoAnterior < NovaPosicao){
        tick = -1;
    }
    else{
        tick = 0;
    }

    PosicaoAnterior = NovaPosicao;
}

void tick(){
    int tick =0;
    KY_040.tick(); // Verificar o estado do Codificador
    NovaPosicao = KY_040.getPosition();

}