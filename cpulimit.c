#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
//input: percentages, path, args
const int checkTime = 10;
int main (int arc, char **argv) 
{
  if (arc <= 1)
    printf("There are not any args\n");
  else
  {
    float limitPercent = (float)atoi(argv[1])/100;
    char *path = malloc(sizeof(char)*256);  
    strcpy(path, argv[2]);
    printf("path is %s\n",path);
    printf("percent is %f\n", limitPercent);
    int pid;
    char **args = ++argv;
    args = ++args;
    
    if (pid = fork() == -1)
    {	
      printf("fork error\n");
      return 1;
    }
    else
      {
	if (pid == 0)
	{
	  execve(path, args, NULL);
	}
	else 
	  {
	    float percent = 0;
	    while (kill(pid, 0) != -1)
	    {	    
	      kill(pid, SIGSTOP);
	      usleep(checkTime*percent);
	      kill(pid, SIGCONT);
	    }
	    
	  }
      waitpid(pid, NULL, NULL);
     }
  }
  return 0;
}