#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
	struct sigaction act;
	int i = 0;
	act.sa_handler = SIG_IGN;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	while(1) {
		printf("Time %d\n",i);
		sleep(1);
		i++;
	}
}

