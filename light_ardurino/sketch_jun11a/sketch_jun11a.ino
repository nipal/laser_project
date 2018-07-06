#include <OSCData.h>
#include <SLIPEncodedSerial.h>
#include <OSCTiming.h>
#include <SLIPEncodedUSBSerial.h>
#include <OSCMatch.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

int periode = 13812;
float prct = 1;
int curseur;




void setup()                                 // Built-in initialization block
{
  curseur = periode * prct;
  pinMode(13, OUTPUT);                       // Set digital pin 13 -> output
}  

void loop()                                  // Main loop auto-repeats
{                                         
  digitalWrite(13, HIGH);                    // Pin 13 = 5 V, LED emits light
  delayMicroseconds(curseur);                                // ..for 0.5 seconds
  digitalWrite(13, LOW);                     // Pin 13 = 0 V, LED no light
  delayMicroseconds(periode - curseur);      // ..for 0.5 seconds
}  
