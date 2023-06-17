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
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

<<<<<<< HEAD

=======
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33
int aux_conta = 0;
int filaIndex = 0;


bool aux_bt_pp     = 0,
     aux_bt_mm     = 0,
     aux_bt_ok     = 0;



<<<<<<< HEAD
=======
bool aux_bt_pp     = 0,
     aux_bt_mm     = 0,
     aux_bt_ok     = 0;
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33

TickType_t xTimeBefore, xTotalTimeSuspended;

SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;
SemaphoreHandle_t xMutex3;
SemaphoreHandle_t xMutex4;

void task_ihm_btn_display(void*parametro)
<<<<<<< HEAD
{
  while(1)
  {
    xSemaphoreTake(xMutex1, portMAX_DELAY);

    int valor_bt_pp = 0;
    int valor_bt_mm = 0;
    int valor_bt_ok = 0;
  

      if(!digitalRead(bt_pp))  aux_bt_pp  = 1;                           
      if(digitalRead(bt_pp) && aux_bt_pp)                                  
      {
        aux_bt_pp = 0;
        valor_bt_pp ++;
        display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(" -- .... ++ .... OK");
  display.display();                                                                               
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

    

  

 // display.setTextSize(1);
  //display.setCursor(1,0);
  //display.println(valor_bt_pp);
  //display.display();

    xSemaphoreGive(xMutex1);
    delay(500);
  }
}

void task_logica_1(void*parametro)
=======
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33
{
  while(1)
  {
    xSemaphoreTake(xMutex1,portMAX_DELAY);

<<<<<<< HEAD
      if(!digitalRead(in_01))  aux_bt_pp  = 1;                             
      if(digitalRead(in_01) && aux_bt_pp)                                  
      {
        aux_bt_pp = 0;                                                                             
      }
    
    xSemaphoreGive(xMutex1);

      if(!digitalRead(in_02))  aux_bt_mm  = 1;                             
      if(digitalRead(in_02) && aux_bt_mm)                                  
=======
      if(!digitalRead(bt_pp))  aux_bt_pp  = 1;                             
      if(digitalRead(bt_pp) && aux_bt_pp)                                  
      {
        aux_bt_pp = 0;                                                                             
      }

      if(!digitalRead(bt_mm))  aux_bt_mm  = 1;                             
      if(digitalRead(bt_mm) && aux_bt_mm)                                  
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33
      {
        aux_bt_mm = 0;                                                                              
      }

<<<<<<< HEAD
      if(!digitalRead(in_03))  aux_bt_ok  = 1;                             
      if(digitalRead(in_03) && aux_bt_ok)                                  
      {
        aux_bt_ok = 0;                                                                              
      }
=======
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
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33

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
  xMutex3 = xSemaphoreCreateMutex();
  xMutex4 = xSemaphoreCreateMutex();


//inicializa o display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();



  //Cria tarefa 1
  xTaskCreatePinnedToCore(
              task_ihm_btn_display,   //Tarefa
              "task_ihm_btn_display", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              3,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
<<<<<<< HEAD

  //Cria tarefa 2
  xTaskCreatePinnedToCore(
              task_logica_1,   //Tarefa
              "task_logica_1", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              3,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
=======
>>>>>>> 0d5c6eabb16ff19ad719ddbe1a49351705f8ef33
  
}

// the loop function runs over and over again forever
void loop() 
{ 

}