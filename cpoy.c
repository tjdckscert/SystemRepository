#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_READ 100
int main(int argc, char *argv[]){
	int exist;
	int new;
	char buf[MAX_READ];
	ssize_t rcnt;
	ssize_t tot_cnt = 0;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 
	if (argc < 3) {
	fprintf(stderr, "write new file \n");
	exit(1);
	}
	if ((exist = open(argv[1], O_RDONLY)) == -1 ){
	perror("src "); 
	exit(1);
	}
	if ((new = creat(argv[2], mode)) == -1 ){
	perror("new "); 
	exit(1);
	}
	if (rcnt < 0) {
	perror("read");
	exit(1);
	}
	while ( (rcnt = read(exist, buf, MAX_READ)) > 0) {
	write(new, buf, rcnt);
	}

	close(exist);
	close(new);
}

