#ifndef IPC_ID
#define IPC_ID

// Message Constant
#define END "END"

// buffer related params
#define maxMsg 20
#define msgSize 1024

// POSIX shared memory
#define shmPath "/shm_producer_consumer"


// POSIX message queue
#define mqPath "/mq_producer_consumer"

// POSIX semaphore
#define SEM1 "/sem1"
#define FULL "/full"
#define EMPTY "/empty"

void initIPC(void);
void closeIPC(void);
void unlinkIPC(void);

#endif
