#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define PASSWORDSIZE 12
typedef unsigned long long int tick64_t;
typedef unsigned long int tick32_t;

tick32_t GetTickCount()
{
	tick32_t tick = 0ul;
	#if defined(WIN32) || defined(WIN64)
	tick = GetTickCount();
	#else
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	tick = (ts.tv_sec*1000ul) + (ts.tv_nsec/1000ul/1000ul);
	#endif
	return tick;
}

int main(void) {
	int fd, start;
	int nread, cnt=0, cnt1=0, errcnt=0;
	double typing_msec, typing_sec, typing_per_sec;
	char ch,ch1;
	char line[]= {"20183207 KimSeongChan"};
	struct termios init_attr, new_attr;
	fd = open(ttyname(fileno(stdin)), O_RDWR); tcgetattr(fd, &init_attr);
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO; /* ~(ECHO | ECHOE | ECHOK | ECHONL); */
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	printf("write this sentence.\n%s\n", line);
	start = GetTickCount();
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == line[cnt++]) write(fd, &ch, 1);
		else {
			write(fd, "*", 1); 
			errcnt++;
		}
	}
	typing_msec = GetTickCount() - start;
	typing_sec = fmod((typing_msec/1000), 60);
	typing_per_sec = (sizeof(line) / sizeof(int)) / typing_sec;
	printf("\nerror %d\n", errcnt);
	printf(" %d steersman.\n\n", (int)(typing_per_sec*60));
	printf("\ntime : %.3lf sec\n", typing_sec);
	tcsetattr(fd, TCSANOW, &init_attr);
	close(fd);
}
