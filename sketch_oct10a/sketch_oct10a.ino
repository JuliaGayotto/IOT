#include <WiFi.h>
#define LED 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.print("Meu macaddress ->>>> ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Liga o LED");
  digitalWrite(LED, HIGH);
  delay(500);
  Serial.println("Desliga o LED");
  digitalWrite(LED, LOW);
  delay(500);
}
