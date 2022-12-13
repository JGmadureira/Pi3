/*
GND --> GND
VCC -->5V
V0 --> Pino central de um potenciometro de 10k para ajuste de contraste (os outros dois pinos devem ser ligados em 5V e GND, como de costume)
RS --> 21
R/W -->19
E --> 18
PSB --> GND
RST --> 22
BLA --> 3,3V
BLK --> GND
*/


#include <Arduino.h>
#include <RotaryEncoder.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define PinoAnalogico 12                                        //O compilador substituirá qualquer menção de PinoAnalogico ao valor 12 no momento da compilação.
//#define PinoLED 15                                              //O compilador substituirá qualquer menção de PinoLED ao valor 15 no momento da compilação.


//PWM Setup para ESP32
int freq = 5000;                                                 //Frequencia para o PWM
int CanalLED = 0;
int resolution = 8;
byte ValorPWM = 0;                                               //Variável para armazenar a variável para o PWM


// ========= ENCODER ============== //
#define CLKE 39
#define DTE 34
#define SW 35
RotaryEncoder KY_040(CLKE, DTE);                                 //Configura os pinos CLK e DT do Codificador KY-040


bool BotaoSW = 1;                                              
int NovaPosicao = 0;
bool Inicio = 1;

// ========= LCD ============ //
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 18, 19, 21, 22);    //Enable, RW, RS, RESET
byte menu_inicial = 1;                                           //Variável para armazenar a variável para chamar o menu principal


int leituraADC = 0, AnaRead = 0;                                 //Variáveis para armazenar os valores analógicos

//Icones em XBMP para barra de icones (Gerados no GIMP)
static unsigned char bluetooth_bits[] = {
   0x10, 0x32, 0x54, 0x38, 0x38, 0x54, 0x32, 0x10 };

static unsigned char wifi_bits[] = {
   0x7e, 0x81, 0x3c, 0x42, 0x18, 0x00, 0x18, 0x18 };


//Lista do Menu Principal
const char *string_list =                                       //Lista de Menus, você pode adicionar mais itens se desejar
  "Barra de icones\n"
  "Leitura Analogica\n"
  "LED PWM\n"
  "Projeto X\n"
  "5. Item\n"
  "6. Item\n"
  "7. Item\n"
  "Final";

uint8_t current_selection = 1;      
 uint8_t PosicaoAtual = 1;                           //Configura o primeiro item estar selecionado

/*******************************************************************
 *                       SETUP
 *****************************************************************/

void setup(void) {
  
  pinMode(SW, INPUT_PULLUP);                         //Habilita o GPIO35 como entrada com Pull-up para o SW
  // MKR Zero Test Board
  //u8g2.begin(/*Select=*/ 12, /*Right/Next=*/ 27, /*Left/Prev=*/ 25, /*Up=*/ 26, /*Down=*/ 14, /*Home/Cancel=*/ 13);  //Inicia os botões de navegação para o menu
  u8g2.begin(SW, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);  //Inicia os botões de navegação para o menu
  u8g2.setFont(u8g2_font_6x12_tr);               //Configura o tipo de Fonte
  
  pinMode(PinoAnalogico, INPUT);                     //Configura o pino PinoAnalogico para IO34 como entrada
 
  
  //pinMode(PinoLED, OUTPUT);
  //------------------PWM ESP32--------------------                
  //sigmaDeltaAttachPin(PinoLED,0);                //Inicializa o PWM e anexa o PinoLED para o canal 0
  //sigmaDeltaSetup(CanalLED, freq);             //Configura a frequencia do canal 0 do PWM para 5000Hz
  //sigmaDeltaWrite(CanalLED, 0);                //Inicia o PWM em zero (pode ser configurado de 0 a 255)
}


