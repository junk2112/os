#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main (int arc, char ** argv) {
        if (arc<=1) {
            write(1, "No arguments\n", 20);
            return 0;
        }
        int i;
	for (i=1; i<arc; i++) {
		const int fd = open(argv[i],O_RDONLY);
		if (fd>0) {
			char * temp = malloc(1024*sizeof(char));
			while(read(fd, temp, 1024)!=0)
			  write(1, temp, strlen(temp));
			write(1, "\n", 2);
			free(temp);
		}
		else {
			write(1, "Error\n", 7);
		}
	}
return 0;
}
