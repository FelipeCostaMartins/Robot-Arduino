#include <Servo.h>

Servo myservo;
Servo myservo2;  

int pos = 70; 
int speed = 100;
int low_limit = 70;
int high_limit = 120;

int zero1 = 98;
int zero2 = 90;
int move = 0;

void setup() {
  // Serial comum para comunicação com o Computador (Monitor Serial)
  Serial.begin(9600);
  
  // Serial1 para comunicação com o Bluetooth (Pinos 18 e 19 no Mega)
  Serial1.begin(9600); 

  myservo.attach(9);
  myservo2.attach(10);

  myservo.write(zero1);
  myservo2.write(zero2);
  
  Serial.println("Sistema Iniciado via Bluetooth no Serial1");
}

void loop() {
  app(); // interpretation of commands received from the LOFI Control App
}

void forward() {
  myservo.write(zero1 + 22);
  delay(speed);
  myservo2.write(zero2 - 20);
  delay(speed);
  myservo.write(zero1 - 21);
  delay(speed);
  myservo2.write(zero2 + 20);
  delay(speed);
}

void left() {
  myservo.write(zero1 - 40);
  delay(speed);
  myservo2.write(zero2 - 20);
  delay(speed);
  myservo.write(zero1 + 20);
  delay(speed);
  myservo2.write(zero2 + 20);
  delay(speed * 2);
}

void back(int speed) {
  myservo.write(zero1 - 20);
  delay(speed);
  myservo2.write(zero1 - 20);
  delay(speed);
  myservo.write(zero1 + 20);
  delay(speed);
  myservo2.write(zero1 + 20);
  delay(speed);
}

void right(int speed) {
  myservo.write(zero1 + 40);
  delay(speed);
  myservo2.write(zero2 + 20);
  delay(speed);
  myservo.write(zero1 - 20);
  delay(speed);
  myservo2.write(zero2 - 20);
  delay(speed * 2);
}

void happy() {
  int swing = 12;
  for (pos = zero1 - swing; pos <= zero1 + swing; pos += 1) { 
    myservo.write(pos);  
    delay(5);           
  }
  for (pos = zero1 + swing; pos >= zero1 - swing; pos -= 1) {  
    myservo.write(pos);                                
    delay(5);                                          
  }
}

void app() {
  // MUDANÇA AQUI: Ler do Serial1 (Bluetooth) e não do Serial (USB)
  if (Serial1.available() > 0) {
    move = Serial1.read();
    
    // Debug: Mostra no computador o que o Bluetooth recebeu
    Serial.print("Comando recebido: ");
    Serial.println(move);
  }

  // Nota: Se o app envia texto, '1' é diferente do numero 1.
  // Se não funcionar, tente trocar 1 por '1' (com aspas simples) nos ifs abaixo.

  if (move == 1) {
    forward();
    move = 0; // Reseta para não ficar repetindo infinitamente se não for a intenção
  }

  if (move == 2) {
    left();
    move = 0;
  }

  if (move == 3) {
    right(speed);
    move = 0;
  }

  if (move == 4) {
    back(200);
    move = 0;
  }

  if (move == 5) {
    happy();
    move = 0;
  }

  if (move == 0) {
    myservo.write(zero1);
    myservo2.write(zero2);
  }
}