#include <Servo.h>
#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;
Servo myservo;  

int potpin = 0;  
int val;    
int E2 = 5;
int M2 = 4;
int motor_button = 2;
int motor_speed = 6;

void setup() {
  myservo.attach(9);  
  Serial.begin(115200);
  matrix.begin();
  pinMode(M2, OUTPUT);
  pinMode(motor_button, INPUT_PULLUP);
  pinMode(motor_speed, INPUT_PULLDOWN);
}

const uint32_t heart[] = {
  0x0001B024,
  0x82081100,
  0xA0040000
};


void loop() {
  val = analogRead(potpin);            
  val = map(val, 0, 1023, 0, 300);     
  myservo.write(val);                  
  delay(15);                           


  if(digitalRead(motor_speed) == HIGH){
    analogWrite(E2, 150);
  }
    else{
      analogWrite(E2, 0);
    }

  digitalWrite(M2, LOW);
  /*if(digitalRead(motor_button) == HIGH){
    digitalWrite(M2, HIGH);
  }
    else{
      digitalWrite(M2, LOW);
    }*/
  

  matrix.loadFrame(heart);

}