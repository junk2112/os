#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool print (char *path)
{ 
  const int fd = open(path,O_RDONLY);
  if (fd>0) 
  {
    char * temp = malloc(sizeof(char));
    while(read(fd, temp, 1)!=0) //not sure that its rational
      write(1, temp, strlen(temp));
    write(1, "\n", 2);	
    free(temp);
    return true;
  }
  else 
  {
    write(1, "Error (path is not exist)\n", 26);
    return false;
  }
}

int main (int arc, char **argv) {
        if (arc<=1) 
	{
	  while(true) //as at original cat
	  {
	    char *str = malloc(1024*sizeof(char));
	    read(0, str, 1024);
	    write(1, str, 1024);
	  }
        }
        else 
	{
	  int i;
	  for (i=1; i<arc; i++) 
	    if(!print(argv[i]))
	      return 1;
	}
return 0;
}
