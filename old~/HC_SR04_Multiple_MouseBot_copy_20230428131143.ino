#include <HCSR04.h>

byte triggerPin = A0;
byte echoCount = 3;
byte* echoPins = new byte[echoCount] { A1, A2, A3 };
int wait = 1000; //time between measurments

const int forwardPin = 9;
const int reversePin = 8;
const int leftPin = 10;
const int rightPin = 11;


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
  digitalWrite(leftPin,HIGH);
  delay(wait);
  digitalWrite(leftPin,LOW);
  delay(wait);
  digitalWrite(rightPin,HIGH);
  delay(wait);
  digitalWrite(rightPin,LOW);
  delay(wait);
  digitalWrite(forwardPin,HIGH);
  delay(wait);
  digitalWrite(forwardPin,LOW);
  delay(wait);
  digitalWrite(reversePin,HIGH);
  delay(wait);
  digitalWrite(reversePin,LOW);
  delay(wait);
}