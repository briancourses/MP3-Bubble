

/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
 
#include <Servo.h> 
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sampleL;
unsigned int sampleR;
Servo servo;
 
 
void setup() 
{
   Serial.begin(9600);
   
   pinMode(7, OUTPUT);
   servo.attach(7);
}
 
 
void loop() 
{
//  for (int i = 0; i < 4; i++) {
     unsigned long startMillis= millis();  // Start of sample window
     unsigned int peakToPeakL = 0;   // peak-to-peak level
     unsigned int peakToPeakR = 0;   // peak-to-peak level
   
     unsigned int signalMaxL = 0;
     unsigned int signalMinL = 1024;
     unsigned int signalMaxR = 0;
     unsigned int signalMinR = 1024;
   
     // collect data for 50 mS
     while (millis() - startMillis < sampleWindow)
     {
        sampleL = analogRead(0);
        sampleR = analogRead(1);
        if (sampleL < 1024)  // toss out spurious readings
        {
           if (sampleL > signalMaxL)
           {
              signalMaxL = sampleL;  // save just the max levels
           }
           else if (sampleL < signalMinL)
           {
              signalMinL = sampleL;  // save just the min levels
           }
        }
        
        if (sampleR < 1024)  // toss out spurious readings
        {
           if (sampleR > signalMaxR)
           {
              signalMaxR = sampleR;  // save just the max levels
           }
           else if (sampleR < signalMinR)
           {
              signalMinR = sampleR;  // save just the min levels
           }
        }
        
     }
     peakToPeakL = signalMaxL - signalMinL;  // max - min = peak-peak amplitude
     peakToPeakR = signalMaxR - signalMinR;  // max - min = peak-peak amplitude
//  }


//   int displayPeak = map(peakToPeak, 0, 1023, 0, maxScale);
   
//   double voltsL = (peakToPeakL * 3.3) / 1024;  // convert to volts
//   double voltsR = (peakToPeakR * 3.3) / 1024;  // convert to volts
 
//   Serial.println(voltsL);
//   Serial.println(voltsR);
//   int printOut = peakToPeakL - peakToPeakR;
//   Serial.println(printOut);

   
   int diff = peakToPeakL - peakToPeakR;
   Serial.println(diff);
   
   if (diff > 50)
     servo.write(120);
   else if (diff > 25)
     servo.write(105);
   else if (diff >= -25)
     servo.write(90);
   else if (diff >= -50)
     servo.write(75);
   else
     servo.write(60);

   
   
   
//   int pos = 30*(voltsL- voltsR);
//   servo.write(90 + pos); // UNCOMMENT THIS!!!
//   Serial.println(pos);
   
//   if (pos > 4)
//     pos = 4;
//   else if (pos < -4)
//     pos = -4;
//     
//   pos = 20*pos;
//   servo.write(90 + pos);
//   servo.write(0);
}


