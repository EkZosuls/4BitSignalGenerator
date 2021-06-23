/*
 * Simple binary counter for the DAC
 * Aleks Zosuls 2021
 * 
 *    //delayMicroseconds(151);  //hand adjusted delay that sets sample update rate
   // C 440 Hz is approximately 151 uS.
 */
#define ptsPerCycle 8
byte signal1[ptsPerCycle] = {8, 15, 14, 9, 7, 6, 1, 0};
byte signal2[ptsPerCycle] = {8, 15, 10, 10, 8, 5, 5, 0};
byte signal3[ptsPerCycle] = {8, 13, 15, 13, 8, 2, 0, 2};
byte rampCount = 8;
byte DC = 7;

void playArb(byte signa[], long cycles, int samPeriod);
void playRamp(long nCycles);
void playPoint(byte sig);
void printInstructions(void);

void setup() {
Serial.begin(9600);
DDRD = DDRD | B11110000;    //set digital pins D4-D7 as digital outputs
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
//PORTD = B11110000 & (rampCount << 4); 
playPoint(DC);
delay(20);
digitalWrite(13, LOW);
Serial.println("Arduino signal Generator for EK307");
printInstructions();
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
          playArb(signal1, 4000, 364);
          playPoint(DC);
          printInstructions();
          break;
  
         case 'R':
           Serial.println("Ramp generator!");
           delay(100);
           playRamp(100);
           playPoint(DC);
           printInstructions();
           break;
  
         case '2':
           Serial.println("Signal 2");
           playArb(signal2, 2000, 728);
           playPoint(DC);
           printInstructions();
           break;

         case '3':
           Serial.println("Signal 3");
           playArb(signal3, 2000, 1000);
           playPoint(DC);
           printInstructions();
           break;

          case '4':
           Serial.println("Signal 4");
           playArb(signal3, 20000, 100);
           playPoint(DC);
           printInstructions();
           break;

          case '5':
           Serial.println("Signal 5");
           playArb(signal3, 40000, 50);
           playPoint(DC);
           printInstructions();
           break;
      } //end of switchcase
  } //end of if Serial.avail...  

} //end of looop

void playArb(byte signa[], long cycles, int samPeriod){
  int circIndex = 0;
  long endPoint = cycles * ptsPerCycle;
  long point = 0;
  while(point <= endPoint){
    PORTD = B11110000 & (signa[circIndex] << 4); 
    delayMicroseconds(samPeriod);
    ++circIndex;
    circIndex = circIndex % (ptsPerCycle);
    ++ point;
  } //end of while(point...
} //end of playArb

void playRamp(long nCycles) {
  byte rampCount = 8; //start at offstted 'zero'
  long endPoint = 16 * nCycles;
  long point = 0;
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

void playPoint(byte sig){
    PORTD = B11110000 & (sig << 4); 
}
void printInstructions(void){
  Serial.println("input 1,2,R for a signal");
}
