/* =========================================================================
   @Curso de Engenharia Elétrica e Engenharia da Computação
   @Tarefa2GB-PLC em ESP32 com FreeRTOS 
      
   Disciplina de Interfaceamento e Drivers
   
   Professor: Lúcio Rene Prade
   Autor: Daniel Klauck e Felipe Paloschi
============================================================================*/

//==========================================================================

// --- Bibliotecas --- =====================================================
#include <SPI.h>
#include <Wire.h>
//==========================================================================

// -- Inicializa filas --- =================================================
QueueHandle_t integerQueue1,
              integerQueue2,
              integerQueue3,
              integerQueue4;
//==========================================================================

// --- Mapeamento de Hardware --- ==========================================
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
#define a_in_01 GPIO_NUM_13

// --- Define saídas digitais do PLC ---
#define out_01 GPIO_NUM_26
#define out_02 GPIO_NUM_25
#define out_03 GPIO_NUM_33
#define out_04 GPIO_NUM_32
//==========================================================================

<<<<<<< HEAD
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

=======
volatile int    aux_volat_IN1_task1 = 0,
                aux_volat_IN2_task1 = 0,
                aux_volat_IN3_task1 = 0,
                aux_volat_IN4_task1 = 0;

volatile float  aux_volat_a0_task1 = 0;
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22

int   menu_number           = 1,
      menu_operacoes        = 1,
      menu_entradas         = 1,
      aux_escolha_task      = 1,
      aux_task_escolhida    = 1,
      aux_escolha_IN1       = 1,
      aux_IN1_escolhida     = 1,
      aux_escolha_IN2       = 1,
      aux_IN2_escolhida     = 1,
      aux_escolha_OP1       = 1,
      aux_OP1_escolhida     = 1,
      aux_escolha_OP2       = 1,
      aux_OP2_escolhida     = 1,
      aux_confirma          = 1,
      aux_escolha_OK        = 1;

bool  aux_bt_pp             = 0,
      aux_bt_mm             = 0,
      aux_bt_ok             = 0;

int aux_conta               = 0,
    delay_Time              = 0;

float threshold_Valor       = 0.0;



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
<<<<<<< HEAD
=======
SemaphoreHandle_t xMutex5;
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22

