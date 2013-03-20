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
int main (int arc, char **argv) 
{
  if (arc <= 1) 
    printf("There are not any args\n");
  else
  {
    int sec = atoi(argv[1]);
    printf("sec is %d\n", sec);
    char *path = malloc(sizeof(char)*256);  
    strcpy(path, argv[2]);
    printf("path is %s\n",path);
    char **a = ++argv;
    a=++a;
    alarm(sec);
    if (pid = fork() == -1)
    {
     printf("fork error\n"); 
     return 1;
    }
    if (pid == 0)
    {
      execve(path, a, NULL);
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