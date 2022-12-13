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
#include <Telas.h>

//#define FontePadrao u8g2_font_5x8_tf                          //Seleciona a fonte padrão
// U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 18, 19, 21, 22);    //Enable, RW, RS, RESET
// RotaryEncoder KY_040(39, 34);
//#define SW 35                                 //Configura os pinos CLK e DT do Codificador KY-040

// Variáveis Globais para a programação

// int NovaPosicao = 0;
int PosicaoMenu_Atual = 1;    // Variável Local de Posição do Codificador
int PosicaoMenuAjuste_Atual = 1;    // Variável Local de Posição do Codificador
int PosicaoMenu_Recebida = 0; // Variável Local de Posição do Codificador
int PosicaoMenuAjuste_Recebida = 0; // Variável Local de Posição do Codificador
bool Inicio = 1;

bool Flag_ControleManual = 0;
bool Flag_MenuPrincipal = 1;
bool Flag_MenuAjuste = 1;


const char *string_list = 
  "Altocumulus\n"
  "Altostratus\n"
  "Cirrocumulus\n"
  "Cirrostratus\n"
  "Cirrus\n"
  "Cumulonimbus\n"
  "Cumulus\n"
  "Nimbostratus\n"
  "Stratocumulus\n"
  "Stratus";

uint8_t current_selection = 0;

void setup()
{
  // u8g2.begin();                                            //Inicia a Biblioteca do Display
  // u8g2.setFont(FontePadrao);                               //Configura o tipo de Fonte u8g2_font_5x8_tf
  beginTelas();

  digitalWrite(1, HIGH); // Liga o pino do LED de luz de fundo do LCD (opcional)

  Serial.begin(115200); // Inicia a Transmissão Serial
  Serial.println("Pronto para Transmitir - XProjetos.net:");
  Serial.println("Gire o Codificador");
}

// XProjetos.net

void loop()
{
   
  current_selection = tick_menu(
    "MENU PRINCIPAL",
    current_selection, 
    string_list);

  if ( current_selection == 0 ) {
    u8g2.userInterfaceMessage(
	"Nothing selected.", 
	"",
	"",
	" ok ");
  } else {
    u8g2.userInterfaceMessage(
	"Selection:", 
	u8x8_GetStringLineStart(current_selection-1, string_list ),
	"",
	" ok \n cancel ");
  }

  /*
  if (Flag_MenuPrincipal) PosicaoMenu_Recebida = tick_menu();

  switch (PosicaoMenu_Recebida)
  {
  case menu_select_1:
    Main_1(PosicaoMenu_Atual);

    break;

  case menu_select_2:
    Main_2(PosicaoMenu_Atual);

    break;

  case menu_select_3:

    if (verificaBot() == 0)
    {
      Flag_ControleManual = 1;
      Flag_MenuPrincipal = 0;
    }
    if (Flag_ControleManual)
    {
      if (Flag_MenuAjuste)PosicaoMenuAjuste_Recebida = tick_ajustes();
      switch (PosicaoMenuAjuste_Recebida)
      {
      case menu_ajuste_1:
        ajuste_main_1(PosicaoMenuAjuste_Atual);
        if (verificaBot() == 0)
        {
          Flag_MenuPrincipal = 1;
          
        }
        break;
      
      case menu_ajuste_2:
        ajuste_main_2(PosicaoMenuAjuste_Atual);
        break;
      
      default:
        break;
      }
     
      PosicaoMenuAjuste_Atual = PosicaoMenuAjuste_Recebida;
    }
    else
    {
      Main_3(PosicaoMenu_Atual);
    }
    break;

  case menu_select_4:
    Main_4(PosicaoMenu_Atual);

    break;

  default:
    break;
  }

  PosicaoMenu_Atual = PosicaoMenu_Recebida;
  */
}