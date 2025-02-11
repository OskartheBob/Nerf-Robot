#include <Servo.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h> 
#include <Wire.h>
#include <SPI.h>
#include <RunningAverage.h>

Servo myservo;  
Adafruit_MMA8451 mma = Adafruit_MMA8451();
RunningAverage myRa1(16);
RunningAverage myRa2(16);

int E2 = 5;
int M2 = 4;
int motor_button = 2;
int motor_speed = 6;

float average = 0;
long degrees = 0;

/*unsigned long previous_millis = 0;
void set_interval(unsigned long interval, void (*callback)()) {
  unsigned long current_millis = millis();
  if(current_millis - previous_millis >= interval){
    previous_millis = current_millis;
    callback();
  }
}*/

float mapfloat(float x, float in_min, float in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {
  myservo.attach(9);  
  Serial.begin(9600);
  pinMode(M2, OUTPUT);
  pinMode(motor_button, INPUT_PULLUP);
  pinMode(motor_speed, INPUT_PULLUP);

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);
}



void loop() {
  mma.read(); 
  sensors_event_t event; 
  mma.getEvent(&event);

  myRa1.addValue(event.acceleration.x);
  average = myRa1.getAverage();
  average = mapfloat(average, -10, 10, 0, 180);
  myRa2.addValue(average);
  degrees = myRa2.getAverage();
  Serial.println(degrees);
    
  myservo.write(degrees); 
  delay(15);
}