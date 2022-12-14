#include "Arduino.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "Motor.h"
#include "Sensor.h"
#include "Parametros.h"
//#include "Encoder.h"

#define FontePadrao u8g2_font_5x8_tf                       // Seleciona a fonte padrão
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 18, 19, 21, 22); // Enable, RW, RS, RESET


//====== Defines das Telas ========= //
#define menu_select_1 1

#define menu_select_2 2
#define menu_select_21 21
#define menu_select_211 211

#define menu_select_22 22
#define menu_select_221 221

#define menu_select_23 23
#define menu_select_231 231

#define menu_select_24 24

#define menu_select_3 3
#define menu_select_31 31
#define menu_select_311 311
#define menu_select_312 312

#define menu_select_32 32

#define menu_select_33 33
#define menu_select_331 331
#define menu_select_332 332

#define menu_select_34 34

#define menu_select_4 4

bool Flag_NovaTela = 1;

bool status_sensor_1 = 0;
bool status_sensor_2 = 0;

int PosicaoMenu = 1;
int QTD = 0;
int VEL = 0;

void beginTelas(){
    u8g2.begin();              // Inicia a Biblioteca do Display
    u8g2.setFont(FontePadrao); // Configura o tipo de Fonte u8g2_font_5x8_tf
    pinMode(SW, INPUT_PULLUP); // Habilita o GPIO35 como entrada com Pull-up para o SW
    pinMode(1, OUTPUT);        // Configura o pino do LED de luz de fundo do LCD (opcional)
}

