#include <stdio.h>
#include <signal.h>

int isalarm_on = 0;
void alarm(int sig) {
	isalarm_on = 5;
}

int main() {
	struct sigaction act;
	act.sa_handler = alarm;
	sigaction(SIGALRM, &act, NULL);
	alarm (2);
	if (isalarm_on==5) printf("alarm on\n");
}
	
