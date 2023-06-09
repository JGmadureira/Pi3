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
#include "TELAS.h"
#include "IMEC_SPIFFS.h"

void setup()
{
  // u8g2.begin();                                            //Inicia a Biblioteca do Display
  // u8g2.setFont(FontePadrao);                               //Configura o tipo de Fonte u8g2_font_5x8_tf
  beginTelas();
  configMotores();
  initSPIFFS();
  beginIMEC();
  VEL = VELslv;
  QTD = QTDslv;
  digitalWrite(1, HIGH); // Liga o pino do LED de luz de fundo do LCD (opcional)
  Serial.begin(115200); // Inicia a Transmissão Serial
  
}

void loop()
{
  //Serial.print(digitalRead(39));
  //Serial.println(digitalRead(34));
  tick_menu();

  switch (PosicaoMenu)
  {
  case menu_select_1:
    Main_1();

    break;

  case menu_select_11:
    Main_11();

    break;

  case menu_select_2:
    Main_2();

    break;
  case menu_select_21:
    Main_21();

    break;
  case menu_select_22:
    Main_22();

    break;
  case menu_select_23:
    Main_23();

    break;

  case menu_select_24:
    Main_24();

    break;
  case menu_select_211:
    Main_211();

    break;
  case menu_select_221:
    Main_221();

    break;
  case menu_select_231:
    Main_231();

    break;

  case menu_select_3:
    Main_3();

    break;

  case menu_select_31:
     Main_31();

    break;

  case menu_select_32:
     Main_32();
    
    break;

  case menu_select_33:
     Main_33();
    
    break;
  case menu_select_34:
     Main_34();
    
    break;

  case menu_select_311:
     Main_311();
    
    break;
  case menu_select_312:
     Main_312();
    
    break;
  case menu_select_331:
     Main_331();
    
    break;
 

  default:
   Fundo_Menu_Erro();
  
    break;
  }

}