#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
//input: percentages, path, args
const int checkTime = 1000;
int main (int arc, char **argv, char **env) 
{
  if (arc <= 2)
    printf("There must be 2 args at least: seconds and path\n");
  else
  {
    int limitPercent = atoi(argv[1]);
    printf("path is %s\n",argv[2]);
    printf("Use %d percentages of cpu\n", limitPercent);
    int pid;
    
    if ( (pid = fork()) == -1)
    {	
      printf("fork error\n");
      return 1;
    }
    else
      {
	if (pid == 0)//child
	{
	  execv(argv[2], argv+2);
	}
	else //parent
	  {
	    while (kill(pid, 0) != -1)
	      {	
		kill(pid, SIGSTOP);
		usleep(checkTime*(100-limitPercent));
		kill(pid, SIGCONT);
		usleep(checkTime*(limitPercent));	
	      }  
	  }
	waitpid(pid, NULL, NULL);
	}
  }
  return 0;
}