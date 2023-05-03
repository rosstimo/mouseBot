#include <HCSR04.h>

byte triggerPin = A0;
byte echoCount = 3;
byte* echoPins = new byte[echoCount] { A1, A2, A3 };
// human readable sensor valu labels
const int frontSensor = 0;
const int leftSensor = 1;
const int rightSensor = 2;


//drive pin assignments
const int forwardPin = 9;
const int reversePin = 8;
const int leftPin = 10;
const int rightPin = 11;

// current sensor values to the nearest cm
int leftDistance = 0;
int rightDistance = 0;
int frontDistance = 0;

// decision limits
const int danger = 50;
int onTime = 100;

//debug switch enable serial message output serial output
boolean debug = false;
String debugMessage = "";


void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  pinMode(forwardPin, OUTPUT);
  pinMode(reversePin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
}

String forward () {
  digitalWrite(forwardPin, HIGH); 
  digitalWrite(reversePin, LOW); 
  return "forward ";
}

String reverse () {
  digitalWrite(forwardPin, LOW); 
  digitalWrite(reversePin, HIGH); 
  return "reverse ";
}

String brake () {
  digitalWrite(forwardPin, HIGH); 
  digitalWrite(reversePin, HIGH);
  return "brake ";
}

String left () {
  digitalWrite(rightPin,LOW);      
  digitalWrite(leftPin,HIGH);
  return "left ";
}

String right () {
  digitalWrite(rightPin,HIGH);      
  digitalWrite(leftPin,LOW);
  return "right ";
}

String straight () {
  digitalWrite(rightPin,LOW);      
  digitalWrite(leftPin,LOW);
  return "straight ";
}

String allStop () {
  digitalWrite(forwardPin, LOW); 
  digitalWrite(reversePin, LOW); 
  digitalWrite(forwardPin, LOW); 
  digitalWrite(reversePin, LOW); 
  return "stop ";
}

//make out of range distance obsurdly large
//instead of -1
int fixOutOfRange(double distance) {
  if (distance <= 0) {
    distance = 1000;
  }
  return int(distance);
}


void loop () {
  debugMessage = "";
  //allStop();
  
  double* distances = HCSR04.measureDistanceCm();  
  frontDistance = fixOutOfRange(distances[frontSensor]);
  leftDistance = fixOutOfRange(distances[leftSensor]);
  rightDistance = fixOutOfRange(distances[rightSensor]);
  
  //if forward is obstructed turn in the direction with the most clearance and go reverse
  if (frontDistance < danger ) {
    //debugMessage.concat(brake());
    //delay(onTime * 2);

    if (leftDistance >= rightDistance ) {
      debugMessage.concat(right());
      debugMessage.concat(reverse());
    }
    else {
      debugMessage.concat(left());
      debugMessage.concat(reverse());
    }
    
    delay(onTime * 2);
    //debugMessage.concat(allStop());
  }      
  //if too close on either side move away
  else if (leftDistance <= danger ) {      
    debugMessage.concat(right());
    debugMessage.concat(forward());     
  }
  else if (rightDistance <= danger ){
    debugMessage.concat(left());
    debugMessage.concat(forward());
  }
  else {
    debugMessage.concat(straight());
    debugMessage.concat(forward());
  }

  delay(onTime);

  if (debug) {
    Serial.print("left: ");
    Serial.print(leftDistance);
    Serial.print(" front: ");
    Serial.print(frontDistance);
    Serial.print(" right: ");
    Serial.println(rightDistance);
    Serial.println(debugMessage);
    delay(1000);
  }
}