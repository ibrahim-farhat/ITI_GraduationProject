#ifndef QUEUE_H_
#define QUEUE_H_


/*Functions' Prototypes*/
/*Fuction to initialize a Queue of Circular array*/
void Queue_voidCircularArrayQueueInit(sint32 *FrontPtr, sint32 *RearPtr);
/*Fuction to check if the Queue of Circular array is full*/
sint32 Queue_s32CircularArrayQueueIsFull(sint32 Front, sint32 Rear, sint32 Size);
/*Fuction to check if the Queue of Circular array is empty*/
sint32 Queue_s32CircularArrayQueueIsEmpty(sint32 Front);
/*Function to push into a Queue of Circular array*/
void Queue_voidCircularArrayQueueEnqueue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray, f32 NewElement);
/*Function to pop from a Queue of Circular array*/
sint32 Queue_s32CircularArrayQueueDequeue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray);
/*Function to peek from a Queue or Circular array*/
sint32 Queue_s32CircularArrayQueuePeek(sint32 Front, sint32 *QueueArray);
/*Function to return number of Circular array Queue elements*/
sint32 Queue_s32CircularArrayQueueSize(sint32 Front, sint32 Rear, sint32 Size);

void Queue_voidCircularArrayQueueDequeueEnqueue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray, f32 NewElement);




#endif
