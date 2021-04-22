# Single Producer and Single Consumer Problem

In this project, there should be two main C files: "producer.c" and "consumer.c", which are then compiled and run separately. If you want, you could have other C files or header files, which can be linked with "producer.c" and "consumer.c". There should be only 2 executables after compilation.

You would also need to write a bash script (e.g. "run.sh"), where you could write commands to run the Producer Process and the Consumer Process in background.

## Am I allowed to use Thread in each process?

Yes, you are allowed to use Thread in each process. But even if you use thread, there should be only 1 Producer Process and only 1 Consumer Process for this problem.

## What IPC objects are allowed in this project?

* One POSIX Shared Memory object
* One POSIX Message Queue object
* As many POSIX Semaphore objects as you want

Note: You could also choose to use the System V IPC objects instead for this project.

## The Buffer

In this project, you must use the POSIX Shared Memory with "mmap()" to create the buffer that will be used by the Producer and Consumer Process. 

Note: You are **NOT ALLOWED** to use the POSIX Message Queue to store the main data, which refer to the data produced by the Producer and consumed by the Consumer. The POSIX Message Queue should only be used to notify another process about program status or to exchange metadata.

The buffer should hold an array of C-String. You should manually utilize pointer arithmetic to implement an array in the shared memory. For example, if `char* buf` points to the start of the shared memory region and assume each item in the array is consisted of 1024 characters, then, to select the element at index 2 in the array, you would write `buf+2*1024`.

You may assume that each item in the buffer would contain less than or equal to 1024 characters. There should be less than or equal to 20 items in the buffer at one time.

## The Producer Process

The Producer Process should read the file "article.txt", which is provided [here](https://github.com/tezktenr/Tezktenr-IPC-Practice-Projects/blob/main/The_Producer_And_Consumer_Problem/SingleProducer_SingleConsumer/article.txt). As can be seen, the "article.txt" is a text file that contains many lines of string. The Producer Process should open this file and read each line of the file. That is, the Producer Process should put lines into the buffer 1 line at a time. When the Consumer Process tries to consume from the buffer, it should read out 1 line at a time. 

Note: In this project, a newline is defined as when a END-OF-LINE character ('\n') is met. Note that the "line" here is different from the "lines" concept in some of the famous app, like Microsoft Word. For example, in Microsoft Word, the number of lines refer to how many rows on the Display Screen the paragraph occupy.

When all lines in the files are processed by the Producer Process, the Producer Process should utilize a POSIX Message Queue to send a message "END" to the Consumer Process, indicating that the Producer Process have finished sending all the lines. Then, the Producer Process should exit. All resources used should be closed gracefully.

## The Consumer Process

The Consumer Process should monitor the buffer constantly. Once the buffer has a new item, it should try to consume it as immediate as possible.

For each line read out from the buffer, the Consumer Process should do the following:

1.	Prepend to the line with its line number in the format of "[Line %d]". 

	For example, if the "article.txt" is as follows:
	```
	Hi, this is the first line.
	You now see the second line.
	Ohh, the third line is here
	Ha, the final line, which is the 4th line
	```
	After processing each line, the Consumer Process should have something like below:
	```
	[Line 1] Hi, this is the first line.
	[Line 2] You now see the second line.
	[Line 3] Ohh, the third line is here
	[Line 4] Ha, the final line, which is the 4th line
	```

	Note: For practicing purpose, it's not important to get the exact format correct here as long as the correct line number is prepended to each line.

2.	For each processed line, print it to the console
3. 	For each processed line, write it to a file named "output.txt". If "output.txt" already exists, clear the original contents of the file before writing to it. The "output.txt" file should be located in the same directory as "main.c".

Once the Consumer Process sees that there is a message in the POSIX Message Queue, it checks whether the message is equal to "END". If the message is indeed "END", it indicates that the Producer Process has finished processing all lines. After that, the Consumer Process should finish processing all the remaining items in the buffer. Once the buffer becomes empty in this case, the Consumer Process should exit. All resources used should be closed gracefully.

## Release All Resources and Terminate Gracefully
After both the Producer and Consumer process finish, all IPC objects and file descriptor should be closed. All allocated memory should be released and there should be no memory leak. Moreover, all IPC objects should be unlinked, meaning that all IPC objects should be removed after both processes exit. 
* The directory "/dev/shm" contains all the POSIX Shared Memory object in the system
* The directory "/dev/mq" or "/dev/mqueue" contains all the POSIX Message Queue object in the system
* The directory "/dev/shm" contains all the POSIX Semaphore object in the system (the semaphore object differs from the shared memory object in that all semaphore object files started with the "sem.xxx" filename)

## Extra: Handling Error
Since both the Producer and Consumer Process could encounter unexpected error. If one process exits due to error, the other one might not be correctly notified. In this case, one of the process might be stuck and never exit while the other one is forcibly terminated by error.

For example, if the Producer Process accesses invalid memory and is forcibly terminated, the Consumer Process might not be notified about that and keeps waiting for the data from Producer Process. In this case, the Consumer Process will never terminate and occupies system resources. 

Our final task is to gracefully handle these kinds of situations.

