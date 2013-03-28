#include <stdio.h>  
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
int pid;
int arr[2];
int tempSizeIn = 1;
int tempSizeOut = 1;
int bytes = 0;
int time = 1;
void alarmAction (int signum) 
{
  printf("ALARM\n");
  kill(pid,SIGUSR1);
  kill(pid, SIGKILL);
  char temp[tempSizeOut];
  while(read(arr[0], &temp, tempSizeOut) > 0) 
  {
       bytes += tempSizeOut;
  }
  close(arr[0]);
  printf("Total bytes: %d\nPipe speed: %f kb/s\n", bytes, (double)bytes/(1024*time));
  
}
void newHandler (int signum)
{
  close(arr[1]);
}
int main (int arc, char **argv) 
{
    
    if (pipe(arr) == -1)
    {
     printf("pipe error\n");
     return 1;
    }
    if ( (pid = fork()) == -1)
    {
     printf("fork error\n"); 
     return 1;
    }
    if (pid == 0)
    {
      signal(SIGUSR1, newHandler);
      close(arr[0]);
      while (1) 
      {
	char temp[tempSizeIn];
	write (arr[1], &temp, tempSizeIn);
      }
    }
    else 
    {      
      alarm(time);
      close(arr[1]);
      if (signal(SIGALRM, alarmAction) == SIG_ERR)
      {
	printf("sigaction error\n");
	return 1;
      }
    }
    waitpid(pid, NULL, NULL);
    return 0;
}