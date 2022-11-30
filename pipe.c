/* selfpipe.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *msg[3] = { "tjdcks", "20183207","DEU"};
int main() {
	char buf[8]; 
	int pipe_p[3];
	if (pipe(pipe_p) == -1)exit(1);
	for (int i = 0; i < 3; i++)
	write (pipe_p[1], msg[i], 8);
	for (int i = 0; i < 3; i++) {
	read (pipe_p[0], buf, 8);
	printf ("%s\n", buf);
	}
}
