
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


/// variable globale 
t_segments	seg;			// pour l'instant les fonction manipule cette variable globale... on pourrai changer
bool		laser_state;
byte		buf[100]; // on en aurait besoin de 60 avec 5 segment

void		pin_test(int tick)
{
	digitalWrite(13, HIGH);
	delay(tick);
	digitalWrite(13, LOW);
	delay(tick);
}

void		pin_chek(int tick)
{
//	digitalWrite(13, HIGH);
//	delay(1000);
//	digitalWrite(13, LOW);
//	delay(1000);

	for (int i = 0; i < tick; i++)
	{
		digitalWrite(13, HIGH);
		delay(300);
		digitalWrite(13, LOW);
		delay(100);
	}
}

void		seg_print()
{
	int	i;
	bool	state;
	long	time;
	
	state = OFF;		// on cherche si il y en a aumoin 1
	time = (long)(micros() + seg.offset) % (long)seg.period;
	for (i = 0; i < seg.nbr_seg && !state; i += 2)
	{
		if (seg.lst_pt[i] <= time && seg.lst_pt[i + 1] > time)
			state = ON;
	}
	if (state != laser_state)
	{
		laser_state = state;//(state) ? HIGH : LOW;
		digitalWrite(13, (state) ? HIGH : LOW);
	}
}

void		seg_set_test()
{
	seg.period = 10000;
	seg.nbr_seg = 1;
	seg.lst_pt[0] = 0;
	seg.lst_pt[1] = seg.period / 2;
}

void		seg_init()
{
	int	i;

	seg.beg = '#' | '#' << 8 | (long)'#' << 16 | (long)'#' << 24;
	seg.fin = '$' | '$' << 8 | (long)'$' << 16 | (long)'$' << 24;
	seg.period = 1;
	seg.nbr_seg = 0;
	seg.offset = 0;
	for (i = 0; i < NBR_SEG * 2; i++)
	{
		seg.lst_pt[i] = 0;
	}
}

void	event_function()
{
	int	i;
	size_t	pack_size;

	if (!Serial.available())
		return;
//laser_state = OFF;
//digitalWrite(13, LOW);

	pack_size = sizeof(t_segments);
	laser_state = OFF;// par recaution on va eteindre le laser
	digitalWrite(13, LOW);
	for (i = 0; Serial.available() && i < pack_size; i++)
	{
//		*(((char*)&seg) + i) = (char)Serial.read();	
		buf[i] = Serial.read();
	}
	check_buf(i);
	//println(i);
//	pin_test(check_buf(i) ? 100 : 1000);

//	Serial.write("\nEnd connexion\n");
}


void	check_beg_end(int size)
{
	int nb_sharp, nb_doll, i;
	for (nb_sharp = 0, nb_doll = 0, i = 0; i < 4; i++)
	{
		nb_sharp += (buf[i] == '#') ? 1 : 0;
		nb_doll += (buf[size - (i + 1)] == '$') ? 1 : 0;
	}
//pin_test((nb_sharp == 4) ? 300: 0);
//pin_chek(nb_sharp);

}

bool	check_buf(int size)
{
	pin_chek(size - sizeof(t_segments));
	return (false);
	if ( false
	|| size > sizeof(t_segments)
//	|| buf[0] != '#'
//	|| buf[1] != '#'
//	|| buf[2] != '#'
//	|| buf[3] != '#'
//	|| buf[size - 1] != '$'
//	|| buf[size - 2] != '$'
//	|| buf[size - 3] != '$'
//	|| buf[size - 4] != '$'
		)
		return (false);
	return (true);
}

//void serialEvent()
//{
//}

void setup()
{
	memset(buf, 0, 100);
	seg_init();
//seg_set_test();	// pour oir si le system fonctionne
	Serial.begin(19200);				//	normalized baudrate: 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
	pinMode(13, OUTPUT);
	laser_state = OFF;				// etein
	digitalWrite(13, LOW);			 	// sets the digital pin 13 off
}

void loop()
{
  digitalWrite(13, LOW);  
//	event_function();
//	seg_print();
}
