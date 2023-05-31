/*CABEÇALHO*/


//Variáveis globais de controle do cronometro
byte start = 0;
byte stop = 0;
byte reset = 0;

//Variáveis globais das parciais, com 3 posições cada
char p1[3];
char p2[3];

//Variáveis globais do tempo
int hora = 0;
int minuto = 0;
int segundo = 0;

//Mutex para proteção das variáveis
SemaphoreHandle_t xMutex01;
SemaphoreHandle_t xMutex02;


void task_tempo(void *pvParameters){
    while (true){
    xSemaphoreTake(xMutex01,portMAX_DELAY);
    Serial.print("Task 1: ");
    Serial.println(start);
    start =  start > 1 ? start-1 : start+1;
    delay(500);
    xSemaphoreGive(xMutex01);
    
    }
}

void task_btn(void *pvParameters){
    while (true){
    xSemaphoreTake(xMutex01,portMAX_DELAY);
    Serial.print("Task 2: ");
    Serial.println(start);
    start =  start > 1 ? start-1 : start+1;
    delay(500);
    xSemaphoreGive(xMutex01);
    
    }
}

void task_serial(void *pvParameters){
    while (true){
    xSemaphoreTake(xMutex01,portMAX_DELAY);
    Serial.print("Task 2: ");
    Serial.println(start);
    start =  start > 1 ? start-1 : start+1;
    delay(500);
    xSemaphoreGive(xMutex01);
    
    }
}

void setup(){
  Serial.begin(115200);
    xMutex01 = xSemaphoreCreateMutex();
    if(xMutex01 != NULL){
         xTaskCreatePinnedToCore(task_tempo, "Print1", 10000,NULL, 3, NULL,0);
         xTaskCreatePinnedToCore(task_btn, "Print2", 10000,NULL, 3, NULL,0);
         xTaskCreatePinnedToCore(task_serial, "Print2", 10000,NULL, 3, NULL,0);
    }
}

void loop(){
  //limbo
}