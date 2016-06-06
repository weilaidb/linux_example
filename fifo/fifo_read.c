#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>



#define FIFO "./myfifo"



int main(int argc, char **argv)
{
	
	int fd;
	char r_buf[100];
	int nread;
	
	if(mkfifo(FIFO, O_CREAT | 0777) < 0)
	{
		printf("cannot make fifoserver\n");
		exit(1);
	}
	
	printf("Preparing for reading bytes...\n");
	
	memset(r_buf,0,sizeof(r_buf));
	
	
	fd = open(FIFO, O_RDONLY|O_NONBLOCK,0);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	
	while(1)
	{
		memset(r_buf,0,sizeof(r_buf));
		
		if((nread = read(fd, r_buf,sizeof(r_buf))) == -1)
		{
			if(errno == EAGAIN)
			{
				printf("no data yet\n");
			}
		}
		printf("read %d len from FIFO\n", nread);
		printf("read %s from FIFO\n", r_buf);
		if(0 == strncmp(r_buf,"quit",4))
			break;
		sleep(2);
	}
	
	unlink(FIFO);
	
	return 0;
}

