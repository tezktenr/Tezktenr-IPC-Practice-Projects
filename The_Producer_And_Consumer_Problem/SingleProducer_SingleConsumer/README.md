# Single Producer and Single Consumer Problem

Create a single "main.c" file for this project. 

## How to Create new Processes?

You might use "fork()" to create the Producer and Consumer processes. Only 1 Producer process and only 1 Consumer process is needed for this project. There should be technically 3 processes: the main process, which then forks off the Producer process and the Consumer Process. The main process should not exit before the Producer Process and the Consumer Process.

## Am I allowed to use Thread in each process?

Yes, you are allowed to use Thread in each process. But even if you use thread, there should be only 1 Producer Process and only 1 Consumer Process for this problem.

## What IPC objects are allowed in this project?

* One POSIX Shared Memory object
* One POSIX Message Queue object
* As many POSIX Semaphore objects as you want

## The Producer Process

The Producer Process should read the file "article.txt", which is provided here -> link. As can be seen, the "article.txt" is a text file that contains many lines of string. The Producer Process should open this file and read each line of the file. That is, the Producer Process should put each line into the buffer 1 line at a time. When the Consumer Process tries to consume from the buffer, it should read out 1 line at a time. 

When all lines in the files are processed by the Producer Process, the Producer Process should utilize a POSIX Message Queue to send a message "END" to the Consumer Process. Then, the Producer Process should exit.

## The Consumer Process

The Consumer Process should probe the buffer constantly. Once the buffer has a new item, it should try to consume it as immediate as possible.

For each line read out from the buffer, the Consumer Process should do the following:
	1.	Prepend to the line with its line number in the format of "[Line %d]". 

For example, if the "article.txt" is as follows:
+------------------------------------------------------------
|Hi, this is the first line.
|You now see the second line.
|Ohh, the third line is here
|Ha, the final line, which is the 4th line

After processing each line, the Consumer Process should have something like below:
+------------------------------------------------------------
|[Line 1] Hi, this is the first line.
|[Line 2] You now see the second line.
|[Line 3] Ohh, the third line is here
|[Line 4] Ha, the final line, which is the 4th line

Note: For practicing purpose, it's not important to get the exact format correct here as long as the correct line number is prepended to each line.

	2.	For each processed line, print it to the console
	3. 	For each processed line, write it to a file named "output.txt". The "output.txt" file should be located in the same directory as "main.c".

Once the Consumer Process sees that there is a message in the POSIX Message Queue, it checks whether the message is equal to "END". If the message is indeed "END", it indicates that the Producer Process has finished processing all lines. Thus, the Consumer Process should finish processing all the remaining items in the buffer. Once the buffer becomes empty in this case, the Consumer Process should exit.

## The Buffer

In this project, you would need to use POSIX Shared Memory with "mmap()" to create the buffer that will be used by the Producer and Consumer Process. The buffer should be an array of C-String. 

You may assume that each line would contain less than or equal to 1024 characters. There should be less than or equal to 20 lines in the buffer at the same time.
