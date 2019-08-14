#include <DS3231.h>
#include <Servo.h>
Servo myservo;

int pos = 0;
int Relay = 9;
DS3231 rtc(SDA, SCL);
Time t;

const int OnHour = 17;
const int OnMin = 35;
const int OnSec = 30;
const int OffHour = 17;
const int OffMin = 35;
const int OffSec = 45;

const int OnHour2 = 17;
const int OnMin2 = 36;
const int OnSec2 = 0;
const int OffHour2 = 17;
const int OffMin2 = 36;
const int OffSec2 = 15;

bool flag;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  myservo.attach(9);
  flag = 0;
}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" hours(h), ")
  Serial.print(t.min);
  Serial.print(" minute(m), ");
  Serial.print(t.sec);
  Serial.print(" seconds(s).");
  Serial.println(" ");
  delay(1000);
  if ((t.hour == OnHour && t.min == OnMin && t.sec == OnSec && flag == 0)||(t.hour == OnHour2 && t.min == OnMin2 && t.sec == OnSec2 && flag == 0))  {
    digitalWrite(Relay, HIGH);
    Serial.println("FOOD HOLE OPEN");
    for (pos = 0; pos <= 90; pos +=1) { // goes from 0 degrees to 90 degrees //change if we need to turn less
      //in steps of 1 degree
      myservo.write(pos); //servo goes to position 'pos'
      delay(10);  //waits 15 ms for servo to get there
    }
    flag = 1;
  }
  else if ((t.hour == OffHour && t.min == OffMin && t.sec == OffSec && flag == 1)||(t.hour == OffHour2 && t.min == OffMin2 && t.sec == OffSec2 && flag == 1)) {
    digitalWrite(Relay, LOW);
    Serial.println("FOOD HOLE CLOSED");
    for (pos = 90; pos >= 0; pos -=1) { //goes from 90 degrees to 0 degrees  //change this with the for loop 
      myservo.write(pos); // tell servo to go to 'pos'
      delay(10);  //waits 15ms for servo to get there
    }
    flag = 0;
  }
  
}
