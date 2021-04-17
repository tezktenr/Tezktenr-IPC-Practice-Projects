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
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>

#include "ipc.h"
#include "buf_util.h"

extern void* shm;
extern int mq_fd;
extern sem_t* sem1;
extern sem_t* full;
extern sem_t* empty;

char* buf;

static int Running = 1;

void* waitForFinish()
{
	char msgbuf[1024];
	while (Running)
	{
		mq_receive(mq_fd, msgbuf, 1024, NULL);
		if (strcmp(msgbuf, END) == 0)
		{
			int currVal;
			sem_getvalue(full, &currVal);
			while (currVal != 0)
				sem_getvalue(full, &currVal);
			Running = 0;
		}
	}
	return 0;
}

void consumerSay(const char* str)
{
	printf("[Consumer] %s\n", str);
}

void Consumer()
{
	// opening the output file
	FILE* output = fopen("output.txt", "w+");
	

	buf = (char*) shm;

	pthread_t daemonTID;
	pthread_create(&daemonTID, NULL, waitForFinish, NULL);

	struct timespec ts;
	ts.tv_sec = 2;
	ts.tv_nsec = 0;


	int currIndex = 0;
	int lineNum = 1;
	char processedLine[2000];
	while (Running)
	{
		int status = sem_timedwait(full, &ts);
		if (status == -1 && errno == ETIMEDOUT)
		{
			if (Running)
				continue;
			else
				break;
		}
		sprintf(processedLine, "[Line %d] %s", lineNum++, getMsgAtIndex(currIndex, buf));
		consumerSay(processedLine);
		fprintf(output, "%s\n", processedLine);		
		currIndex = (currIndex + 1) % maxMsg;
		sem_post(empty);
	}

	fclose(output);
}


int main()
{
	consumerSay("started");
	initIPC();
	Consumer();
	closeIPC();
	unlinkIPC();
	return 0;
}
