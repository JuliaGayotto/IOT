// C++ code

#define RED 2
#define YELLOW 3
#define GREEN 4

#define VERMELHO 8
#define AMARELO 9
#define VERDE 10

#define BOTAO 5
#define PEDESTRE 6



void setup(){
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  pinMode(VERMELHO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  
  pinMode(BOTAO, INPUT);
  pinMode(PEDESTRE, OUTPUT);
}

int i = 0;
void loop(){
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(1000);
  
  
  if(i == 1){
    digitalWrite(PEDESTRE, HIGH);
    delay(2000);
    digitalWrite(PEDESTRE, LOW);
    delay(1000);
    i = 0;
  }
  
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  digitalWrite(VERMELHO, LOW);
  digitalWrite(AMARELO, LOW);
  digitalWrite(VERDE, HIGH);
  delay(3000);
  
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  digitalWrite(VERMELHO, LOW);
  digitalWrite(AMARELO, HIGH);
  digitalWrite(VERDE, LOW);
  delay(2000);
  
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  digitalWrite(VERMELHO, HIGH);
  digitalWrite(AMARELO, LOW);
  digitalWrite(VERDE, LOW);  
  delay(1000);
  
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  if(i == 1)
  {
    digitalWrite(PEDESTRE, HIGH);
    delay(2000);
    digitalWrite(PEDESTRE, LOW);
    delay(1000);
    i = 0;
  }
  
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(3000);
  
  
  if(digitalRead(BOTAO) == HIGH){
    i = 1;
  }
  
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW);
  delay(2000);

}