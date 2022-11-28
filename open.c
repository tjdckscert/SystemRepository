#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
//20183207 
//KimseongChan
int main(int argc, char *argv[]){
	int i;
	if (argc < 2) {
		fprintf(stderr, "write new file\n"); //if file name os not exist
		exit(1); //end
	}	
	if ( (i = open(argv[1], O_RDONLY)) == -1 ) {
		perror("read : "); 
		exit(1); //end
	}
	printf("\"%s\" exist \n", argv[1]);
	close(i);
}

