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

volatile int    aux_volat_IN1_task1 = 0,
                aux_volat_IN2_task1 = 0,
                aux_volat_IN3_task1 = 0,
                aux_volat_IN4_task1 = 0;

volatile float  aux_volat_a0_task1 = 0;

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

TickType_t xTimeBefore, xTotalTimeSuspended;

SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;
SemaphoreHandle_t xMutex3;
SemaphoreHandle_t xMutex4;
SemaphoreHandle_t xMutex5;

void task_ihm_btn_display(void*parametro)
{
  while(1)
  { 
      int valor_analogica,
          enviando_valores;

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
                enviando_valores = 1;
                delay(500);  
            
          }                                                                             
      }
      

      Serial.println("+...-...ok ");

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
    if(enviando_valores)
    {
      int tamanho_fila = 4;
      int valores[] = {aux_IN1_escolhida, aux_IN2_escolhida, aux_OP1_escolhida, aux_OP2_escolhida};

      for (int i = 0; i < tamanho_fila; i++) 
      {
        if(aux_task_escolhida == 1)
        {
          xQueueSend(integerQueue1, &valores[i], portMAX_DELAY);
          vTaskDelay(pdMS_TO_TICKS(100)); // Atraso de 1 segundo entre cada envio
        }

        if(aux_task_escolhida == 2)
        {
          xQueueSend(integerQueue2, &valores[i], portMAX_DELAY);
          vTaskDelay(pdMS_TO_TICKS(1000)); // Atraso de 1 segundo entre cada envio
        }

        if(aux_task_escolhida == 3)
        {
          xQueueSend(integerQueue3, &valores[i], portMAX_DELAY);
          vTaskDelay(pdMS_TO_TICKS(1000)); // Atraso de 1 segundo entre cada envio
        }

        if(aux_task_escolhida == 4)
        {
          xQueueSend(integerQueue4, &valores[i], portMAX_DELAY);
          vTaskDelay(pdMS_TO_TICKS(1000)); // Atraso de 1 segundo entre cada envio
        }
      }
      // --- Encerra o envio dos dados --- ==============================================
      enviando_valores      = 0;
      //=================================================================================

      // --- Retorna a configuração original para a lógica --- ==========================
      aux_task_escolhida    = 1;
      aux_IN1_escolhida     = 1;
      aux_IN2_escolhida     = 1;
      aux_OP1_escolhida     = 1;
      aux_OP2_escolhida     = 1;
      //=================================================================================
    }

    xSemaphoreTake(xMutex1,portMAX_DELAY);

    if(digitalRead(in_01))
      {
        aux_volat_IN1_task1 = 1;
      }
      else
        {
          aux_volat_IN1_task1 = 0;
        }

    if(digitalRead(in_02))
      {
        aux_volat_IN2_task1 = 1;
      }
      else
        {
          aux_volat_IN2_task1 = 0;
        }

    if(digitalRead(in_03))
      {
        aux_volat_IN3_task1 = 1;
      }
      else
        {
          aux_volat_IN3_task1 = 0;
        }

    if(digitalRead(in_04))
      {
        aux_volat_IN4_task1 = 1;
      }
      else
        {
          aux_volat_IN4_task1 = 0;
        }

    valor_analogica = analogRead(a_in_01);
    aux_volat_a0_task1 = ((valor_analogica/4095.0)*3.3);
    
    xSemaphoreGive(xMutex1);

    delay(500);
  }
}

void task_logica1(void*parametro)
{  
  while(1)
  {
    xSemaphoreTake(xMutex1,portMAX_DELAY);

    //Teste leitura entrada IN1 pela task
    if(aux_volat_IN1_task1)
      {
        Serial.println("Mutex");
        //Serial.println(valor1);
      }                         
    
    xSemaphoreGive(xMutex1);

    int aux1,
        aux2,
        aux3,
        aux4;

    int tamanho_fila = 4;
    
      int valoresRecebidos[4];

    if (uxQueueMessagesWaiting(integerQueue1) > 0)
    {
      for (int i = 0; i < tamanho_fila; i++)
        {      
        int valorRecebido;

          xQueueReceive(integerQueue1, &valorRecebido, pdMS_TO_TICKS(1000));
          valoresRecebidos[i] = valorRecebido;        
        }
    }    

    
    Serial.print("Valor recebido1: ");
    Serial.println(valoresRecebidos[0]);
    Serial.print("Valor recebido2: ");
    Serial.println(valoresRecebidos[1]);
    Serial.print("Valor recebido3: ");
    Serial.println(valoresRecebidos[2]);
    Serial.print("Valor recebido4: ");
    Serial.println(valoresRecebidos[3]);
    
    delay(500);
  }
}

void task_logica2(void*parametro)
{  
  while(1)
  {
    
    int valorRecebido;
    if (xQueueReceive(integerQueue2, &valorRecebido, pdMS_TO_TICKS(100))) {
            // Processar o valor recebido
            printf("Valor recebido: %d\n", valorRecebido);
        }
   

    delay(500);
  }
}

void task_logica3(void*parametro)
{  
  while(1)
  {
    
    int valorRecebido;
    if (xQueueReceive(integerQueue3, &valorRecebido, pdMS_TO_TICKS(100))) {
            // Processar o valor recebido
            printf("Valor recebido: %d\n", valorRecebido);
        }
   

    delay(500);
  }
}

void task_logica4(void*parametro)
{  
  while(1)
  {
    
    int valorRecebido;
    if (xQueueReceive(integerQueue4, &valorRecebido, pdMS_TO_TICKS(100))) {
            // Processar o valor recebido
            printf("Valor recebido: %d\n", valorRecebido);
        }
   

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

  // --- Cria tarefa 1 - Tarefa display e leitura de botões --- ============
  xTaskCreatePinnedToCore(
              task_ihm_btn_display,   //Tarefa
              "task_ihm_btn_display", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              3,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
//==========================================================================

  // --- Cria tarefa 1 - Tarefa da lógica 1 --- ============================
  xTaskCreatePinnedToCore(
              task_logica1,   //Tarefa
              "task_logica1", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              5,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
//==========================================================================
  
  // --- Cria tarefa 2 - Tarefa da lógica 2 --- ============================
  xTaskCreatePinnedToCore(
              task_logica2,   //Tarefa
              "task_logica2", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              5,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
//==========================================================================

  // --- Cria tarefa 3 - Tarefa da lógica 3 --- ============================
  xTaskCreatePinnedToCore(
              task_logica3,   //Tarefa
              "task_logica3", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              5,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
//==========================================================================
  
  // --- Cria tarefa 4 - Tarefa da lógica 4 --- ============================
  xTaskCreatePinnedToCore(
              task_logica4,   //Tarefa
              "task_logica4", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              5,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
  //==========================================================================

}

// the loop function runs over and over again forever
void loop() 
{ 
}
