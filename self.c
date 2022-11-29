#include <signal.h>
int main() {
	raise(SIGFPE);
}

