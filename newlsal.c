#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	pid_t pidnumber;
	pidnumber = fork();
	
	if(pidnumber == 0)
	{
		execvp(argv[1], argv+1);
	}
	else if(pidnumber > 0)
	{
		wait((int*)0);
		exit(0);
	}

}
