#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_SERVER "./myfifo"



int main(int argc, char **argv)
{
	int fd;
	char w_buf[100];
	int nwrite;
	
	fd = open(FIFO_SERVER, O_WRONLY|O_NONBLOCK,0);
	if(fd == -1)
	{
		if(errno == ENXIO)
			printf("open error:no reading process\n");
	}
	
	if(argc <= 1)
	{
		printf("please send something\n");
		return -1;
	}
	
	strcpy(w_buf,argv[1]);
	if((nwrite = write(fd,w_buf,sizeof(w_buf)) == -1))
	{
		if(errno == EAGAIN)
		{
			printf("The FIFO has not been read yet.Please try laster.\n");
		}
		}else{
			printf("write %s to the FIFO\n", w_buf);
		}
		
	
	return 0;
}