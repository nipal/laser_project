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

double  tosc_get_value(tosc *osc, int arg_pos)
{
    double  value;
    char    type;

    // on chope le type

    type = '\0';
    value = 0.0;
    switch ()
    {
        case 'i':
            //  on converti
            //  on envoie
            break ;
        case 'f':
            // on envoie tel quel
            break ;
        case 's':
            // on filtre les merdre de ','
            // on convertie
            // on envoie
            break ;
    }
    return (value);
}

#define NBR_SEG 16
void    osc_wraper(tosc_message *osc)
{
    // on recupere chaque partie des truc "slash"
    // on fait les switch case qu'il faut
  
    char    key_word[][32] = {"period", "nbr_seg", "list_pt"};
    int     period, nbr_seg, list_pt[NBR_SEG];
    float   value;

    char    *addr, *format, **parts;
    int     nb_parts, pt_id, i;


    addr = tosc_getAddress(osc); 
    format = tosc_getFormat(osc);
    if (!(parts = ft_strsplit(addr, '/')))
        return ((void)printf("aie aie aie, une erreur est survenue... ... ... mais que va t'il se passer?!?\n"));

    printf("=============\naddr:%s\n", addr);
    for (i = 0; parts[i]; i++)
    {
        printf("parts[%d]:%s\n", i, parts[i]);
    }

    if (strcmp(parts[0], "period") == 0)
    {
        // TODO: recupere la valeur de la periode
       printf("periode actualisation:  >> %5d <<\n", value); 
    }
    else if (strcmp(parts[0], "nbr_seg") == 0)
    {
        // TODO: recuperer la valeur du nombre de segment
      printf("nbr_seg actualisation:  >> %5d <<\n", value); 
    }
    else if (strcmp(parts[0], "list_pt") == 0)
    {
        // TODO: recuperer l'indice du point.
        // TODO: recuperer la posotion du point.
       printf("list_pt actualisation: PT[%d]    >> %5d <<\n", value); 
    }
    ft_free_tab(parts);
}

int main_old(int argc, char *argv[]) {

  char buffer[2048]; // declare a 2Kb buffer to read packet data into

  printf("Starting write tests:\n");
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
          tosc_printMessage(&osc);
          osc_wraper(&osc);
        }
      }
    }
  }

  // close the UDP socket
  close(fd);

  return 0;
}
