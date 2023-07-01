//see: https://www.handsontec.com/dataspecs/HC-SR04-Ultrasonic.pdf

// define sensor pin variable. duplicate or remove as needed
const int frontTrigPin = 2;
const int leftTrigPin = 3;
const int rightTrigPin = 4;

const int frontEchoPin = 5;
const int leftEchoPin = 6;
const int rightEchoPin = 7;

const int frontRED_LED = 8;
const int leftRED_LED = 9;
const int rightRED_LED = 10;

const int frontGREEN_LED = 11;
const int leftGREEN_LED = 12;
const int rightGREEN_LED = 13;

/* 
microseconds since power on. 
rolls over after about 70 min @ 1,000,000 us per second
returns unsigned long
*/
long time = micros();

int timeOut = 60000;  // maximum time in microseconds to wait for valid measurement

bool debug = true;

int globalmax = 100;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  //set up trigger pins as outputs
  //used to start mesurement cycle
  pinMode(frontTrigPin, OUTPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(rightTrigPin, OUTPUT);

  //set up echo pins as inputs
  //polled during measurment cycle to determine end of cycle
  pinMode(frontEchoPin, INPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);

  pinMode(frontGREEN_LED, OUTPUT);
  pinMode(frontRED_LED, OUTPUT);
  pinMode(leftGREEN_LED, OUTPUT);
  pinMode(leftRED_LED, OUTPUT);
  pinMode(rightGREEN_LED, OUTPUT);
  pinMode(rightRED_LED, OUTPUT);
}

void loop() {
  // example polling pattern

  // measure front
  long duration = measure(frontEchoPin, frontTrigPin);
  indicate(frontGREEN_LED, frontRED_LED, cm(duration) , 25);

  if (debug == true) {
    sendSerial(duration);
  }

  // measure right
  // measure front
  // measure left
}

// a short (~10us) pulse will initiate a new measurement cycle
void sendPing(int pingPin) {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
}

bool echoPinState(int echoPin) {
  //the sensor will drive the echopin high at the start of a measurment cycle
  //the echo pin drops low if it receives a sound echo back or upon timeout. (~38ms)
  return digitalRead(echoPin);
}

// return duration in microseconds
long measure(int echoPin, int triggerPin) {
  sendPing(triggerPin);
 return pulseIn(echoPin,HIGH);
 }


//return measurment in cm
long cm(long microseconds) {
  // speed of sound @ 20 degrees celsius is 343.4 m/s or 0.03434 cm/us
  // the total measured duration includes there and back so twice the time
  // so distance in centimeters equals 0.03434 times the time in microseconds divided by 2

  return microseconds  / 29 / 2;
}

// return inches
long in(long microseconds) {
  //return microseconds / 74 / 2;
  //return microseconds * (1/148)
  // cm * 0.393701 = inches
  return 0.393701 * cm(microseconds);
}

void indicate(int GREEN_LED, int RED_LED, int distance, int threashhold ) {
  if (distance <= threashhold) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  // else if (distance >= 2430) {
  //   digitalWrite(GREEN_LED, HIGH);
  //   digitalWrite(RED_LED, HIGH);      
  // }
  else if (distance >= globalmax) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);    
  }
  else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
}

// write values to serial port
void sendSerial(long duration) {
  Serial.print(in(duration));
  Serial.print("in, ");
  Serial.print(cm(duration));
  Serial.print("cm");
  Serial.println();
}
