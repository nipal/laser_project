#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       
#include <errno.h> 
#include <string.h>       

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
