#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       
#include <errno.h> 
#include <string.h>       

#include <laser_project.h>

void    appel_system_debug(int fd)
{
    char    *tmp;

    tmp = strerror(errno);
    printf("==================\n");
    printf("fd:%d\n", fd);
    printf("errno:%d\n", errno);
    printf("msg:%s\n", tmp);
    printf("fd:%d\n     errno:%d    msg:%s\n", fd, errno, strerror(errno));
}

int open_ardu_standar()
{
    int fd;

    fd = open("/dev/ttyACM0",O_RDWR);
    appel_system_debug(fd);
//    fd = 2;     // to debug with error output
    return (fd);
}

void    light_pack_init(t_light_pack *lp)
{
    memset(lp, 0, sizeof(t_light_pack));
    memset(&lp->beg, '#', 4);
    memset(&lp->end, '@', 4);
    
    lp->period = DELAY_RESOLUTION;  // 1000000 one million by etienne klein
    
}

void    ardu_print_return(int fd_ardu)
{
    char    buff[4096];
    int     ret;
    int     has_read;

    has_read = 0;
    while ((ret = read(fd_ardu, buff, sizeof(buff))) > 0)
    {
        has_read = 1;
        write(1, buff, ret);
    }
    if (has_read)
    {
        write(1, "===============\n", 16);
    }
    if (ret < 0)
    {
        appel_system_debug(fd_ardu);
    }
}


/*
int main()
{
    int fd;

    fd = open("/dev/ttyACM0",O_WRONLY);
    appel_system_debug(fd);
    write(fd, "coucou", 6);
    appel_system_debug(fd);

    return (0);
}
*/
