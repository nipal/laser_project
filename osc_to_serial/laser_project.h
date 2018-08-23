#ifndef LASER_PROJECT
# define LASER_PROJECT

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

// read with timeout
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

int ardu_print_return2(int fd_ardu);



# define NBR_SEG 5
# define DELAY_RESOLUTION 50000 // 20 hz au minimum: 0.05 s

typedef struct  s_light_pack
{
  	int	beg;
	int	period;
	int	offset;
	int	nbr_seg;
	int	lst_pt[NBR_SEG * 2];
//	int	none;
	int	end;
}               t_light_pack;

char		**ft_strsplit(const char *str, char c);
int         main_old(int argc, char *argv[]);
void        ft_free_tab(char **tab);

void        appel_system_debug(int fd);
int         open_ardu_standar();
void        light_pack_init(t_light_pack *lp);
void        ardu_print_return(int fd_ardu);

#endif
