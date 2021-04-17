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

#include "ipc.h"
#include "buf_util.h"

extern void* shm;
extern int mq_fd;
extern sem_t* sem1;
extern sem_t* full;
extern sem_t* empty;

char* buf;

void producerSay(const char* str)
{
	printf("[Producer] %s\n", str);
}

void signalConsumer(const char* msg)
{
	int status = mq_send(mq_fd, msg, strlen(msg), 0);
	if (status < 0)
	{
		producerSay(strerror(errno));
		exit(-1);
	}
}

void producerError(const char* err)
{
	producerSay(err);
	signalConsumer(END);
	closeIPC();	
	exit(-1);
}


void Producer()
{
	// setting buf to point to the shared memory
	buf = (char*) shm;

	// open the file
	FILE* article_file = fopen("article.txt", "r");
	if (article_file == NULL)
		producerError(strerror(errno));


	int currIndex = 0;
	char line[msgSize];
	while (fgets(line, msgSize, article_file) != NULL)
	{
		line[strcspn(line, "\n")] = 0;
		sem_wait(empty);
		// producerSay(line);
		strcpy(getMsgAtIndex(currIndex, buf), line);
		currIndex = (currIndex+1) % maxMsg;
		sem_post(full);
	}
	fclose(article_file);
}


int main()
{
	producerSay("started");
	initIPC();
	Producer();
	signalConsumer(END);
	closeIPC();
	return 0;
}
