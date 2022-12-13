/*============================================================================
Programa de teste para o Codificador KY-040 para ESP32, desenvolvido por JailsonBR utilizando a biblioteca u8g2 do olikraus.
   
   
  Código adaptado por JailsonBR do site XProjetos.net em 19-01-2020, o uso deste código é livre porem deve respeitar e mante o nome do criador
  e tambêm de quem modificou.

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright(c) sobre o XPsys 2020, XProjetos.net

------------------------------------------------------------------------------

Program test for the KY-040 Encoder for ESP32, developed by JailsonBR using the olikraus u8g2 library.

   Code adapted by JailsonBR from the site XProjetos.net on 01-19-2020, the use of this code is free but must respect and keep the name of the creator
   and also those who modified it.

   Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

   Copyright (c) about XPsys 2020, XProjetos.net
==============================================================================*/

#include <Arduino.h>
#include <RotaryEncoder.h>
#include <U8g2lib.h>
#include <SPI.h>

#define FontePadrao u8g2_font_5x8_tf                          //Seleciona a fonte padrão
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 18, 19, 21, 22);    //Enable, RW, RS, RESET
RotaryEncoder KY_040(39, 34);
#define SW 35                                 //Configura os pinos CLK e DT do Codificador KY-040

//Variáveis Globais para a programação
bool BotaoSW = 1;                                              
int NovaPosicao = 0;
bool Inicio = 1;

void setup()
{
  u8g2.begin();                                            //Inicia a Biblioteca do Display
  u8g2.setFont(FontePadrao);                               //Configura o tipo de Fonte u8g2_font_5x8_tf
  pinMode(SW, INPUT_PULLUP);                               //Habilita o GPIO35 como entrada com Pull-up para o SW
  pinMode(1, OUTPUT);                                      //Configura o pino do LED de luz de fundo do LCD (opcional)
  digitalWrite(1, HIGH);                                   //Liga o pino do LED de luz de fundo do LCD (opcional)

  Serial.begin(115200);                                      //Inicia a Transmissão Serial
  Serial.println("Pronto para Transmitir - XProjetos.net:");
  Serial.println("Gire o Codificador");
}

//XProjetos.net

void loop()
{
      int PosicaoAtual = 0;                                //Variável Local de Posição do Codificador
      
      BotaoSW = digitalRead(SW);                           //Lê o estado do Pino SW (Eixo do Codificador)                         
      KY_040.tick();                                       // Verificar o estado do Codificador
      int NovaPosicao = KY_040.getPosition();

      if (PosicaoAtual != NovaPosicao || BotaoSW == 0 || Inicio == 1) {

      Serial.print(NovaPosicao);
      Serial.println();
      Inicio = 0;

      u8g2.firstPage();                                        //Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)
      do {                                                     //Tudo o que estiver dentro do "do {}" será exibido na tela.
      
      u8g2.drawRFrame(0,0,127,10,2);                          //Desenha um retangulo em volta do titulo
      u8g2.drawStr(15,8,"Teste Encoder KY-040");              //Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
      u8g2.drawStr(15,18,"Posi\xe7\xe3o:");                   //Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
      u8g2.drawRFrame(13,22,64,16,2);                         //Desenha um retangulo em volta do titulo
      u8g2.drawRFrame(80,16,42,42,4);                         //Desenha um retangulo em volta do icone
      u8g2.setCursor(2, 46);                                  //Configura a posição do proximo item a ser escrito na tela
      u8g2.print("Bot\xe3o Eixo:");                           //Escreve na tela baseado na posição informada anteriormente..
      u8g2.setCursor(65, 46);                                 //Configura a posição do proximo item a ser escrito na tela
      u8g2.print(BotaoSW);                                    //Escreve na tela a variavel temporaria do botão do Eixo (SW).

      if(BotaoSW == 0) {                                       //Caso  o Eixo do Codificador seja pressionado
        u8g2.setCursor(2, 56);                                 //Configura a posição do proximo item a ser escrito na tela
        u8g2.print("Eixo Press.");
        Serial.println("Botao Pressionado");
        u8g2.setFont(u8g2_font_open_iconic_all_4x_t);          //Configura a fonte para uma fonte diferente do padrão
        u8g2.drawGlyph(84, 55, 0x004f);                        //Exibe o Desenho de uma Flecha para Baixo
        u8g2.setFont(FontePadrao);                             //Retorna para a fonte padrão do projeto
      }
      
      if(NovaPosicao > PosicaoAtual){                           //Caso  o Eixo do Codificador for girado sentido horário
        u8g2.setFont(u8g2_font_open_iconic_all_4x_t);           //Configura a fonte para uma fonte diferente do padrão
        u8g2.drawGlyph(84, 55, 0x0042);                         //Exibe o Desenho de uma Flecha girando para a Direita
        u8g2.setFont(FontePadrao);                              //Retorna para a fonte padrão do projeto
      }

      if(NovaPosicao < PosicaoAtual){                           //Caso  o Eixo do Codificador for girado sentido anti-horário
        u8g2.setFont(u8g2_font_open_iconic_all_4x_t);           //Configura a fonte para uma fonte diferente do padrão
        u8g2.drawGlyph(84, 55, 0x0043);                         //Exibe o Desenho de uma Flecha girando para a Esquerda
        u8g2.setFont(FontePadrao);                              //Retorna para a fonte padrão do projeto
      }

      u8g2.setCursor(15, 35);                                   //Configura a posição do proximo item a ser escrito na tela
      u8g2.setFont(u8g2_font_unifont_t_latin);                  //Configura a fonte para uma fonte diferente do padrão
      u8g2.print(NovaPosicao);                                  //Escreve na tela a posição armazenada do Encoder.
      u8g2.setFont(FontePadrao);                                //Retorna para a fonte padrão do projeto
                                                            
    }
    while ( u8g2.nextPage() );                                  //Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)
    PosicaoAtual = NovaPosicao;                                 //Armazena a Posição Atual na Nova posição
  }
}