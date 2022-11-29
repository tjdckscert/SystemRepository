#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	struct flock testlock;
	testlock.l_type = F_WRLCK;
	testlock.l_whence = SEEK_SET;
	testlock.l_start = 0;
	testlock.l_len = 10;
	int fd;

	int pidnumber;
	fd = open ("recodelock", O_RDWR | O_CREAT, 0666);
	pidnumber = fork();
	if (pidnumber == 0) { 
	testlock.l_len = 5;
		if (fcntl (fd, F_SETLKW, &testlock) == -1) {
			perror ("child: locking");
			exit (0);
		}
		printf ("childlocked\n"); 
		sleep(10);
		printf ("childunlock\n");
	}
	else if (pidnumber > 0) {
		sleep(10);
		printf ("parentunlock");
	}
}

