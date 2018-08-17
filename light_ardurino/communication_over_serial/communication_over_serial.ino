
/*


void setup()
{
  pinMode(13, OUTPUT);          // sets the digital pin 13 as output
}

void loop()
{
  digitalWrite(13, HIGH);       // sets the digital pin 13 on
  delay(1000);                  // waits for a second
  digitalWrite(13, LOW);        // sets the digital pin 13 off
  delay(1000);                  // waits for a second
}


*/

void setup() {

//  normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void    pin_test()
{
 digitalWrite(13, HIGH);       // sets the digital pin 13 on
 delay(100);                  // waits for a second
 digitalWrite(13, LOW);        // sets the digital pin 13 off
 delay(100);                  // waits for a second
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
	Serial.write(inChar);
    }
  }
  Serial.write("End connexion\n");
}

void loop() {
    pin_test();
//  delay(500);
//Serial.println("Hello world.");
/*
        if (Serial.available() > 0)
		{
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
*/
}
