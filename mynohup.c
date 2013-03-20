#include <stdio.h>
#include <signal.h>
#include <string.h>
int main (int arc, char **argv) 
{
  if (arc <= 1) 
    printf("There are not any args\n");
  else
  {
    char *path = malloc(sizeof(char)*256);  
    strcpy(path, argv[1]);
    //printf("path is %s\n",path);
    int pid;
    char **a = ++argv;
    if (pid = fork() == -1)
    {	
      printf("fork error\n");
      return 1;
    }
    else
      if (pid == 0)
      {
	execve(path, a, NULL);
      }
      else 
	{
	  static struct sigaction act;
	  act.sa_handler = SIG_IGN;
	  sigaction(SIGHUP, &act, NULL);
	  waitpid(pid, NULL, NULL);
	  free(path);
	}
  }
  return 0;
}