#include <WiFi.h>
#include "time.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

TaskHandle_t taskColeta;
TaskHandle_t taskMonWiFi;

SemaphoreHandle_t mutex;

typedef struct {
  float temp;
  float umi;
  float dirvento;
  float velvento;
  float pressao;
} Medidas_t;

Medidas_t med;
DynamicJsonDocument post(1024);
String uid;

String serverName = "http://postman-echo.com/post";

//Configs do wifi
char *ssid = "Júlia Gayotto";
char *pwd = "senha aqui";

//configs do servidor NTP
char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

void tColeta(void *pvParameters)
{
  Serial.println("Task de Coleta de Dados");
  while(true){
    //regiao crítica
    xSemaphoreTake(mutex, portMAX_DELAY);
    med.temp = random(100,400) / 10.0;
    med.umi = random (20, 99);
    med.dirvento = random(0,359);
    med.velvento = random(100,1000) / 10.0;
    med.pressao = random(100000,101325) / 10.0;
    xSemaphoreGive(mutex);
    delay(1000);
  }
}

void connectWiFi()
{
  Serial.print("Conectando o WiFI ");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void tTemInternet(void *pvParameters)
{
  Serial.println("Task Monitor de Internet");
  while(true){
    if (WiFi.status() != WL_CONNECTED)
      connectWiFi();
    delay(30000);
  }
}

void setup() {
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");

  mutex = xSemaphoreCreateMutex();
  if (mutex == NULL)
    Serial.println("Erro ao criar o mutex");

  Serial.println("Criando a task de Coleta");
  xTaskCreatePinnedToCore(
    tColeta, //funcao da task
    "TaskColeta", //nome da task
    1000, //tamanho da task
    NULL, //parametros task
    1, //prioridade da task
    &taskColeta, //task handle
    0 //core (loop = 1)
    );

  WiFi.begin(ssid, pwd);

  Serial.println("Criando a task 2");
  xTaskCreatePinnedToCore(
    tTemInternet, //funcao da task
    "MonitoraWiFi", //nome da task
    1000, //tamanho da task
    NULL, //parametros task
    1, //prioridade da task
    &taskMonWiFi, //task handle
    1 //core (loop = 1)
    );
}

void sincronizaTempo(void)
{
  //Configurando o tempo
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Erro ao acessar o servidor NTP"); 
  }
  else
  {
    Serial.print("Configurado Data/Hora ");
    Serial.println(time(&now));
  }
}

void loop() {
  if ((time(&now) % 120) == 0)
  {
    Serial.println("-->> Time to Trans");
    sincronizaTempo();
    xSemaphoreTake(mutex, portMAX_DELAY);
    post["uid"] = uid;
    post["unixtime"] = time(&now);
    post["temp"] = med.temp;
    post["umi"] = med.umi;
    post["dirvento"] = med.dirvento;
    post["velvento"] = med.velvento;
    post["pressao"] = med.pressao;
    xSemaphoreGive(mutex);

    //VAMOS TRANSMITIR EM HTTP POST
    WiFiClient wclient;
    HTTPClient http_post;

    http_post.begin(wclient, serverName);
    http_post.addHeader("Content-Type","application/json");
    http_post.addHeader("x-api-key","blablablabla");
  
    String tmp;
    serializeJson(post, tmp);
    int http_get_code = http_post.POST(tmp.c_str());

    Serial.print("\n\r HTTP CODE=");
    Serial.println(http_get_code);
    if (http_get_code > 0)
    {
      Serial.println(http_post.getString());
    }
    else
    {
      Serial.println("Erro ao executar o GET");
    }
  }
  delay(1000);
}
