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

// O_RDWR 
//  O_RDONLY, O_WRONLY, or O_RDWR.
int open_ardu_standar()
{
    int fd;

    fd = open("/dev/ttyACM0",O_RDWR);
//    fd = open("./log_file",O_RDWR);
    appel_system_debug(fd);
//    fd = 2;     // to debug with error output
    return (fd);
}

void    light_pack_init(t_light_pack *lp)
{
    memset(lp, 0, sizeof(t_light_pack));
    memset(&lp->beg, '#', 4);
    memset(&lp->end, '@', 4);
    
    lp->period = DELAY_RESOLUTION;      
}

int ardu_print_return2(int fd_ardu)
{
	fd_set set;
	struct timeval timeout;
	int		rv;
	char		buff[4096];
	int		len = 4096;
	int		ret = 0;
//	int fd_ardu = open( "dev/ttyS0", O_RDWR );

	FD_ZERO(&set); /* clear the set */
	FD_SET(fd_ardu, &set); /* add our file descriptor to the set */

	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;	// 10 miliseconde

	printf("\n                ******* === === ******\n");

	rv = select(fd_ardu + 1, &set, NULL, NULL, &timeout);
	if(rv == -1)
	{
			perror("select"); /* an error accured */
	}
	else if(rv == 0)
	{
		printf("timeout"); /* a timeout occured */
	}
	else
	{
		ret = read( fd_ardu, buff, len); /* there was data to read */
		write(1, "***__***\n", 10);
		write(1, buff, ret);
//		for (int i = 0; i < ret; i++)
//		{
//			write(1, buff + i, 1);
//		}
		write(1, "***__***\n", 10);
		printf("\n ^--- buf_len:%d	=== ===\n", ret);
	}
	if (!ret)
		printf("\n ^--- buf_len: XXX	=== ===\n");
}

void    ardu_print_return(int fd_ardu)
{
    char    buff[4096];
    int     ret;
    int     has_read;

    has_read = 0;
    while ((ret = read(fd_ardu, buff, sizeof(buff))) > 0)
    {
	printf("RET:---->%d\n", ret);
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
