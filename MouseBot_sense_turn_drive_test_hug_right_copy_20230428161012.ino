#include <HCSR04.h>

byte triggerPin = A0;
byte echoCount = 3;
byte* echoPins = new byte[echoCount] { A1, A2, A3 };
int wait = 20; //time between measurments

const int forwardPin = 9;
const int reversePin = 8;
const int leftPin = 10;
const int rightPin = 11;

const int frontSensor = 0;
const int leftSensor = 1;
const int rightSensor = 2;

int leftDistance = 0;
int rightDistance = 0;
int frontDistance = 0;

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



void loop () {

  double* distances = HCSR04.measureDistanceCm();  

  //make out of range obsurdly large
  if (distances[leftSensor] <= 0){
    leftDistance = 1000;
  }
  else {
    leftDistance =  int(distances[leftSensor]);
  }

  if (distances[rightSensor] <= 0){
    rightDistance = 1000;
  }
  else {
    rightDistance =  int(distances[rightSensor]);
  }

    if (distances[frontSensor] <= 0){
    frontDistance = 1000;
  }
  else {
    frontDistance =  int(distances[frontSensor]);
  }

  Serial.print("left: ");
  Serial.print(leftDistance);
  Serial.print("cm |");
  Serial.print("front: ");
  Serial.print(frontDistance);
  Serial.print("cm |");
  Serial.print("right: ");
  Serial.print(rightDistance);
  Serial.println("cm");

    //if forward is obstructed turn in the direction with the most clearance
    if (frontDistance < 100 ) {
      Serial.println("Danger!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      // go left
      digitalWrite(rightPin,LOW);      
      digitalWrite(leftPin,HIGH);
      analogWrite(forwardPin, 0);

    }      
  //if forward is clear go straight or re-center
    else if (rightDistance > 100) {
      // go right
      Serial.println("Go Right");
      digitalWrite(leftPin,LOW);
      digitalWrite(rightPin,HIGH);
    }
    else {
      // go straight
      Serial.println("Go Straight");
      digitalWrite(leftPin,LOW);
      digitalWrite(rightPin,LOW);
    }
    analogWrite(forwardPin, 128);
  
  delay(wait);
}