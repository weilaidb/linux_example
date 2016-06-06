#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pipe_rw[2];
	char buf[1024];
	int res = 0;
	pid_t pid;
	
	if(pipe(pipe_rw) < 0)
	{
		return -1;
	}
	
	if((pid = fork()) == 0 )
	{
		close(pipe_rw[1]);
		sleep(2);
		int r_nums = read(pipe_rw[0], buf, sizeof(buf));
		printf("read %d nums\n", r_nums);
		printf("read things:%s\n", buf);
		
		close(pipe_rw[0]);
		exit(0);
		
	}else
	{
		close(pipe_rw[0]);
		
		write(pipe_rw[1], "hello pipe!\n",20);
		write(pipe_rw[1], "hello pipe!\n",20);
		write(pipe_rw[1], "hello pipe!\n",20);
		write(pipe_rw[1], "hello pipe!\n",20);
		write(pipe_rw[1], "hello pipe!\n",20);
		close(pipe_rw[1]);
		printf("wait for pid:%d\n", pid);
		sleep(3);
		waitpid(pid,NULL,0);
		exit(0);
		
	}
	
	printf("==end==\n");
	return 0;

}