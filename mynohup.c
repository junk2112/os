#include <stdio.h>
#include <signal.h>
#include <string.h>
void handler (int sig)
{
  printf("handler\n");
}
int main (int arc, char **argv, char **envp) 
{
  if (arc < 2) 
  {
    printf("There are not any args\n");
    return 1;
  }
  else
  {	
    //printf("hello\n");
    int pid;
    if ( (pid = fork()) == -1)
    {	
      printf("fork error\n");
      return 1;
    }
    else
      if (pid == 0)
      {
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGHUP, &act, NULL) != 0 )
	{
	  printf("sigaction error\n");
	}
	if (execv(argv[1], argv+1) == -1)
	{
	 printf("execv error\n"); 
	 return 1;
	}
      }
      else 
	{
	  waitpid(pid, NULL, NULL);
	}
  }
  return 0;
}