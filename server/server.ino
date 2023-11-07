#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>

String uid;
char *ssid = "Júlia Gayotto";
char *pwd = "senha aqui";

char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

//String serverName = "http://postman-echo.com/Post";

String serverName = "http://192.168.111.74:5000/v0/dados";

void connectWifi() {
  Serial.print("conectando ");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  WiFi.begin(ssid, pwd);
  connectWifi();
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo)) {
    Serial.println("erro ao acessar o servidor ntp");
  } else {
    Serial.print("a hora é ");
    Serial.println(time(&now));
  }
}
float t = 12.0;
float u = 27.0;

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    if (!getLocalTime(&timeinfo)){
      Serial.println("erro ao conectar data/hora");
    }

    //HTTP POST
    WiFiClient wclient;
    HTTPClient http_post;

    http_post.begin(wclient, serverName);
    http_post.addHeader("Content-Type", "application/json");
    http_post.addHeader("x-api-key", "blablablabla");


    String tmp = "{\"uid\":\"" + uid + "\",\"unx\":" + time(&now) + ",\"temp\":" + t + ",\"umi\":" + u + "}";

    int http_get_code = http_post.POST(tmp.c_str());
    Serial.print("");
    Serial.print(http_get_code);

    if (http_get_code > 0){
      Serial.println(tmp);
      Serial.println(http_post.getString()); 
      }
    }
  else{
    Serial.println("nunca tem internet");
    connectWifi();
  }
  t = t+0.25;
  u = u+0.09;
  delay(30000);


}
