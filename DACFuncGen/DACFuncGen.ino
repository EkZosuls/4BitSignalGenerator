/*
 * Simple binary counter for the DAC
 * Aleks Zosuls 2021
 * 
 *    //delayMicroseconds(151);  //hand adjusted delay that sets sample update rate
   // C 440 Hz is approximately 151 uS.
 */
#define ptsPerCycle 7
byte signal1[ptsPerCycle] = {8, 15, 13, 7, 8, 2, 0};
byte signal2[ptsPerCycle] = {8, 15, 13, 7, 8, 2, 0};
byte rampCount = 8;

void playArb(byte signa[], int cycles);
void playRamp(void);

void setup() {
Serial.begin(9600);
DDRD = DDRD | B11110000;    //set digital pins D4-D7 as digital outputs
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
PORTD = B11110000 & (rampCount << 4); 
delay(2000);
digitalWrite(13, LOW);
Serial.println("Arduino signal Generator for EK307");
}

void loop() {
  int controlByte;
  // put your main code here, to run FOR EVER!!
  if (Serial.available() > 0) {
      controlByte = Serial.read(); 
      controlByte = toupper(controlByte); //make it upper case
      //UI check for commands then 
      switch (controlByte) {
        case '1':
          Serial.println("Signal 1");
          delay(100);
          playArb(signal1, 1000);
          break;
  
         case 'R':
           Serial.println("Ramp generator!");
           delay(100);
           playRamp();
           break;
  
         case '2':
           Serial.println("Signal 2");
           playArb(signal2, 1000);
           break;
      } //end of switchcase
  } //end of if Serial.avail...  
Serial.println("input 1,2,R for a signal");
} //end of looop

void playArb(byte signa[], int cycles){
  int circIndex = 0;
  int endPoint = cycles * ptsPerCycle;
  int point = 0;
  while(point <= endPoint){
    PORTD = B11110000 & (signa[circIndex] << 4); 
    delayMicroseconds(10);
    ++circIndex;
    circIndex = circIndex % (ptsPerCycle-1);
    ++ point;
  } //end of while(point...
} //end of playArb

void playRamp(void) {
  byte rampCount = 8;
  int endPoint = 8 * 10;
  int point = 0;
    while(point <= endPoint){
      if (rampCount == 0)
      { rampCount = 16;
      }
      PORTD = B11110000 & (rampCount << 4); 
     //place the lower nibble in the upper nibble of port D using a bit shift op
      delay(10); 
      -- rampCount;  // this is a decrement because or circuit is an inverter
      ++ point;
    } //end of while(point...
} //end of playRamp
