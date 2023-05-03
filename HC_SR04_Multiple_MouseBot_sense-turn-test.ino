#include <HCSR04.h>

byte triggerPin = A0;
byte echoCount = 3;
byte* echoPins = new byte[echoCount] { A1, A2, A3 };
int wait = 100; //time between measurments

const int forwardPin = 9;
const int reversePin = 8;
const int leftPin = 10;
const int rightPin = 11;

const int frontSensore = 0;
const int leftSensor = 1;
const int rightSensor = 2;

//if front sensor >=100 cm go forward
//if left sensor >= right  go left
//if right sensor >= left go right
//otherwise go straight
//if front < 100 cm turn in the direction 
//with the greatest distance


void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  pinMode(forwardPin, OUTPUT);
  pinMode(reversePin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
}

void front () {
  double* distances = HCSR04.measureDistanceCm();
  Serial.print("front: ");
  Serial.print(distances[0]);
  Serial.println("cm");

}

void left () {
  double* distances = HCSR04.measureDistanceCm();
  Serial.print("left: ");
  Serial.print(distances[1]);
  Serial.println("cm");
}

void right () {
  double* distances = HCSR04.measureDistanceCm();
  Serial.print("right: ");
  Serial.print(distances[2]);
  Serial.println("cm");
}

void loop () {

 double* distances = HCSR04.measureDistanceCm();  

    if (distances[leftSensor] >= (distances[rightSensor] * 1.2) ) {
      // go left
      digitalWrite(rightPin,LOW);      
      digitalWrite(leftPin,HIGH);      
    }
    else if (distances[rightSensor] >= (distances[leftSensor] * 1.2) ){
      // go right
      digitalWrite(leftPin,LOW);
      digitalWrite(rightPin,HIGH);
    }
    else {
      // go straight
      digitalWrite(leftPin,LOW);
      digitalWrite(rightPin,LOW);
    }
    

  delay(wait);
}