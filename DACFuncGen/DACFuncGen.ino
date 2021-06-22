/*
 * Simple binary counter for the DAC
 * Aleks Zosuls 2021
 */
byte rampCount = 8;

void setup() {
Serial.begin(1000000);
DDRD = DDRD | B11110000;    //set digital pins D4-D7 as digital outputs
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
PORTD = B11110000 & (rampCount << 4); 
delay(2000);
digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
      if (rampCount == -1)
    { rampCount = 15;
    }
     PORTD = B11110000 & (rampCount << 4); 
     //place the lower nibble in the upper nibble of port D using a bit shift op
    delay(10); 
   //delayMicroseconds(151);  //hand adjusted delay that sets sample update rate
   // C 440 Hz is approximately 151 uS.
    -- rampCount;  // this is a decrement because or circuit is an inverter

    //rampCount = rampCount % 256;
    //Serial.println(rampCount);
}
