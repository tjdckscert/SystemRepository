#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pidnumber;
	int status, exit_status;
	pidnumber =fork();
	
	if (pidnumber == 0) {
		sleep(2);
		exit(0);
	}
	
	if (WIFEXITED(status)) {
		exit_status = WEXITSTATUS(status);
		printf("Exit from %d was exit = %d\n", pidnumber, exit_status);
	}
	exit(0);
}

