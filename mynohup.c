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
    printf("path is %s\n",path);
    int pid;
    char **a = ++argv;
    if (pid = fork() == 0)
    {
      execve(path, a, NULL);
    }
    sigaction(SIGHUP, NULL, NULL);
    waitpid(pid, NULL, NULL);
    free(path);
  }
  return 0;
}