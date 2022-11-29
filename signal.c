#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo) {
	printf("signo=%d\n", signo);
}

int main() {
	struct sigaction act;
	int i = 0;
	act.sa_handler = handler;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	while(1) {
		printf("time : %d\n",i);
		sleep(1);
		i++;
	}
}

