#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	pid_t pidnumber;
	pidnumber = fork();
	if (pidnumber> 0)printf("parent\n");
	else printf("child");	
}
