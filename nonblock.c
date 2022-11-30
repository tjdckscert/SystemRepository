#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MSGSIZE 10
char *parent = "parent";
char *msg = "non-block";
char *child = "child";


void nonblock_rw (char *name, int read_pipe, int write_pipe, char *message)
{
	char buf[10];
	int nread;
	fcntl (read_pipe, F_SETFL, O_NONBLOCK) ;
	fcntl (write_pipe, F_SETFL, O_NONBLOCK) ;
	while(1)
	{
		switch (nread = read(read_pipe, buf, 10))
		{
				case 0:
				printf ("%s: read pipe closed\n", name);
				exit (1);
				default:
					printf("%s: MSG=%s\n", name, buf);
		}
		write(write_pipe, message, 10);
		sleep (1);
	}
}

int main()
{
	int pipe_p[2][2], i;
	int pidnumber;
	for (i = 0; i < 2; i++) if (pipe(pipe_p[i]) == -1) exit (0);
	pidnumber = fork();
	if (pidnumber == 0)
	{
		close(pipe_p[0][1]);
		close(pipe_p[1][0]);
		nonblock_rw(child, pipe_p[0][0], pipe_p[1][1], msg);
	}
	else if (pidnumber > 0)
	{
		close(pipe_p[0][0]);
		close(pipe_p[1][1]);
		nonblock_rw(parent, pipe_p[1][0], pipe_p[0][1], msg);
	}

}

