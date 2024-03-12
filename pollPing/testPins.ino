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

void loop(){
// toggle all pins every 250 milliseconds

for(int i=0; i<=21; i++){
    digitalWrite(i, HIGH);
  }
  delay(250);
  for(int i=0; i<=21; i++){
    digitalWrite(i, LOW);
  }
  delay(250);
}
