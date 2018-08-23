
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

size_t	buffer_size = 512;
byte	buffer_receive[512];
byte	buffer_transmit[512];
int	cursor_rx;
int	cursor_tx;

// pur initialiser tout les buffer
void	buff_init();

//	ce seront des fonction destiner a manipuler des variable globale
//TODO: 
void	buff_transmit_push_float(char *name_var, int to_push);
void	buff_transmit_push_float_array(char *name_array, char *name_elem, float *to_push, int len);


void	buff_init()
{
	buff_transmit_clear();
}

void	buff_transmit_clear()
{
	memset(buffer_transmit, 0, cursor_tx);
	cursor_tx = 0;
}

void	buff_transmit_send()
{
	int	i, ret;

	i = 0;
	while (i < cursor_tx)
	{
		while (!Serial.availableForWrite());
		ret = Serial.write((buffer_transmit + i), 128);
		i += 128;
		//i += ret; // au cas ou
	}
	buff_transmit_clear();
}


void	buff_transmit_push(byte *to_push, int len)
{
	memmove(buffer_transmit, to_push, len);
}

void	buff_transmit_push_str(const char *to_push)
{
	int	len_str;

	len_str = strlen(to_push);
	if ((len_str + cursor_tx) > buffer_size)
	{
		return ;// TODO: lacher un message d'erreur/log
	}
	memmove(buffer_transmit + cursor_tx, to_push, len_str);
	cursor_tx += len_str;
}

void	buff_transmit_push_int(const char *name_var, int to_push)
{
	char	nbr[32];

	itoa(to_push, nbr, 10);
	buff_transmit_push_str(name_var);
	buff_transmit_push_str(":\t");
	buff_transmit_push_str(nbr);
	buff_transmit_push_str("\n");
}

void	buff_transmit_push_int_array(const char *name_array,const char *name_elem, long int *to_push, int len)
{	
	char	pre_name[64];
	int	i, cursor;

	buff_transmit_push_str(name_array);
	buff_transmit_push_str(":\n");
	for (i = 0; i < len; i++)
	{
		pre_name[0] = '\t';
		cursor = strlen(name_elem) + 1;
		memmove((void*)name_elem, pre_name + 1, cursor - 1);
		pre_name[cursor] = '[';
		itoa(i, pre_name, 10);
		cursor += strlen(pre_name) + 1;
		pre_name[cursor] = ']';
		buff_transmit_push_int(pre_name, to_push[i]);
	}
}


void	serial_print_pack(byte *buff, size_t len)
{
	t_segments	*seg;
	int		i;
	char		mini_buff[32];
	char		limiteur[5] = {0, 0, 0, 0, 0};

	seg = (t_segments*)buff;

	// TODO: faire une fonction qui reuni toute ces ligne en une
	memmove(limiteur, &(seg->beg), 4);
	buff_transmit_push_str("beg:\t");
	buff_transmit_push_str(limiteur);
	buff_transmit_push_str("\n");

	buff_transmit_push_int("period", seg->period);
	buff_transmit_push_int("offset", seg->offset);
	buff_transmit_push_int("nbr_seg", seg->nbr_seg);
	buff_transmit_push_int_array("lst_pt", "pt", seg->lst_pt, 10); // on metra nbr seg quand cafoncitonera bien

	memmove(limiteur, &(seg->end), 4);
	buff_transmit_push_str("end:\t");
	buff_transmit_push_str(limiteur);
	buff_transmit_push_str("\n");
}


void serialEvent()
{
	int	i;
	byte	oct;
	
	i = 0;
	while (Serial.available())
	{
		buffer_receive[i] = Serial.read();
		i++;
	}
	serial_print_pack(buffer_receive, i);
}
