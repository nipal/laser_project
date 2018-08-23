
#include <string.h>
#include <math.h>

void	pin_cycle2(int val)
{
	int	cycle_len = 10;
	int	high_time[cycle_len] = {500, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int	low_time;
	int	i;

	memset(high_time, 0, sizeof(int) * cycle_len);
	// on met les valeur
	if (val < 0)
	{
		high_time[0] = 300;
		high_time[1] = 300;
		high_time[2] = 300;
		low_time = 300;
	}
	else if (val >= cycle_len)
	{
		high_time[0] = 50;
		high_time[1] = 50;
		high_time[2] = 50;
		low_time = 300;
	}	
	else
	{
		for (i = 0; i < cycle_len; i++)
		{
			high_time[i] = (i <= val) ? 100 : 0;
		}
		low_time = 100;
	}

	// on les affiche
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	for (i = 0; i < cycle_len; i++)
	{
		digitalWrite(13, HIGH);
		delay(high_time[i]);
		digitalWrite(13, LOW);
		delay(low_time);
	
	}
}

//	pour afficher des nombre a 4 digit on va appeler 4 fois la fonction pin_cycle2
void	pin_cycle3(int	val)
{
	int	div, i;
	int	val_max = 10000;

	div = val_max;
	if (val < 0)
	{
		pin_cycle2(-1);
	}
	else if (val >= val_max)
	{
		pin_cycle2(20); // une valeur trop grande pour pin_cycle2
	}	
	else
	{
		for (i = 0; i < 4; i++, div /= 10)
		{
			pin_cycle2((val / div) % 10);
		}
	}
}

void	pin_cycle1()
{
	int	cycle_len = 10;
	int	high_time[cycle_len] = {500, 150, 150, 150, 0, 0, 0, 0, 0, 0};
	int	low_time = 50;
	int	i;

	for (i = 0; i < cycle_len; i++)
	{
		digitalWrite(13, HIGH);
		delay(high_time[i]);
		digitalWrite(13, LOW);
		delay(low_time);
	
	}
}

void serialEvent()
{
	int	i;
	byte	oct;
	byte	buffer[1024];
	
	i = 0;
	while (Serial.available())
	{
		buffer[i] = Serial.read();
		i++;
	}
	while (!Serial.availableForWrite())
		;
	Serial.write("Yolo swag du 1337\n");
//	pin_cycle1();
//	pin_cycle3(1337);
//	pin_cycle2(-1);
//	pin_cycle2(20);
//	pin_cycle2(3);
//	pin_cycle2(4);
//	pin_cycle2(6);
//	pin_cycle2(0);
//	pin_cycle2(0);
}


