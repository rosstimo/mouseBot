//see: https://www.handsontec.com/dataspecs/HC-SR04-Ultrasonic.pdf

        /*

   TX   --|D0/TX     VIN|<-   +5V
   RX   --|D1/RX     GND|--   GND
        --|RST       RST|--
   GND  --|GND        5V|->
   FT   --|D2     D21/A7|--   Button+
   FE   --|D3~    D20/A6|--   Buzz+
   FG   --|D4     D19/A5|--   SCL
   MR   --|D5~    D18/A4|--   SDA
   ML   --|D6~    D17/A3|--   LG
   FR   --|D7     D16/A2|--   LR
   RT   --|D8     D15/A1|--   LE
   MR   --|D9~    D14/A0|--   LT
   MF   --|D10~     AREF|--   
   RE   --|D11~     3.3V|->
   RR   --|D12       D13|--   RG

        */


// define sensor pin variable. duplicate or remove as needed
const int frontTrigPin = 2;
const int frontEchoPin = 3;
const int front_Red_LED = 4;
const int front_Green_LED = 5;

const int leftTrigPin = 6;
const int leftEchoPin = 7;
const int left_Red_LED = 8;
const int left_Green_LED = 9;

const int rightTrigPin = 10;
const int rightEchoPin = 11;
const int right_Red_LED = 12;
const int right_Green_LED = 13;

//
const int mode_select_button = A0;  // A0 is used as digital pin 14
const int buzzerPin = A1;           // A1 is used as digital pin 15

/* 
   microseconds since power on. 
   rolls over after about 70 min @ 1,000,000 us per second
   returns unsigned long
 */
long time = micros();
long pollingTime = 1000;

int timeOut = 60000;  // maximum time in microseconds to wait for valid measurement

bool debug = false;  //measure method writes to serial when true TODO toggle on button

int globalmax = 100;             // largest distance in cm that we care about. don't indicate above this distance
int threshold = 25;              // distance in cm that is considered close. indicate green above red below
String indicatorStatus = "OFF";  // holds current LED status

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

  //set up LED indicator pins
  //Red when less than close threshold Green when between threshold and globalmax
  pinMode(front_Green_LED, OUTPUT);
  pinMode(front_Red_LED, OUTPUT);
  pinMode(left_Green_LED, OUTPUT);
  pinMode(left_Red_LED, OUTPUT);
  pinMode(right_Green_LED, OUTPUT);
  pinMode(right_Red_LED, OUTPUT);

  // button inputs
  pinMode(mode_select_button, INPUT);  //input pull up resistor enabled

  // active buzzer for audible indication of mode
  pinMode(buzzerPin, OUTPUT);

  beep();
  beep();
  beep();
}

void loop() {

  long startTime = millis();
  long pollCycle = 0;
  do {
    // example polling pattern
    // measure front
    front();
    // measure right
    right();
    // measure front
    front();
    // measure left
    left();
    pollCycle = millis() - startTime;
  } while (pollCycle <= pollingTime && pollCycle >= 0);
  checkModeButton();
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

// return echo pulse duration in microseconds
long measure(int echoPin, int triggerPin) {
  sendPing(triggerPin);
  long pulseDuration = pulseIn(echoPin, HIGH);
  return pulseDuration;
}

//return measurment in cm
long cm(long microseconds) {
  // speed of sound @ 20 degrees celsius is 343.4 m/s or 0.03434 cm/us
  // the total measured duration includes there and back so twice the time
  // so distance in centimeters equals 0.03434 times the time in microseconds divided by 2
  return microseconds / 29 / 2;
}

// return measurment in inches
long in(long microseconds) {
  // cm * 0.393701 = inches
  return 0.393701 * cm(microseconds);
}

void indicate(int Green_LED, int Red_LED, int distance, int threshold) {
  if (distance <= threshold) {
    digitalWrite(Green_LED, LOW);
    digitalWrite(Red_LED, HIGH);
    indicatorStatus = "RED";
  } else if (distance >= globalmax) {
    digitalWrite(Green_LED, LOW);
    digitalWrite(Red_LED, LOW);
    indicatorStatus = "OFF";
  } else {
    digitalWrite(Green_LED, HIGH);
    digitalWrite(Red_LED, LOW);
    indicatorStatus = "GREEN";
  }
}

// write values to serial port
void sendSerial(long duration, String description) {
  Serial.println("***   " + description + "   ***");
  Serial.println("Echo PW: " + String(duration) + "us");
  Serial.println("Distance: " + String(in(duration)) + "in");
  Serial.println("Distance: " + String(cm(duration)) + "cm");
  Serial.println("LED: " + indicatorStatus);
  Serial.println();
}

void front() {
  long duration = measure(frontEchoPin, frontTrigPin);
  indicate(front_Green_LED, front_Red_LED, cm(duration), threshold);
  if (debug == true) {
    sendSerial(duration, "Front Sensor");
  }
}

void left() {
  long duration = measure(leftEchoPin, leftTrigPin);
  indicate(left_Green_LED, left_Red_LED, cm(duration), threshold);
  if (debug == true) {
    sendSerial(duration, "Left Sensor");
  }
}

void right() {
  long duration = measure(rightEchoPin, rightTrigPin);
  indicate(right_Green_LED, right_Red_LED, cm(duration), threshold);
  if (debug == true) {
    sendSerial(duration, "Right Sensor");
  }
}

// buzzer on 100ms off 100ms
void beep() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}

void debug_mode() {
}

void checkModeButton() {
  int state = digitalRead(mode_select_button);
  if (state == HIGH && debug == false) {
    debug = true;
    beep();
    beep();
    delay(500);
  } else if (state == HIGH && debug == true) {
    debug = false;
    beep();
    delay(500);
  }

  if (debug == true) {
    beep();
  }
}
