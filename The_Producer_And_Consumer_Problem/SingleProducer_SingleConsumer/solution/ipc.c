#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <mqueue.h>

#include "ipc.h"


void* shm;
int mq_fd;
sem_t* sem1;
sem_t* empty;
sem_t* full;
sem_t* in_use;

static int getBuffer()
{
	int shmfd = shm_open(shmPath, O_RDWR | O_CREAT, 0600);
	ftruncate(shmfd, sizeof(char)*msgSize*maxMsg);
	if (shmfd < 0)
	{
		perror("shm_open");
		exit(-1);
	}
	else
		return shmfd;
}

void closeIPC()
{
	// Release POSIX Shared Memory
	munmap(shm, sizeof(char)*msgSize*maxMsg);

	// Release POSIX Message Queue
	mq_close(mq_fd);

	// Release POSIX Semaphore
	sem_close(sem1);
	sem_close(full);
	sem_close(empty);
}

void unlinkIPC()
{
	// Unlink POSIX Shared Memory
	shm_unlink(shmPath);

	// Unlink POSIX Message Queue
	mq_unlink(mqPath);

	// Unlink POSIX Semaphore
	sem_unlink(SEM1);
	sem_unlink(FULL);
	sem_unlink(EMPTY);
}

void initIPC()
{
	// POSIX Shared Memory
	int buffer_fd = getBuffer(shmPath);
	shm = mmap(NULL, sizeof(char)*msgSize*maxMsg, PROT_READ | PROT_WRITE, MAP_SHARED, buffer_fd, 0);
	close(buffer_fd);

	// POSIX Message Queue
	struct mq_attr attr;
	attr.mq_maxmsg = 2;
	attr.mq_msgsize = 100;
	mq_fd = mq_open(mqPath, O_RDWR | O_CREAT, 0600, &attr);

	// POSIX Semaphore
	sem1 = sem_open(SEM1, O_RDWR | O_CREAT, 0600, 0);
	full = sem_open(FULL, O_RDWR | O_CREAT, 0600, 0);
	empty = sem_open(EMPTY, O_RDWR | O_CREAT, 0600, maxMsg);
}


