#include <Servo.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h> 
#include <Wire.h>
#include <SPI.h>

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
  pinMode(M2, OUTPUT);
  pinMode(motor_button, INPUT_PULLUP);
  pinMode(motor_speed, INPUT_PULLUP);
}



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
  

}