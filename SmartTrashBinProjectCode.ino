#include <Servo.h>
Servo myservo; 
#define ep1 2
#define tp1 3
#define ep2 4
#define tp2 5
#define buzzer 10
int duration1;
int distance1;
int duration2;
int distance2;
const unsigned long interval = 5000;
unsigned long previousTime = 0;
int pos =0;   


void setup() {
  pinMode(tp1, OUTPUT);
  pinMode(ep1, INPUT);
  
  pinMode(tp2, OUTPUT);
  pinMode(ep2, INPUT);

  pinMode(11, OUTPUT);  // red
  pinMode(12, OUTPUT);  // yellow
  pinMode(13, OUTPUT);  // green
  
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(tp1, LOW);
  delayMicroseconds(5);
  digitalWrite(tp1, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp1, LOW);
  duration1 = pulseIn(ep1, HIGH);
  distance1 = duration1 * 0.017;
  if (distance1 <= 10) {

      myservo.write(120);
    
  }

  else {
      myservo.write(0);    
  }

  

  digitalWrite(tp2, LOW);
  delayMicroseconds(5);
  digitalWrite(tp2, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp2, LOW);
  duration2 = pulseIn(ep2, HIGH);
  distance2 = duration2 * 0.017;

  //Serial.println(distance2);

  if (distance2 <= 10) {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    unsigned long currentTime = millis();

    if (currentTime-previousTime >= interval) {
      
      int i = 0;
      while (i < 2) {
        tone(buzzer, 450);
        delay(200);
        noTone(buzzer);
        delay(200);
        i++;
      }

      Serial.println("Dustbin no 2 is full! Please clean it");

      previousTime = currentTime;
    }
  }
  else if (distance2 <= 20) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  else {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
  delay(1000);
}
