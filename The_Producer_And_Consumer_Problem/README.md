# The Producer and Consumer Problem

The Producer and Consumer Problem is a famous problem about process synchronization in computer science. In these problem, there are usually 2 types of processes: one of them being the Producer process and the other one being the Consumer process. 

The Producer process is responsible for producing items while the Consumer process consumes the items. The only issue here is that the Producer Process and the Consumer Process is running concurrently without any guaranteed order. The following situations could happen:
* Suppose the Producer Process runs first and it produce and store one item in the buffer. Then, the Consumer Process runs and consumes the item in the buffer. In this situation, it would be completely fine. Other situations might not be so lucky.
* Suppose the Consumer Process runs first. The Consumer Process would try to consume an item out of an empty buffer, which might lead to failure if no synchronization or no check is performed.
* Suppose the Producer Process runs first and keeps running while the Consumer Process is either too slow or so unlucky that it doesn't get a chance to run. In this case, since the buffer is limited in size, the Producer Process would eventually produce enough items that fill the buffer entirely. If the Producer Process continues to produce items without any synchronization and any checks, the program might fail after trying to put another item in a full buffer.
* Suppose the Producer and Consumer Process runs in an interleaved manner. There are many situations that could occur depending on whether the Producer Process or the Consumer Process is faster. 
  * If the Producer Process is faster, then the buffer will gradually be full. 
  * If the Consumer Process is faster, then the buffer will gradually be empty. 
  * There could also be situations like: the Consumer Process runs faster at one moment while the Producer Process runs faster at the next moment.
* ... Many other situations might occur

The thing is: the two processes run concurrently and run in no guaranteed order. Their behaviors are not consistent and might change during the whole execution time. Our task is to synchronize the Producer Processes and Consumer Processes using either POSIX or System V IPC in C.

## Prompt 1: Single Producer and Single Consumer
[click to see prompt1](https://github.com/tezktenr/Tezktenr-IPC-Practice-Projects/tree/main/The_Producer_And_Consumer_Problem/SingleProducer_SingleConsumer)
