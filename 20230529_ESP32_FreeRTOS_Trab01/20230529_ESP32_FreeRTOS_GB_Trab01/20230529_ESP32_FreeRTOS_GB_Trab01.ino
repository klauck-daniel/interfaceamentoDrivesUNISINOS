/* ===========================================================
   @Curso de Engenharia Elétrica e Engenharia da Computação
   @Tarefa2GB-Cronômetro parcial com FreeRTOS 
      
   Disciplina de Interfaceamento e Drivers
   
   Professor: Lúcio Rene Prade
   Autor: Daniel Klauck e Felipe Paloschi
==============================================================*/

//============================================================
// --- Mapeamento de Hardware ---
#define bt_start GPIO_NUM_21
#define bt_stop GPIO_NUM_22
#define bt_zerar GPIO_NUM_23
#define bt_parcial GPIO_NUM_19

volatile int hora = 0;
volatile int minuto = 0;
volatile int segundo = 0;

volatile int aux_iniciar = 0;
volatile int aux_zerar = 0;
volatile int aux_parcial = 0;

volatile int h = 0;
volatile int m = 0;
volatile int s = 0;

volatile int parcial1_h = 0;
volatile int parcial1_m = 0;
volatile int parcial1_s = 0;

volatile int parcial2_h = 0;
volatile int parcial2_m = 0;
volatile int parcial2_s = 0;

int aux_conta = 0;

bool aux_bt_start   = 0,
     aux_bt_stop    = 0,
     aux_bt_zerar   = 0,
     aux_bt_parcial = 0;

TickType_t xTimeBefore, xTotalTimeSuspended;

SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;

void task_btn(void*parametro)
{
  while(1)
  {
    xSemaphoreTake(xMutex1,portMAX_DELAY);

      if(!digitalRead(bt_start))  aux_bt_start  = 1;                             
      if(digitalRead(bt_start) && aux_bt_start)                                  
      {
        aux_bt_start = 0;                                                           
        aux_iniciar = 1;                   
      }

      if(!digitalRead(bt_stop))  aux_bt_stop  = 1;                             
      if(digitalRead(bt_stop) && aux_bt_stop)                                  
      {
        aux_bt_stop = 0;                                                           
        aux_iniciar = 0;                   
      }

      if(!digitalRead(bt_zerar))  aux_bt_zerar  = 1;                             
      if(digitalRead(bt_zerar) && aux_bt_zerar)                                  
      {
        aux_bt_zerar = 0;                                                           
        aux_zerar = 1;                   
      }

      if(!digitalRead(bt_parcial))  aux_bt_parcial  = 1;                             
      if(digitalRead(bt_parcial) && aux_bt_parcial)                                  
      {
        aux_bt_parcial = 0;                                                           
        aux_parcial = 1;                   
      }

    xSemaphoreGive(xMutex1);

    delay(500);
  }
}

void task_tempo(void*parametro)
{  
  while(1)
  {

    xTotalTimeSuspended = xTaskGetTickCount() - xTimeBefore;
    
    if (xTotalTimeSuspended >= 10)
          {
		  			xTimeBefore = xTaskGetTickCount();

		  			if (segundo < 60) 
              {segundo++;}
            else
              {
                segundo = 0;
		  			    if (minuto < 60)
                  {minuto++;}
                else
                  {
                    minuto = 0;
		  			        if (hora < 24) 
                      {hora++;}
                    else
                      {hora = 0;}
		  			      }
		  			  }
		  	  }

    xSemaphoreTake(xMutex1,portMAX_DELAY);
    xSemaphoreTake(xMutex2,portMAX_DELAY);

    if (aux_iniciar)
      {
			  h=hora;
			  m=minuto;
			  s=segundo;
		  }
      
    if (aux_zerar)
      {
			  hora = 0;
			  minuto = 0;
			  segundo = 0;

			  h=0;
			  m=0;
			  s=0;

			  parcial1_h = 0;
			  parcial1_m = 0;
			  parcial1_s = 0;

			  parcial2_h = 0;
			  parcial2_m = 0;
			  parcial2_s = 0;

			  aux_zerar = 0;
		  }
      
    if(aux_parcial)
      {
			  aux_conta++;
			  if (aux_conta == 1)
			    {
            parcial1_h = hora;
			      parcial1_m = minuto;
			      parcial1_s = segundo;

		  	    aux_parcial = 0;
			    }

			  if (aux_conta == 2)
			 		{
			 			aux_conta=0;

            parcial2_h = hora;
			      parcial2_m = minuto;
			      parcial2_s = segundo;

			 		  aux_parcial = 0;
			 			}
		  }
    
    xSemaphoreGive(xMutex1);
    xSemaphoreGive(xMutex2);

    delay(500);

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
  pinMode(bt_start, INPUT_PULLUP);                                                       
  pinMode(bt_stop, INPUT_PULLUP);                                                       
  pinMode(bt_zerar, INPUT_PULLUP);
  pinMode(bt_parcial, INPUT_PULLUP);                                                       

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

  //Cria tarefa 2
  xTaskCreatePinnedToCore(
              task_btn,   //Tarefa
              "task_btn", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              2,          //Prioridade
              NULL,
              0        //Identificador da tarefa
              );
  
  
  //Cria tarefa 3
  xTaskCreatePinnedToCore(
              task_display,   //Tarefa
              "task_display", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              1,          //Prioridade
              NULL,        //Identificador da tarefa
              0
              );
  
}

// the loop function runs over and over again forever
void loop() 
{ 
}