void task_ihm_btn_display(void*parametro)
<<<<<<< HEAD
{
  while(1)
<<<<<<< HEAD
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
=======
  { 
      int valor_analogica;

      // --- Variáveis para ajuste no valor do tempo --- =============================== 
      const int valorMinimo = 0;
      const int valorMaximo = 4095;
      const int valorMinimoMapeado = 0;
      const int valorMaximoMapeado = 15;

      // --- Variável para ajuste no valor do Threshold --- =============================== 
      const int valor_minimo_threshold = 0.0;
      const int valor_maximo_threshold = 4095;
      const int valor_minimo_map_threshold = 500;
      const int valor_maximo_map_threshold = 3300;

      // --- Variáveis --- ===============================
      int Max_itens_menu            = 6,
          max_task_logica           = 4,
          max_escolha_entradas      = 6,
          max_escolha_operacoes     = 5,
          min_task_logica           = 1,
          min_escolha_entradas      = 1,
          min_escolha_operacoes     = 1;
      
      if(!digitalRead(bt_pp))  aux_bt_pp  = 1;                             
      if(digitalRead(bt_pp) && aux_bt_pp)                                  
      {
        aux_bt_pp = 0;

          // --- Aumenta escolha da task --- ===============================
          if(aux_escolha_task)  
            { 
              aux_task_escolhida ++;

              if(aux_task_escolhida > max_task_logica)
              aux_task_escolhida = max_task_logica;
            }
          // ===============================================================

          // --- Aumenta escolha da entrada 1 --- ==========================
          if(aux_escolha_IN1)  
            { 
              aux_IN1_escolhida ++;

              if(aux_IN1_escolhida > max_escolha_entradas)
              aux_IN1_escolhida = max_escolha_entradas;
            }
          // ===============================================================
          
          // --- Aumenta escolha da entrada 2 --- ==========================
          if(aux_escolha_IN2)  
            { 
              aux_IN2_escolhida ++;

              if(aux_IN2_escolhida > max_escolha_entradas)
              aux_IN2_escolhida = max_escolha_entradas;
            }
          // ===============================================================
          
          // --- Aumenta escolha da operação 1 --- =========================
          if(aux_escolha_OP1)  
            { 
              aux_OP1_escolhida ++;

              if(aux_OP1_escolhida > max_escolha_operacoes)
              aux_OP1_escolhida = max_escolha_operacoes;
            }
          // ===============================================================

          // --- Aumenta escolha da operação 2 --- =========================
          if(aux_escolha_OP2)  
            { 
              aux_OP2_escolhida ++;

              if(aux_OP2_escolhida > max_escolha_operacoes)
              aux_OP2_escolhida = max_escolha_operacoes;
            }
          // ===============================================================                                                 
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22
      }

      if(!digitalRead(bt_mm))  aux_bt_mm  = 1;                             
      if(digitalRead(bt_mm) && aux_bt_mm)                                  
      {
        aux_bt_mm = 0;

          // --- Diminui escolha da task --- ===============================
          if(aux_escolha_task)  
            { 
              aux_task_escolhida --;

              if(aux_task_escolhida < min_task_logica)
              aux_task_escolhida = min_task_logica;
            }
          // ===============================================================
          
          // --- Diminui escolha da entrada 1 --- ==========================
          if(aux_escolha_IN1)  
            { 
              aux_IN1_escolhida --;

              if(aux_IN1_escolhida < min_escolha_entradas)
              aux_IN1_escolhida = min_escolha_entradas;
            }
          // ===============================================================
          
          // --- Diminui escolha da entrada 2 --- ==========================
          if(aux_escolha_IN2)  
            { 
              aux_IN2_escolhida --;

              if(aux_IN2_escolhida < min_escolha_entradas)
              aux_IN2_escolhida = min_escolha_entradas;
            }
          // ===============================================================

          // --- Diminui escolha da operação 1 --- =========================
          if(aux_escolha_OP1)  
            { 
              aux_OP1_escolhida --;

              if(aux_OP1_escolhida < min_escolha_operacoes)
              aux_OP1_escolhida = min_escolha_operacoes;
            }
          // ===============================================================

          // --- Diminui escolha da operação 2 --- =========================
          if(aux_escolha_OP2)  
            { 
              aux_OP2_escolhida --;

              if(aux_OP2_escolhida < min_escolha_operacoes)
              aux_OP2_escolhida = min_escolha_operacoes;
            }
          // ===============================================================                                                             
      }

      if(!digitalRead(bt_ok))  aux_bt_ok  = 1;                             
      if(digitalRead(bt_ok) && aux_bt_ok)                                  
      {
       
        aux_bt_ok = 0;
        
          if(!aux_bt_ok)
          menu_number ++;
          if(menu_number > Max_itens_menu)  
          menu_number = 1;
          delay(150);
          
          if(aux_escolha_OK == 1){
            
                Serial.println("ENVIA DADOS ");
                delay(5000);  
            
          }                                                                             
      }
      

<<<<<<< HEAD
    

  

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
=======
      Serial.println("+...-...ok ");
      Serial.printf("CONFIORMA: %d \n", aux_confirma);
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22

    // --- Mostra o menu --- ===============================================
    switch(menu_number)
    {
      case 1:
              Serial.printf("Escolha Tarefa: %d \n", aux_task_escolhida);
              aux_escolha_task = 1;
              aux_escolha_IN1 = 0;
              aux_escolha_IN2 = 0;
              aux_escolha_OP1 = 0;
              aux_escolha_OP2 = 0;
              aux_escolha_OK = 0;                                 
              break;
      case 2:
              Serial.print("Config_IN1: ");
              menu_entradas = aux_IN1_escolhida;
              aux_escolha_task = 0;
              aux_escolha_IN1 = 1;
              aux_escolha_IN2 = 0;
              aux_escolha_OP1 = 0; 
              aux_escolha_OP2 = 0;
              aux_escolha_OK = 0;                                                      
              break;
      case 3:
              Serial.print("Config_IN2: ");
              menu_entradas = aux_IN2_escolhida;
              aux_escolha_task = 0;
              aux_escolha_IN1 = 0;
              aux_escolha_IN2 = 1;
              aux_escolha_OP1 = 0; 
              aux_escolha_OP2 = 0;
              aux_escolha_OK = 0;                                                       
              break;
      case 4:
              Serial.print("Config_OP1: ");
              menu_operacoes = aux_OP1_escolhida;
              aux_escolha_task = 0;
              aux_escolha_IN1 = 0;
              aux_escolha_IN2 = 0;
              aux_escolha_OP1 = 1; 
              aux_escolha_OP2 = 0;
              aux_escolha_OK = 0;                                                       
              break;
      case 5:
              Serial.print("Config_OP2: ");
              menu_operacoes = aux_OP2_escolhida;
              aux_escolha_task = 0;
              aux_escolha_IN1 = 0;
              aux_escolha_IN2 = 0;
              aux_escolha_OP1 = 0; 
              aux_escolha_OP2 = 1;
              aux_escolha_OK = 0;                                                      
              break;
    case 6:
              Serial.print("Pressione OK para enviar a lógica.");
              menu_operacoes = 0;
              aux_escolha_task = 0;
              aux_escolha_IN1 = 0;
              aux_escolha_IN2 = 0;
              aux_escolha_OP1 = 0; 
              aux_escolha_OP2 = 0;
              aux_escolha_OK = 1;                                                      
              break;
    }
    // =====================================================================

    // --- Mostra as opções para entrada --- ===============================
    if(aux_escolha_IN1 || aux_escolha_IN2)
      {
      switch(menu_entradas)
        {
          case 1:
                  Serial.println("Nada");                                                     
                  break;
          case 2:
                  Serial.println("IN1");                                                      
                  break;
          case 3:
                  Serial.println("IN2");                                                      
                  break;
          case 4:
                  Serial.println("IN3");                                                      
                  break;
          case 5:
                  Serial.println("IN4");                                                      
                  break;
          case 6:
                  Serial.println("ANALOG_IN1");
                  break;
        }
      }
    // =====================================================================

    // --- Mostra as opções para operações --- =============================
    if(aux_escolha_OP1 || aux_escolha_OP2)
      {
      switch(menu_operacoes)
        {
          case 1:
                  Serial.println("Nada");                                                     
                  break;
          case 2:
                  Serial.println("AND");                                                      
                  break;
          case 3:
                  Serial.println("OR");                                                      
                  break;
          case 4:
                  Serial.println("NOT");                                                 
                  break;
          case 5:
                  Serial.println("DELAY");                                                      
                  break;
        }
      }
    // =====================================================================

    // --- Ajusta tempo de delay---
    if(menu_operacoes == 5)
    {
    int valor = analogRead(a_in_01);
    int valor_tempo = map(valor, valorMinimo, valorMaximo, valorMinimoMapeado, valorMaximoMapeado);
    }

    // --- Ajusta Threshold ---
    if(menu_entradas == 6)
    {
    int valor_Threshold = analogRead(a_in_01);
    float valor_Map_threshold = map(valor_Threshold, valor_minimo_threshold, valor_maximo_threshold, valor_minimo_map_threshold, valor_maximo_map_threshold) / 1000.0;
    }


    /*//Variável para a fila 1 se "aux_task_escolhida == 1"
    //  -aux_IN1_escolhida
        -aux_IN2_escolhida
        -aux_OP1_escolhida
        -aux_OP2_escolhida
        -valor_tempo
        -valor_Map_threshold

    */
    //xQueueSendToBack(integerQueue1, &valor_Map_threshold, 0);

    xSemaphoreTake(xMutex1,portMAX_DELAY);
    if(digitalRead(in_01))
      {
        aux_volat_IN1_task1 = 1;
      }
      else
        {
          aux_volat_IN1_task1 = 0;
        }
    xSemaphoreGive(xMutex1);

    xSemaphoreTake(xMutex2,portMAX_DELAY);
    if(digitalRead(in_02))
      {
        aux_volat_IN2_task1 = 1;
      }
      else
        {
          aux_volat_IN2_task1 = 0;
        }
    xSemaphoreGive(xMutex2);

    xSemaphoreTake(xMutex3,portMAX_DELAY);
    if(digitalRead(in_03))
      {
        aux_volat_IN3_task1 = 1;
      }
      else
        {
          aux_volat_IN3_task1 = 0;
        }
    xSemaphoreGive(xMutex3);

    xSemaphoreTake(xMutex4,portMAX_DELAY);
    if(digitalRead(in_04))
      {
        aux_volat_IN4_task1 = 1;
      }
      else
        {
          aux_volat_IN4_task1 = 0;
        }
    xSemaphoreGive(xMutex4);

    xSemaphoreTake(xMutex5,portMAX_DELAY);
    valor_analogica = analogRead(a_in_01);
    aux_volat_a0_task1 = ((valor_analogica/4095.0)*3.3);
    xSemaphoreGive(xMutex5);
    
    delay(500);
  }
}

