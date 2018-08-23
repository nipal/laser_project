/**
 * Copyright (c) 2015, Martin Roth (mhroth@gmail.com)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "tinyosc.h"
#include "laser_project.h"

static volatile bool keepRunning = true;

// handle Ctrl+C
static void sigintHandler(int x) {
  keepRunning = false;
}

/**
 * A basic program to listen to port 9000 and print received OSC packets.
 */

//  pour le peremier mot... peu etre aussi pour les autre
//  mais on va peutre faire autrement au debut pour tester
int get_key_id(int lvl, char *word)
{
}

//  TODO: il faudra faire un truc avec des pointeur sur fonction, une archie super generique
//  pour faire une genre de surcouche a tiny osc avec des outil d'integration et de managment efficace
//  de tout les comportement, et surtout adpter aux differente application ou programme qui emete
//  de l'OSC sans forcement respoecter toute les specification.
//  TODO: et dans tout les cas il faudra faire un  ajout/update de toute les fonction qu'on recode
//  regulierement pour l'utilisation de l'osc en prod ou en debug.
double  tosc_get_value(tosc_message *osc, int arg_pos)
{
    double          value;
    char            type;
    char            *tmp;
    const   char    *tmp2;
    int             i;

    type = osc->format[arg_pos];
    value = 0.0;
    switch (type)
    {
        case 'i':
            value = (double)(tosc_getNextInt32(osc));
            break ;
        case 'f':
            value = tosc_getNextFloat(osc);
            break ;
        case 's':
    value = 0.0;
            tmp = strdup((tmp2 = tosc_getNextString(osc)));
            for (i = 0; tmp && tmp[i]; i++)
                tmp[i] = (tmp[i] == ',') ? '.' : tmp[i];
printf("string[%p] value =>> {%s}\n", tmp, tmp);
            value = atof(tmp);
            free(tmp);
            break ;
        default :
            dprintf(2, "hum i dont find any type conpatible, i put ((1337 + 42) x 0) value\n");
            value = ((1337 + 42) * 0);
            break ;
    }
    return (value);
}

//  la fonction recupere les entrer osc et les charge dans une structure
void    osc_wraper(tosc_message *osc, t_light_pack *lp)
{
    // on recupere chaque partie des truc "slash"
    // on fait les switch case qu'il faut
  
    char    key_word[][32] = {"period", "nbr_seg", "list_pt"};
    int     period, nbr_seg, list_pt[NBR_SEG];
    float   value;

    char    *addr, *format, **parts;
    int     nb_parts, pt_id, i; 

    int     status = 0; // stateof program
    int     ret[3];
    char    tmpBuff[2048];
    int     tmpSize = 0;

    memset(tmpBuff, 0, 2048);


    addr = tosc_getAddress(osc); 
    format = tosc_getFormat(osc);
    if (!(parts = ft_strsplit(addr, '/')))
        return ((void)printf("aie aie aie, une erreur est survenue... ... ... mais que va t'il se passer?!?\n"));

    printf("\n\n===================\n");
    tmpSize = osc->len;
    memmove(tmpBuff, osc->buffer, tmpSize);
    tmpBuff[tmpSize] = '\0';
    printf("buffer[%d]:{%s}\n", tmpSize, tmpBuff);
    printf("=============\naddr:%s\n", addr);
    for (i = 0; parts[i]; i++)
    {
        printf("parts[%d]:%s\n", i, parts[i]);
    }

    //  TODO: refaire le meme principe avec des pointeur sur fonction :)
    printf("\n~~ osc message selector translission ~~\n");


    // before todo
    /*    status = 0;
    status |= ((ret[0] = strcmp(parts[0], "period") ) == 0) << 0;
    status |= ((ret[1] = strcmp(parts[0], "nbr_seg")) == 0) << 1;
    status |= ((ret[2] = strcmp(parts[0], "list_pt")) == 0) << 2;
  */
    
    // TODO: automatiser avec tableau + boucle
// done
    status = 0;
    for (int i = 0;i<3;i++)
    {
	char a;
	a = ret[i];
	a = parts[0];
	a = key_word[i];
        status |= ((ret[i] = strcmp(parts[0], key_word[i])) == 0) << i;
    }

    printf("status: |%x|      ret[0]:%d   ret[1]:%d   ret[2]:%d\n", status, ret[0], ret[1], ret[2]);


    if (strcmp(parts[0], "period") == 0)
    {
        // TODO: recupere la valeur de la periode
        value = tosc_get_value(osc, 0);
       printf("periode actualisation:  >> %5f <<\n", value); 
       lp->period = (int)(value * DELAY_RESOLUTION);
    }
    else if (strcmp(parts[0], "nbr_seg") == 0)
    {
        // TODO: recuperer la valeur du nombre de segment
        value = tosc_get_value(osc, 0);
      printf("nbr_seg actualisation:  >> %5d <<\n", (int)value); 
       lp->nbr_seg = (int)(value);
    }
    else if (strcmp(parts[0], "list_pt") == 0)
    {
        // TODO: recuperer l'indice du point.
        // TODO: recuperer la posotion du point.
        pt_id = atoi(parts[1] + 3); // pour enlever le "pt_"
        value = tosc_get_value(osc, 0);
        printf("list_pt actualisation: PT[%d]    >> %5f <<\n", pt_id, value); 
        lp->lst_pt[pt_id] = (int)(value * lp->period);
    }
    printf("~~ endof transmission ~~\n");
    ft_free_tab(parts);
}

