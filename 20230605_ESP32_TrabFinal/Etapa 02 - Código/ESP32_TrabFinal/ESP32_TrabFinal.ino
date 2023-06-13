/* ===========================================================
   @Curso de Engenharia Elétrica e Engenharia da Computação
   @Tarefa2GB-PLC em ESP32 com FreeRTOS 
      
   Disciplina de Interfaceamento e Drivers
   
   Professor: Lúcio Rene Prade
   Autor: Daniel Klauck e Felipe Paloschi
==============================================================*/

//============================================================
//teste
// --- Bibliotecas ---
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Mapeamento de Hardware ---
// --- Define entrada dos botões de escolha ---
#define bt_pp GPIO_NUM_12
#define bt_mm GPIO_NUM_14
#define bt_ok GPIO_NUM_27

// --- Define entradas digitais do PLC ---
#define in_01 GPIO_NUM_35
#define in_02 GPIO_NUM_34
#define in_03 GPIO_NUM_15
#define in_04 GPIO_NUM_4

// --- Define entrada analógica do PLC ---
#define a_in_04 GPIO_NUM_13

// --- Define saídas digitais do PLC ---
#define out_01 GPIO_NUM_26
#define out_02 GPIO_NUM_25
#define out_03 GPIO_NUM_33
#define out_04 GPIO_NUM_32

// --- Defines do Display ---
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int aux_conta = 0;

bool aux_bt_pp     = 0,
     aux_bt_mm     = 0,
     aux_bt_ok     = 0;

TickType_t xTimeBefore, xTotalTimeSuspended;

SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;

void task_ihm_btn_display(void*parametro)
{
  while(1)
  {
    xSemaphoreTake(xMutex1,portMAX_DELAY);

      if(!digitalRead(bt_pp))  aux_bt_pp  = 1;                             
      if(digitalRead(bt_pp) && aux_bt_pp)                                  
      {
        aux_bt_pp = 0;                                                                             
      }

      if(!digitalRead(bt_mm))  aux_bt_mm  = 1;                             
      if(digitalRead(bt_mm) && aux_bt_mm)                                  
      {
        aux_bt_mm = 0;                                                                              
      }

      if(!digitalRead(bt_ok))  aux_bt_ok  = 1;                             
      if(digitalRead(bt_ok) && aux_bt_ok)                                  
      {
        aux_bt_ok = 0;                                                                              
      }

    String var = ":";
    Serial.print("+...-...ok "); 
    Serial.println("");

    xSemaphoreGive(xMutex1);

    delay(500);
  }
}

void task_tempo(void*parametro)
{  
  while(1)
  {

  }
}

void task_display(void*parametro)
{
  while(1)
  {
    xSemaphoreTake(xMutex2,portMAX_DELAY);
    
    String var = ":";
    Serial.print("Cronometro "); 
    Serial.print(h + var + m + var + s);
    Serial.println("");

    Serial.print("parcial 1 ");
    Serial.print(parcial1_h + var + parcial1_m + var + parcial1_s);
    Serial.println("");

    Serial.print("parcial 2 ");
    Serial.print(parcial2_h + var + parcial2_m + var + parcial2_s);
    Serial.println("");
    Serial.println("");

    xSemaphoreGive(xMutex2);

    delay(500);
  }
}

void setup() 
{

//==========================================
  pinMode(bt_pp, INPUT_PULLUP);                                                       
  pinMode(bt_mm, INPUT_PULLUP);                                                       
  pinMode(bt_ok, INPUT_PULLUP);                                               

  pinMode(in_01, INPUT_PULLUP);
  pinMode(in_02, INPUT_PULLUP);  
  pinMode(in_03, INPUT_PULLUP);  
  pinMode(in_04, INPUT_PULLUP);
  pinMode(a_in_04, INPUT);

  pinMode(out_01, OUTPUT);
  pinMode(out_02, OUTPUT);  
  pinMode(out_03, OUTPUT);  
  pinMode(out_04, OUTPUT);

  Serial.begin(115200);
  delay(1000);

  xMutex1 = xSemaphoreCreateMutex();
  xMutex2 = xSemaphoreCreateMutex();

  //Cria tarefa 1
  xTaskCreatePinnedToCore(
              task_tempo,   //Tarefa
              "task_tempo", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              3,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
  
}

// the loop function runs over and over again forever
void loop() 
{ 
}