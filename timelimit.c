#include <stdio.h>  
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
//input:seconds,path,args
int pid;
void alarmAction (int signum) 
{
  printf("ALARM\n");
  kill(pid,SIGKILL);
}
int main (int arc, char **argv, char **env) 
{
  if (arc <= 1) 
    printf("There are not any args\n");
  else if (arc == 2)
    printf("There must be 2 args at least:seconds and path\n");
  else
  {
    int sec = atoi(argv[1]);
    printf("sec is %d\n", sec);
    char *path = malloc(sizeof(char)*256);  
    strcpy(path, argv[2]);
    printf("path is %s\n",path);
    char **a = argv+2;
    alarm(sec);
    if ( (pid = fork()) == -1)
    {
     printf("fork error\n"); 
     return 1;
    }
    else
    if (pid == 0)
    {
      execv(path, a);
    }
    else 
    {      
      struct sigaction act;
      act.sa_handler = alarmAction;
      if (sigaction(SIGALRM, &act, NULL) != 0)
      {
	printf("sigaction error\n");
      }
      
    }
    waitpid(pid, NULL, NULL);
    free(path);
  }
  return 0;
}