int main_old(int argc, char *argv[]) {

  char buffer[2048]; // declare a 2Kb buffer to read packet data into

  t_light_pack  lp;     // lp ==> light_pack
  int           fd_ardu;

  light_pack_init(&lp);  

  if ((fd_ardu = open_ardu_standar()) < 0)
    return (1); // il faura voir ou est-ce qu'on lache un message d'erreur claire

  printf("Starting OSC write tests:\n");
  int len = 0;
  char blob[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  len = tosc_writeMessage(buffer, sizeof(buffer), "/address", "fsibTFNI",
      1.0f, "hello world", -1, sizeof(blob), blob);
  tosc_printOscBuffer(buffer, len);
  printf("done.\n");

  // register the SIGINT handler (Ctrl+C)
  signal(SIGINT, &sigintHandler);

  // open a socket to listen for datagrams (i.e. UDP packets) on port 9000
  const int fd = socket(AF_INET, SOCK_DGRAM, 0);
  fcntl(fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(9000);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(fd, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));
  printf("tinyosc is now listening on port 9000.\n");
  printf("Press Ctrl+C to stop.\n");

  while (keepRunning) {
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
    struct timeval timeout = {1, 0}; // select times out after 1 second
    if (select(fd+1, &readSet, NULL, NULL, &timeout) > 0) {
      struct sockaddr sa; // can be safely cast to sockaddr_in
      socklen_t sa_len = sizeof(struct sockaddr_in);
      int len = 0;
      while ((len = (int) recvfrom(fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0) {
        if (tosc_isBundle(buffer)) {
          tosc_bundle bundle;
          tosc_parseBundle(&bundle, buffer, len);
          const uint64_t timetag = tosc_getTimetag(&bundle);
          tosc_message osc;
          while (tosc_getNextMessage(&bundle, &osc)) {
            tosc_printMessage(&osc);
          }
        } else {
          tosc_message osc;
          tosc_parseMessage(&osc, buffer, len);
      //    tosc_printMessage(&osc); // si on lis les valeur avant, le buffer se met a la fin 
          osc_wraper(&osc, &lp);     // on recupere les message osc et on met a jour la structure t_light_pack
          write(fd_ardu, &lp, sizeof(t_light_pack));    // on envoie la structure t_light_pack a l'ardurino 
         ardu_print_return2(fd_ardu);
        }
      }
    }
  }

  // close the UDP socket
  close(fd);
  close(fd_ardu);

  return 0;
}
