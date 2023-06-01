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
#define bt_parcial1 GPIO_NUM_23
#define bt_parcial2 GPIO_NUM_19

bool aux_bt_start = 0,
     aux_bt_stop = 0,
     aux_bt_parcial1 = 0,
     aux_bt_parcial2 = 0,
     aux_iniciar = 0;


SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;

void setup() 
{

//==========================================
  pinMode(bt_start, INPUT_PULLUP);                                                       
  pinMode(bt_stop, INPUT_PULLUP);                                                       
  pinMode(bt_parcial1, INPUT_PULLUP);
  pinMode(bt_parcial2, INPUT_PULLUP);                                                       

  Serial.begin(115200);
  delay(1000);

  //Cria tarefa 1
  xTaskCreate(
              task_tempo,   //Tarefa
              "task_tempo", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              3,          //Prioridade
              NULL        //Identificador da tarefa
              );

  //Cria tarefa 2
  xTaskCreate(
              task_btn,   //Tarefa
              "task_btn", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              2,          //Prioridade
              NULL        //Identificador da tarefa
              );
  
  
  //Cria tarefa 3
  xTaskCreate(
              task_display,   //Tarefa
              "task_display", //Nome da tarefa
              10000,      //Tamanho da pilha
              NULL,       //Parâmetro de entrada não passa nada
              1,          //Prioridade
              NULL        //Identificador da tarefa
              );
  
}

// the loop function runs over and over again forever
void loop() 
{
  //Serial.println("void loop");
  //delay(1000);
}

void task_tempo(void*parametro){
  int segundo = 0,
      minuto = 0,
      hora = 0;

  while(1)
  {
    
    if(segundo < 60){
      segundo++;
    }else{
      segundo = 0;
      if (minuto < 60){
        minuto++;
      }else{
        minuto = 0;
        if (hora < 24){
          hora++;
        }else{
          hora = 0;
        }
      }
    }

  }
}

void task_btn(void*parametro)
{
  while(1)
  {
      if(!digitalRead(bt_start))  aux_bt_start  = 1;                             
      if(digitalRead(bt_start) && aux_bt_start)                                  
      {
        aux_bt_start = 0;                                                           
        aux_iniciar = 1;                   
      }

    for(int i=0; i<10; i++)
    {
    Serial.print("Funcao 2: ");
    Serial.println(i);
    delay(1000);
    }
    Serial.println("Funcao 2 terminada");
  }
}

void task_display(void*parametro)
{
  while(1)
  {
    for(int i=0; i<10; i++)
    {
    Serial.print("Funcao 3: ");
    Serial.println(i);
    delay(1000);
    }
    Serial.println("Funcao 3 terminada");
  }
}