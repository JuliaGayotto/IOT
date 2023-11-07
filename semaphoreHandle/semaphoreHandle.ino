TaskHandle_t task1;
TaskHandle_t task2;

SemaphoreHandle_t mutex;

float temp = 0.0;
float umi = 0.0;

void minhaTask1(void *pvParameters)
{
  Serial.println("Comecou a Task1");
  while(true){
    //regiao crítica
    xSemaphoreTake(mutex, portMAX_DELAY);
    temp = temp +0.24;
    umi = umi + 0.51;
    xSemaphoreGive(mutex);
    delay(1300);
  }
}

void minhaTask2(void *pvParameters)
{
  Serial.println("Comecou a Task2");
  while(true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    temp = temp - 0.09;
    umi = umi - 0.23;
    xSemaphoreGive(mutex);
    delay(800);
  }
}

void setup() {
  Serial.begin(115200);

  mutex = xSemaphoreCreateMutex();

  if (mutex == NULL)
    Serial.println("Erro ao criar o mutex");

  Serial.println("Criando a task 1");
  xTaskCreatePinnedToCore(
    minhaTask1, //funcao da task
    "MinhaTask1", //nome da task
    1000, //tamanho da task
    NULL, //parametros task
    1, //prioridade da task
    &task1, //task handle
    0 //core (loop = 1)
    );

  Serial.println("Criando a task 2");
  xTaskCreatePinnedToCore(
    minhaTask2, //funcao da task
    "MinhaTask2", //nome da task
    1000, //tamanho da task
    NULL, //parametros task
    1, //prioridade da task
    &task2, //task handle
    1 //core (loop = 1)
    );
}

void loop() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  Serial.print("Temperatura ");
  Serial.println(temp);
  Serial.print("Umidade ");
  Serial.println(umi);
  xSemaphoreGive(mutex);
  delay(1000);
}