void loop(void) { 
  BotaoSW = digitalRead(SW);                           //Lê o estado do Pino SW (Eixo do Codificador)                         
  KY_040.tick(); 
  int NovaPosicao = KY_040.getPosition(); 
 Serial.println(NovaPosicao);
PosicaoAtual = NovaPosicao;
  current_selection = 0;

  leituraADC = analogRead(PinoAnalogico);           //Leitura de porta analógica e armazenamento na variável
  u8g2.setCursor(0, 0);                         //Configura a posição do proximo item a ser escrito na tela
  u8g2.print(leituraADC);                       //Escreve o valor armazenado da porta analogica
  
  //=========================NAVEGACÃO============================
if ( menu_inicial == 1 ) {
 current_selection = u8g2.userInterfaceSelectionList( //Caso estiver no Menu Princinpal
    "Menu Principal",                                  //Titulo do Menu
    PosicaoAtual, 
    string_list
    );
}
  if ( current_selection == 0) {                       //Caso o botão voltar seja pressionado
    u8g2.userInterfaceMessage(                         // Exibir mensagem abaixo
  "Nada Selecionado.", 
  "",
  "",
  " ok ");
  } 
  //=====================FIM NAVEGACÃO============================

  
  //----------------TELA1 -  TELA DE EXEMPLO DE BARRA DE ICONES----------------- 
  if ( current_selection == 1 ) {
    menu_inicial = 0;
  u8g2.firstPage();
  do {
    KY_040.tick(); 
  current_selection = NovaPosicao;
    int8_t event2 = u8g2.getMenuEvent();
    u8g2.drawRFrame(0,11,127,51,4);           //Desenha um quadro vazio com bordas  u8g2.drawRFrame(x,y,comprimento,altura,borda);
    u8g2.drawLine(0, 9, 127, 9);              //Desenha uma linha
    u8g2.drawXBM(0, 0, 8, 8, bluetooth_bits); //Desenha uma figura tipo XBM para o bluetooth
    u8g2.drawXBM(10, 0, 8, 8, wifi_bits);     //Desenha uma figura tipo XBM para o wifi  
    if (event2 == U8X8_MSG_GPIO_MENU_HOME) {  //Verifica se o botão de voltar/home foi pressionado.
        menu_inicial = 1;                     //Caso pressionado chama o menu principal
        current_selection = 0;
     }

  }while ( u8g2.nextPage() );                 //Condição para manter a tela
  current_selection = 1;                      //se caso current_selection estiver com o mesmo ID da tela a tela fica mantida (travada)
  }                                           // Fim Tela1

//----------------TELA2-----------------

  else if ( current_selection == 2 ) {      
    int8_t event2 = u8g2.getMenuEvent();
    menu_inicial = 0;
  u8g2.firstPage();
  do {
    KY_040.tick(); 
    
  current_selection = NovaPosicao;
  leituraADC = analogRead(PinoAnalogico);     //Leitura de porta analógica e armazenamento na variável
  AnaRead = map(leituraADC, 0, 4095, 0, 120); //Faz uma equivalencia entre o maximo da porta analogica para a barra grafica
  u8g2.drawFrame(3,10,120,8);                 //Desenha um retangulo vazio para a barra gráfica
  u8g2.drawBox(3,10,AnaRead,8);               //Desenha um retangulo preenchido para a barra gráfica apartir do valor gerado do map
  u8g2.setCursor(0, 50);                      //Configura a posição do proximo item a ser escrito na tela
  u8g2.print(leituraADC);                     //Escreve o valor armazenado da porta analogica
  if (event2 == U8X8_MSG_GPIO_MENU_HOME) {    //Verifica se o botão de voltar/home foi pressionado.
        menu_inicial = 1;                     //Caso pressionado chama o menu principal
        current_selection = 0;
     } 
  }while ( u8g2.nextPage() );                 //Condição para manter a tela
  current_selection = 2;                      //se caso current_selection estiver com o mesmo ID da tela a tela fica mantida (travada)
  }                                           // Fim Tela2

//----------------TELA3-----------------

  else if ( current_selection == 3 ) {
    menu_inicial = 0;
  u8g2.firstPage();                           //buffer para exibição gráfica
  do {
  KY_040.tick();
  
  current_selection = NovaPosicao; 
  u8g2.drawFrame(1,10,126,8);                 //Desenha um retangulo vazio para a barra gráfica
  u8g2.drawBox(3,10,ValorPWM / 2,8);          //Desenha um retangulo preenchido para a barra gráfica apartir do valor gerado do ValorPWM
  //sigmaDeltaWrite(0, ValorPWM);               //Valor dado para a variável ValorPWM é enviado ao canal 0 de PWM
  u8g2.setCursor(0, 50);                      //Configura a posição do proximo item a ser escrito na tela
  u8g2.print(ValorPWM);                       //Escreve o valor armazenado do PWM
  
  int8_t event2 = u8g2.getMenuEvent();
  if (event2 == U8X8_MSG_GPIO_MENU_NEXT || event2 == U8X8_MSG_GPIO_MENU_UP) {     //Verifica se o botão de subir/avançar foi pressionado.
        ValorPWM++;                                                               //Incrementa o ValorPWM aumentando o brilho do LED
  }
  if (event2 == U8X8_MSG_GPIO_MENU_PREV || event2 == U8X8_MSG_GPIO_MENU_DOWN) {  //Verifica se o botão de subir/avançar foi pressionado.
       ValorPWM--;                                                               //Incrementa o ValorPWM aumentando o brilho do LED
  }
    if (event2 == U8X8_MSG_GPIO_MENU_HOME) {  //Verifica se o botão de voltar/home foi pressionado.
        menu_inicial = 1;                     //Caso pressionado chama o menu principal
        current_selection = 0;
     } 
  }while ( u8g2.nextPage() );                 //Condição para manter a tela
  current_selection = 3;                      //se caso current_selection estiver com o mesmo ID da tela a tela fica mantida (travada)
  }                                           //Fim Tela3
  else {
    u8g2.userInterfaceMessage(                //Caso o menu não possua nada para se exibir
  "A tela não possui nada:",                  //Exibir mensagem abaixo
  u8x8_GetStringLineStart(current_selection-1, string_list ),
  "",
  "OK \n Cancelar");
  }
}