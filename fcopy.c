#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

#define SHMSIZE 10000

#define SHMNAME "/SystemRepository"
#define SEMNAME "/1"

void p(sem_t *semd) {
	int ret;
	if ((ret = sem_trywait(semd)) != 0 && errno == EAGAIN)sem_wait(semd);
	else if (ret != 0) {
		perror ("sem_trywait failed");
		exit (1);
	}
}

void v(sem_t *semd) {
	if (sem_post(semd) != 0) {
		perror ("sem_post failed");
		exit (1);
	}
}


int main(int argc, char* argv[])
{
	int status, shmd, count;
	int i, val;
	char *path = argv[1];
	char buf[SHMSIZE];
	FILE *fp, *copy_fp;
	void *shmaddr;
	pid_t pid;
	sem_t *semd;
	semd = sem_open(SEMNAME, O_CREAT, 0600, 1);
	sem_getvalue(semd, &val);
	memset(buf, 0, SHMSIZE);
	if((pid = fork()) == 0){
		shmd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666);
		ftruncate(shmd, SHMSIZE);
		shmaddr = mmap(0, SHMSIZE, PROT_WRITE, MAP_SHARED, shmd, 0);
		fp = fopen(path, "r");
		mlock(shmaddr, SHMSIZE);
		p(semd);
		printf("Child use semaphore\n");
		while(feof(fp) != 0){
			count = fread(buf, sizeof(char), SHMSIZE, fp);
			strcpy((char *)shmaddr, buf);
		}
		v(semd);
		printf("Child not use semaphore\n");
		munmap(shmaddr, SHMSIZE);
		fclose(fp);
		close(shmd);
		exit(0);
	}
	else if (pid > 0){
		pid = wait(&status);
		shmd = shm_open(SHMNAME, O_RDWR, 0666);
		shmaddr = mmap(0, SHMSIZE, PROT_READ, MAP_SHARED, shmd, 0);
		mlock(shmaddr, SHMSIZE);
		strcat(path,"_copy");
		copy_fp = fopen(path, "w");
		p(semd);
		printf("Parents use semaphore\n");
		fwrite(shmaddr, sizeof(char), SHMSIZE, copy_fp);
		fclose(copy_fp);
		munmap(shmaddr, SHMSIZE);
		printf("Parents not use semaphore\n");
		v(semd);
		close(shmd);
		shm_unlink(SHMNAME);
		sem_close(semd);
	}

}

