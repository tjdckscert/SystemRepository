#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	DIR *pdir;
	struct dirent *pde; int i = 0;
	if (argc < 2) {
	fprintf(stderr, "write dir_name \n");
	 exit(1);
	}
	if ( (pdir = opendir(argv[1])) < 0 ) { perror("ls start");
	exit(1);
	}
	while ((pde = readdir(pdir)) != NULL) { 
		printf("%15s ", pde->d_name);
		if (++i % 4 == 0) printf("\n");
	}
	closedir(pdir);
}