void Fundo_Principal(){
    if(Flag_NovaTela) u8g2.firstPage();// Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)

    u8g2.drawStr(24, 8, "MENU PRINCIPAL");         // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                   // Desenha uma linha
    u8g2.drawStr(1, 18, "INICIAR PRESSIONE 'OK'");   // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 28, "QTD:"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setCursor(22, 28);
    u8g2.print(QTDslv); 
    u8g2.drawStr(50, 28, "VEL:"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setCursor(70, 28);
    u8g2.print(VELslv); 
    u8g2.drawStr(1, 40, "AJUSTES DE PARAMETROS");  // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 50, "AJUSTES MANUAIS");        // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 60, "STATUS");                 // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.nextPage();
    Flag_NovaTela = false;
}

void Fundo_Menu_Ajustes(){
    if(Flag_NovaTela) u8g2.firstPage(); // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)

    u8g2.drawStr(24, 8, "AJUSTES MANUAIS");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                           // Desenha uma linha
    u8g2.drawStr(1, 18, "MOVIMENTA\xC7\xC3O MOTOR 1"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 28, "MOVIMENTA\xC7\xC3O MOTOR 2"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 38, "VISUALIZA\xC7\xC3O DOS SENSORES"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(1, 62, "RETORNAR");                 // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.nextPage();
    
    Flag_NovaTela = false;
}

void Fundo_Menu_Erro(){
    if(Flag_NovaTela) u8g2.firstPage(); // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)

    u8g2.drawStr(24, 8, "ERRO");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                           // Desenha uma linha
    
    u8g2.nextPage();
    
    Flag_NovaTela = false;
}

void Fundo_Motores(){
    if(Flag_NovaTela) u8g2.firstPage(); // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)

    u8g2.drawStr(24, 8, "ROTA\xC7\xC3O MOTOR");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                           // Desenha uma linha
    u8g2.drawStr(1, 60, "'OK' PARA RETORNAR");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)

    u8g2.nextPage();
    Flag_NovaTela = false;
}

void Fundo_Parametros(){
    if(Flag_NovaTela){ 
        u8g2.firstPage();     // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)
        VEL = VELslv;
        QTD = QTDslv;
       
    }
    u8g2.drawStr(10, 8, "AJUSTES DE PARAMETROS");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                           // Desenha uma linha
    u8g2.drawStr(1, 20, "QUANTIDADE:"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setCursor(85,20);
    u8g2.print(QTD);
    u8g2.drawStr(1, 32, "VELOCIDADE:"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setCursor(85,32);
    u8g2.print(VEL);
    u8g2.drawStr(16, 60, "SALVAR");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(73, 60, "RETORNAR");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)

    u8g2.nextPage();
    Flag_NovaTela = false;
}

void UPD_Tela(int a, int b, int c, int d){// Atualiza a tela (a = atual b= click c= anterior d= proxima)
    
    if (tick == 1){
        PosicaoMenu = d;
        Flag_NovaTela = true;
    }else if(tick == -1){
        PosicaoMenu =  c;
        Flag_NovaTela = true;
    }else if(verificaBot()){ 
        PosicaoMenu = b; 
        Flag_NovaTela = true;
    }else{
        PosicaoMenu = a;
    }  
}

void giro_Motor(){
    if(tick == -1){
        giro_direita();
    }else if(tick == 1){
        giro_esquerda();
    }
}

void Main_1(){
    Fundo_Principal();
    u8g2.drawRFrame(0, 10, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(1, 1, 3, 2);
    
}

void Main_2(){
    Fundo_Principal();
    u8g2.drawRFrame(0, 32, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(2, 21, 1, 3);// a = atual b= click c= anterior d= proxima
    
}

void Main_21(){
    //QUANTIDADE
    Fundo_Parametros();
    u8g2.drawRFrame(60, 12, 60, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(21, 211, 21, 22);// a = atual b= click c= anterior d= proxima
    
}

void Main_211(){
    //VALOR QUANTIDADE
    QTD = newValue(QTDslv);
    Fundo_Parametros();
    u8g2.drawRFrame(60, 12, 60, 10, 2); // Desenha um retangulo em volta do titulo
    u8g2.setCursor(85,20);
    u8g2.print(QTD);
    UPD_Tela(211, 21, 211, 211);// a = atual b= click c= anterior d= proxima
}

void Main_22(){
    //VELOCIDADE
    Fundo_Parametros();
    u8g2.drawRFrame(60, 24, 60, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(22, 221, 21, 23);// a = atual b= click c= anterior d= proxima
    
}

void Main_221(){
    //VALOR VELOCIDADE
    VEL = newValue(VELslv);
    Fundo_Parametros();
    u8g2.drawRFrame(60, 24, 60, 10, 2); // Desenha um retangulo em volta do titulo
    u8g2.setCursor(85,32);
    u8g2.print(VEL);
    UPD_Tela(221, 22, 221, 221);// a = atual b= click c= anterior d= proxima
    
}

void Main_23(){
    //SALVAR
    Fundo_Parametros();
    u8g2.drawRFrame(11, 52, 39, 10, 2); // Desenha um retangulo em volta do titulo 
    UPD_Tela(23, 231, 22, 24);// a = atual b= click c= anterior d= proxima
    
}

void Main_231(){
    
    if(Flag_NovaTela) u8g2.firstPage(); // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)

    u8g2.drawStr(28, 28, "VALORES SALVOS"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawStr(17, 52, "'OK' PARA RETORNAR"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.nextPage();
    Flag_NovaTela = false;
    UPD_Tela(231, 23, 231, 231);// a = atual b= click c= anterior d= proxima
    save(String(QTD), String(VEL));
}

void Main_24(){
    //RETORNAR
    Fundo_Parametros();
    u8g2.drawRFrame(68, 52, 49, 10, 2); // Desenha um retangulo em volta do titulo 
    UPD_Tela(24, 2, 23, 24);// a = atual b= click c= anterior d= proxima
    
}

void Main_3(){
    Fundo_Principal();
    u8g2.drawRFrame(0, 42, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(3, 31, 2, 1);// a = atual b= click c= anterior d= proxima

}

void Main_31(){
   
    beginMotor(26, 27); //Motor 1
    Fundo_Menu_Ajustes();
    u8g2.drawRFrame(0, 10, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(31, 311, 34, 32);// a = atual b= click c= anterior d= proxima
    
}

void Main_32(){
    
    beginMotor(16, 17);//Motor 2
    Fundo_Menu_Ajustes();
    u8g2.drawRFrame(0, 20, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(32, 311, 31, 33);// a = atual b= click c= anterior d= proxima
    
}

void Main_33(){
    //Sensor 
    Fundo_Menu_Ajustes();
    u8g2.drawRFrame(0, 30, 127, 10, 2); // Desenha um retangulo em volta do titulo
    UPD_Tela(33, 331, 32, 34);// a = atual b= click c= anterior d= proxima
    
}

void Main_34(){
    //Retornar
    Fundo_Menu_Ajustes();
    u8g2.drawRFrame(0, 54, 127, 10, 2); // Desenha um retangulo em volta do titulo 
    UPD_Tela(34, 3, 33, 31);// a = atual b= click c= anterior d= proxima
    
}

void Main_311(){
    Fundo_Motores();                                  
    
    giro_Motor();
    u8g2.drawStr(20, 28, "ESQUERDA"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setFont(u8g2_font_open_iconic_all_4x_t);           //Configura a fonte para uma fonte diferente do padrão
    u8g2.drawGlyph(84, 55, 0x0043);                         //Exibe o Desenho de uma Flecha girando para a Esquerda
    u8g2.setFont(FontePadrao);                              //Retorna para a fonte padrão do projeto
          
    UPD_Tela(311, 31, 311, 312);// a = atual b= click c= anterior d= proxima

}

void Main_312(){
    Fundo_Motores();                                  
    
    giro_Motor();
    u8g2.drawStr(20, 28, "DIREITA"); // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.setFont(u8g2_font_open_iconic_all_4x_t);           //Configura a fonte para uma fonte diferente do padrão
    u8g2.drawGlyph(84, 55, 0x0042);                         //Exibe o Desenho de uma Flecha girando para a Direita
    u8g2.setFont(FontePadrao);                              //Retorna para a fonte padrão do projeto
          
    UPD_Tela(312, 32, 311, 312);// a = atual b= click c= anterior d= proxima
   
}

void Main_331(){                                 
    //SENSOR
    if(status_sensor_1 != read_Sensor_1() || status_sensor_2 != read_Sensor_2())Flag_NovaTela = true;

    if(Flag_NovaTela) u8g2.firstPage(); // Este comando é parte do loop (imagem) que renderiza o conteúdo da exibição. (Obrigatório)
   
    u8g2.drawStr(20, 8, "LEITURA DOS SENSORES");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
    u8g2.drawLine(0, 9, 127, 9);                   // Desenha uma linha
    if(read_Sensor_1()){
        u8g2.drawStr(20, 28, "SENSOR 1: INATIVO" );
    }else{
        u8g2.drawStr(20, 28, "SENSOR 1: ATIVO" );
    }
    if(read_Sensor_2()){
        u8g2.drawStr(20, 38, "SENSOR 2: INATIVO" );
    }else{
        u8g2.drawStr(20, 38, "SENSOR 2: ATIVO" );
    }
    u8g2.drawStr(1, 60, "'OK' PARA RETORNAR");                // Escreve o titulo o topo da página (semelhante ao print porem não aceita UTF-8)
   
    status_sensor_1 = read_Sensor_1();
    status_sensor_2 = read_Sensor_2();
    u8g2.nextPage();
    Flag_NovaTela = false;
    UPD_Tela(331, 33, 331, 331);// a = atual b= click c= anterior d= proxima
}
