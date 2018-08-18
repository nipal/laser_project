
void		pin_test()
{
	digitalWrite(13, HIGH);				// sets the digital pin 13 on
	delay(100);					// waits for a second
	digitalWrite(13, LOW);			 	// sets the digital pin 13 off
	delay(100);					// waits for a second
}

void	event_function()
{
	//
	while (Serial.available()) {
		char inChar = (char)Serial.read();
	Serial.write(inChar);
		Serial.print("I received: ");
	}
	Serial.write("End connexion\n");
}

void serialEvent()
{
	event_function();
}

void setup()
{

	Serial.begin(9600);				//	normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
	pinMode(13, OUTPUT);
	pin_test();
}

void loop()
{
}