void task_logica1(void*parametro)
{  
  while(1)
  {
    //recebe parametros da fila
    /*int receiveValue;
    if(xQueueReceive(integerQueue1, &receiveValue, portMAX_DELAY))
    {
      Serial.print(receiveValue);
    }*/

    xSemaphoreTake(xMutex1,portMAX_DELAY);

    //Teste leitura entrada IN1 pela task
    if(aux_volat_IN1_task1)
      {
        Serial.println("Mutex");
      }                         
    
<<<<<<< HEAD
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
=======
    xSemaphoreGive(xMutex1);
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22

    delay(500);
  }
}

void setup() 
{

//==========================================================================
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
  pinMode(a_in_01, INPUT);

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
<<<<<<< HEAD


//inicializa o display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();


=======
  xMutex5 = xSemaphoreCreateMutex();

// --- Criação das filas ---================================================
  integerQueue1 = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                              );
  integerQueue2 = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                              );
  integerQueue3 = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                              );
  integerQueue4 = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                              );
//==========================================================================
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22

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
=======

  //Cria tarefa 2
  xTaskCreatePinnedToCore(
              task_logica1,   //Tarefa
              "task_logica1", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              5,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22
  
}

// the loop function runs over and over again forever
void loop() 
{ 
<<<<<<< HEAD

}
=======
}
>>>>>>> 37fbb292b3fb5ee51aa5c769150f2d9f258dae22
