#include <Servo.h>
#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;
Servo myservo;  

int potpin = 0;  
int val;    
int E2 = 5;
int M2 = 4;

void setup() {
  myservo.attach(9);  
  Serial.begin(115200);
  matrix.begin();
  pinMode(M2, OUTPUT);
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

int value;
for(value = 0 ; value <= 255; value+=5)
  {
    digitalWrite(M2,HIGH);
    analogWrite(E2, value);   //PWM Speed Control
    delay(30);
  }

  matrix.loadFrame(heart);

}