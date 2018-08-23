////hz:42 & period: 0.023809 s
////	normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
//// 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200,
//230400, 460800

/*
	une liste de point a afficher
	une machine a afficher des segments
	une reseption en live fluide

	ouverture/fermeture du fd optimise/automatise c <-> ino
*/

/*
	Il faudrait qualibrer/determiner/tester
	le temps de calcule/traitement disponible
	entre 2 changement d'etat du laser.
*/

#include <string.h>

#define	ON	true
#define	OFF	false
#define	NBR_SEG	5

// pour un ardurino un long fait 32 bit
typedef	struct	s_light_pack
{
	long	beg;
	long	period;
	long	offset;
	long	nbr_seg;
	long	lst_pt[NBR_SEG * 2];
	long	none;
	long	fin;
}		t_segments;

//	normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
void setup()
{
	Serial.begin(115200);					pinMode(13, OUTPUT);
	digitalWrite(13, LOW);			 	// sets the digital pin 13 off
}

void loop()
{
}
