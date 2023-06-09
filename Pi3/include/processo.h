#include "Motor.h"
#include <Arduino.h>

#define prepara_ETQ 0
#define prepara_CART 1
#define andarCARTsensor 2
#define andarCART_ETQ 3
#define atualizaQTD_ETQ 4
#define aguardar_retorno 5
#define Zero_cart 6
#define Zero_etq 7

#define vel_1 1     //100 cartão 424 etiqueta(4x > cartão)
#define vel_2 2     //500 cartão 2120 etiqueta(4x > cartão)
#define vel_3 3     //1000 cartão 4240 etiqueta(4x > cartão)

float VEL_CART = 0.0;
float VEL_ETQ = 0.0;
float VEL_ETQ_COLA = 0.0;

int estadoColagem = 0;

int VEL = 1;
int QTD = 0;
int QTD_ATUAL = 0;

bool flagCartaoFIX = 0;
bool flagCartao_ETQ = 0;
bool sensorETQ_anterior = 0;
bool sensorCART_anterior = 0;


void defineVelocidade(){
    switch (VEL)
    {
    case vel_1:
        VEL_CART = 100.0;
        VEL_ETQ = 100.0;
        VEL_ETQ_COLA = 424.0;//212-->2x  424-->4x   
        break;
    
    case vel_2:
        VEL_CART = 500.0;
        VEL_ETQ = 300.0;
        VEL_ETQ_COLA = 2120.0;
        break;
    
    case vel_3:
        VEL_CART = 1000.0;
        VEL_ETQ = 900.0;
        VEL_ETQ_COLA = 4240.0;
        break;
    
    default:
        break;
    }

}

void preparaCartao(){
    defineVelocidade();
    if(limitSwitchState_CART==HIGH){
        //Motor_CART.startAsService(1); // LIMIT_SWITCH_BEGIN

        MotorCART(VEL_CART, 1000, 1000.0, 1000.0); //long vel, long Passos, long acel, long deacel

        //MotorCART(VEL_CART, 1000, 1000.0, 1000.0); //long vel, long Passos, long acel, long deacel
        while (!Motor_CART.processMovement() && limitSwitchState_CART==HIGH);///////////////////////////////////////////////////////////////////////
        // ideia de usar interrupção 
        //attach an interrupt to the IO pin of the limit switch and specify the handler function
        //attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_PIN), limitSwitchHandler, CHANGE);
    }else if(!sensorCART_anterior){
      sensorCART_anterior = read_Sensor_CART();
      Motor_CART.motionComplete();
      Motor_CART.setCurrentPositionInSteps(0);
    }
}

void avancaCartaoSensor(){    //avança o cartão até sair de cima do sensor do cartão 
    defineVelocidade();
    if(limitSwitchState_CART==LOW){

        MotorCART(VEL_CART, 1000, 1000.0, 1000.0); //long vel, long Passos, long acel, long deacel
    
        while (!Motor_CART.processMovement() && limitSwitchState_CART==LOW);
    }
    else {
      Motor_CART.motionComplete();
      Motor_CART.setCurrentPositionInSteps(0);
    }
}

void preparaETQ(){
    defineVelocidade();
    if(limitSwitchState_ETQ == HIGH){
        MotorETQ(VEL_ETQ, 1000, 1000.0, 1000.0); //long vel, long Passos, long acel, long deacel
        while (!Motor_ETQ.processMovement() && limitSwitchState_ETQ==HIGH);
    }
    else if(!sensorETQ_anterior){

      sensorETQ_anterior = read_Sensor_ETQ();
      Motor_ETQ.motionComplete();
      Motor_ETQ.setCurrentPositionInSteps(0);
    }
}

void procuraSensor_ETQ(){

    Motor_ETQ.setDirectionToHome(1);////////////////
    Motor_ETQ.goToLimitAndSetAsHome(NULL, 2000000000L);////
   
 
}

String infoProcesso(){
    switch (estadoColagem)
    {
    case prepara_ETQ:
        return "Colando..."; 
        break;
    
    case prepara_CART:
        return "Colando..."; 
        break;
    
    case andarCARTsensor:
        return "Colando..."; 
        break;
    
    case andarCART_ETQ:
        return "0"; 
        break;

    case Zero_cart:
        return "Falta de Cartao";

    break;

    case Zero_etq:
        return "Falta de Etiqueta";

    break;

    default:
        return "Finalizado Aguardando";
        break;
    }
     
}

int processoColagem(){
    defineVelocidade();
    switch (estadoColagem)
    {
    case prepara_ETQ:
        preparaETQ();
        if(!read_Sensor_ETQ())estadoColagem = prepara_CART;    //prepara etiqueta 
        if(getCurrentPositionMotorETQ() == 1000) estadoColagem = Zero_etq;
        break;
    
    case prepara_CART:
        preparaCartao();
        if(!read_Sensor_CART())estadoColagem = andarCARTsensor;    //prepara cartão 
        if(getCurrentPositionMotorCART() == 1000) estadoColagem = Zero_cart;
        break;

    case andarCARTsensor:
        avancaCartaoSensor();
        if(read_Sensor_CART()){
            Motor_ETQ.setCurrentPositionInSteps(0);
            Motor_CART.setCurrentPositionInSteps(0);
            estadoColagem = andarCART_ETQ;    //prepara cartão 
        }
        break;
    
    
    case andarCART_ETQ: 
       // MotorCART(100, 255, 1000, 1000); //para motor em 200 p/r(driver) 255
       // MotorETQ(212, 155, 1000, 1000); //para motor em 800 p/r(driver) 155

        MotorCART(VEL_CART, 200, 2000.0, 1000.0); //long vel, long Passos, long acel, long deacel
        MotorETQ(VEL_ETQ_COLA, 55, 2000.0, 1000.0); //long vel, long Passos, long acel, long deacel

        if(getCurrentPositionMotorCART()<200){
            Motor_CART.processMovement();
        }
        if(getCurrentPositionMotorETQ()<55){
            Motor_ETQ.processMovement();
        }
        if(getCurrentPositionMotorCART()==200 && getCurrentPositionMotorETQ()==55){
           // Motor_CART.emergencyStop();
           // Motor_CART.releaseEmergencyStop();
           // Motor_CART.stopService();

            //Motor_ETQ.emergencyStop();
            //Motor_ETQ.releaseEmergencyStop();
           // Motor_ETQ.stopService();

           // Motor_ETQ.motionComplete();
            //MotorETQ(212, 155, 1000, 1000); //para motor em 800 p/r(driver) 155Motor_CART.motionComplete();

            Motor_ETQ.setCurrentPositionInSteps(0);
            Motor_CART.setCurrentPositionInSteps(0);
            estadoColagem = atualizaQTD_ETQ;
        }
        break;

    case atualizaQTD_ETQ: 
        Serial.println("atualizaQTD_ETQ");
        QTD_ATUAL++;
        if(QTD_ATUAL < QTD){
            estadoColagem = 0;
        }
        if(QTD_ATUAL == QTD){
            estadoColagem = aguardar_retorno; 
            QTD_ATUAL = 0;
        }
        break;
    case aguardar_retorno: 
        

        break;

    default:
        break;
    }
    return estadoColagem;
    
}

void setEstadoColagemINI(){
    estadoColagem = 0;
    Motor_ETQ.setCurrentPositionInSteps(0);
    Motor_CART.setCurrentPositionInSteps(0);
}

bool setNovaTela(){
    return true;
}