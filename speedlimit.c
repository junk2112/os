#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int pid;
int arr[2];
int tempSizeIn;
long long int bytes = 0;
int time = 2;
void alarmAction (int signum) 
{
	double speed = (double)bytes/(1024*1024*time);
	printf("Total Mb: %f\nPipe speed: %f Mb/s\n", (double)bytes/(1024*1024), speed);
	FILE * file;
	if ( (file = fopen("result.xls", "a")) != NULL)
	{
		fprintf(file, "%f %d\n", speed, tempSizeIn);
	}
	else 
	{
		printf("file open error\n");
	}
	fclose(file);
	kill(pid, SIGKILL);
	close(arr[0]);
}
int main (int arc, char **argv, char **env) 
{
	tempSizeIn = atoi(argv[1]);
	int tempSizeOut = tempSizeIn;
	if (pipe(arr) == -1)
	{
		printf("pipe error\n");
		return 1;
	}
	alarm(time);
	if ( (pid = fork()) == -1)
	{
		printf("fork error\n"); 
		return 1;
	}
	if (pid == 0)//child
	{
		close(arr[0]);
		char temp[tempSizeIn];
		while (write (arr[1], &temp, tempSizeIn) > 0) {}
		close(arr[1]);
	}
	else //parent
	{      
		close(arr[1]);
		char temp[tempSizeOut];
		if (signal(SIGALRM, alarmAction) == SIG_ERR)
		{
			printf("sigaction error\n");
			return 1;
		}
		while(read(arr[0], &temp, tempSizeOut) > 0)
		{
			bytes += tempSizeOut;
		}
		waitpid(pid, NULL, NULL);
    }
    return 0;
}
