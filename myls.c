#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main (int arc, char **argv) {
  char dir[255] = "./\0";
  int mdata = 0;
  if (arc == 2) {
    if (argv[1] == "-l") {
	mdata = 1;
    }
    else {
      int i;
      for (i=0; i<strlen(argv[1]) && i<=255; ++i)
	dir[i] = argv[1][i];
    }
  }
  else 
    if (arc == 3) {
      mdata = 1;
      int i;
      for (i=1; i<=2; ++i)
	if (argv[i]!="-l") {
	  int j;
	  for (j=0; j<strlen(argv[1]) && j<=255; ++j)
	    dir[j] = argv[i][j];
	}
    }
    else
      if (arc!=1)
	return 0;
      
  DIR *d = opendir(dir);
  struct dirent *tempEnt;
  if (mdata == 0) {
    while ((tempEnt=readdir(d))!=NULL) {
      write(1, tempEnt->d_name, strlen(tempEnt->d_name));
      write(1, "  ", 2);
    }
    write(1, "\n", 1);
  }
  else {
    //with mdata
  }
  closedir(d);
  return 0;
}