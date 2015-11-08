#include <NewPing.h>

//#define TRIGGER_PIN 3
//#define ECHO_PIN 2
//#define MAX_DISTANCE 200 //testBoxLength

NewPing sonar(3, 2, 200);

//global variables
int boxLength = 17; 
bool last = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);

}

void loop () {
  //put your main code here, to run repeatedly:
  int ping = sonar.ping_cm();
  if (ping < boxLength && !last) {
      //Serial.println(ping);
      Serial.write('1');
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      last = true;
    }
   else if (ping >= boxLength && last) {
      Serial.write('0');
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      last = false;
  }
  delay(250);
}

