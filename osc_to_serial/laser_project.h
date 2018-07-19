#ifndef LASER_PROJECT
# define LASER_PROJECT

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define NBR_SEG 10
# define DELAY_RESOLUTION 1000000

typedef struct  s_light_pack
{
    int         beg;                // 32  bit
    int         period;             // 32  bit
    int         nbr_seg;            // 32  bit
    int         lst_pt[NBR_SEG];    // 320 bit
    int         end;                // 32  bit
}               t_light_pack;

char		**ft_strsplit(const char *str, char c);
int         main_old(int argc, char *argv[]);
void        ft_free_tab(char **tab);

void        appel_system_debug(int fd);
int         open_ardu_standar();
void        light_pack_init(t_light_pack *lp);

#endif
