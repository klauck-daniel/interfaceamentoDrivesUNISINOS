byte my_shared_var = 1;
SemaphoreHandle_t xMutex;

void teste(void *pvParameters){
    while (true){
    xSemaphoreTake(xMutex,portMAX_DELAY);
    Serial.print("Task 1: ");
    Serial.println(my_shared_var);
    my_shared_var =  my_shared_var > 1 ? my_shared_var-1 : my_shared_var+1;
    delay(500);
    xSemaphoreGive(xMutex);
    
    }
}

void teste2(void *pvParameters){
    while (true){
    xSemaphoreTake(xMutex,portMAX_DELAY);
    Serial.print("Task 2: ");
    Serial.println(my_shared_var);
    my_shared_var =  my_shared_var > 1 ? my_shared_var-1 : my_shared_var+1;
    delay(500);
    xSemaphoreGive(xMutex);
    
    }
}

void setup(){
  Serial.begin(115200);
    xMutex = xSemaphoreCreateMutex();
    if(xMutex != NULL){
         xTaskCreatePinnedToCore(teste, "Print1", 10000,NULL, 3, NULL,0);
         xTaskCreatePinnedToCore(teste2, "Print2", 10000,NULL, 3, NULL,0);
    }
}

void loop(){
    delay(2000);
    Serial.println("batata");
}