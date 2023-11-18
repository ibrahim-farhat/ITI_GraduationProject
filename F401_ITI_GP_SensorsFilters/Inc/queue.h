#ifndef QUEUE_H_
#define QUEUE_H_


/*Functions' Prototypes*/
/*Fuction to initialize a Queue of Circular array*/
void Queue_voidCircularArrayQueueInit(int *FrontPtr, int *RearPtr);
/*Fuction to check if the Queue of Circular array is full*/
int Queue_s32CircularArrayQueueIsFull(int Front, int Rear, int Size);
/*Fuction to check if the Queue of Circular array is empty*/
int Queue_s32CircularArrayQueueIsEmpty(int Front);
/*Function to push into a Queue of Circular array*/
void Queue_voidCircularArrayQueueEnqueue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray, float NewElement);
/*Function to pop from a Queue of Circular array*/
int Queue_s32CircularArrayQueueDequeue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray);
/*Function to peek from a Queue or Circular array*/
int Queue_s32CircularArrayQueuePeek(int Front, int *QueueArray);
/*Function to return number of Circular array Queue elements*/
int Queue_s32CircularArrayQueueSize(int Front, int Rear, int Size);

void Queue_voidCircularArrayQueueDequeueEnqueue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray, float NewElement);




#endif
