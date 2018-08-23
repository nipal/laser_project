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
//	long	none;
	long	end;
}		t_segments;

extern	byte	buffer_receive[512];
extern	byte	buffer_transmit[512];

//	ce seront des fonction destiner a manipuler des variable globale

void	buff_transmit_push(byte *to_push, int len);
void	buff_transmit_push_str(const char *to_push);
void	buff_transmit_push_int(const char *name_var, int to_push);
void	buff_transmit_push_int_array(const char *name_array, const char *name_elem, long int *to_push, int len);
void	buff_transmit_push_float(char *name_var, int to_push);
void	buff_transmit_push_float_array(char *name_array, char *name_elem, float *to_push, int len);
void	buff_transmit_clear();
void	buff_transmit_send();
void	buff_init();

//	normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
void setup()
{
	buff_init();
	Serial.begin(115200);					pinMode(13, OUTPUT);
	digitalWrite(13, LOW);			 	// sets the digital pin 13 off
}

void loop()
{
//	serial_print_pack(buffer_receive, 0);
}
