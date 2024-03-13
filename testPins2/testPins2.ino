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
/* 
make sure pins are not connected to any power
or GND  before programming to avoid damage
*/

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);

}

void loop() {
// make even pins HIGH
/*
digitalWrite(0, HIGH);
digitalWrite(2, HIGH);
digitalWrite(4, HIGH);
digitalWrite(6, HIGH);
digitalWrite(8, HIGH);
digitalWrite(10, HIGH);
digitalWrite(12, HIGH);
digitalWrite(14, HIGH);
digitalWrite(16, HIGH);
digitalWrite(18, HIGH);
digitalWrite(20, HIGH);
*/
// make odd pins LOW
///*
digitalWrite(1, LOW);
digitalWrite(3, LOW);
digitalWrite(5, LOW);
digitalWrite(7, LOW);
digitalWrite(9, LOW);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
digitalWrite(15, LOW);
digitalWrite(17, LOW);
digitalWrite(19, LOW);
digitalWrite(21, LOW);
//*/
// wait for a 250ms
delay(250);
// make even pins LOW
/*
digitalWrite(0, LOW);
digitalWrite(2, LOW);
digitalWrite(4, LOW);
digitalWrite(6, LOW);
digitalWrite(8, LOW);
digitalWrite(10, LOW);
digitalWrite(12, LOW);
digitalWrite(14, LOW);
digitalWrite(16, LOW);
digitalWrite(18, LOW);
digitalWrite(20, LOW);
*/
///*
// make odd pins HIGH
digitalWrite(1, HIGH);
digitalWrite(3, HIGH);
digitalWrite(5, HIGH);
digitalWrite(7, HIGH);
digitalWrite(9, HIGH);
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
digitalWrite(15, HIGH);
digitalWrite(17, HIGH);
digitalWrite(19, HIGH);
digitalWrite(21, HIGH);
//*/
// wait for a 250ms
delay(250);

}
 
