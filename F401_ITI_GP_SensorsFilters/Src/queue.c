#include <stdint.h>

#include "queue.h"

/**
 * @brief 					Function to initialize a queue from a circular array.
 * @param Copy_ps32FrontPtr Pointer to the index of the front element of the queue.
 * @param Copy_ps32RearPtr 	Pointer to the index of the rear element of the queue.
 */
void Queue_voidCircularArrayQueueInit(int *Copy_ps32FrontPtr, int *Copy_ps32RearPtr)
{
	/*Initializing Front and Rear*/
	*Copy_ps32FrontPtr = -1;
	*Copy_ps32RearPtr = -1;
}

/**
 * @brief				Function to check if the queue is full or not.
 * @param Copy_s32Front	Index of the front element of the queue.
 * @param Copy_s32Rear	Index of the rear element of the queue.
 * @param Copy_s32Size	Size of the queue.
 * @return				Checking Result.
 */
int Queue_s32CircularArrayQueueIsFull(int Copy_s32Front, int Copy_s32Rear, int Copy_s32Size)
{
	/*Defining Variables*/
	int Local_s32IsFull;

	/*Check if the Queue is full*/
	if(((Copy_s32Front == 0) && (Copy_s32Rear == (Copy_s32Size - 1))) || (Copy_s32Front == Copy_s32Rear + 1))
	{
		Local_s32IsFull = 1;
	}
	else
	{
		Local_s32IsFull = 0;
	}

	/*Return State of the Queue*/
	return Local_s32IsFull;
}

int Queue_s32CircularArrayQueueIsEmpty(int Front)
{
	/*Defining Variables*/
	int IsEmpty;

	/*Check if the Queue is full*/
	if(Front == -1)
	{
		IsEmpty = 1;
	}
	else
	{
		IsEmpty = 0;
	}

	/*Return State of the Queue*/
	return IsEmpty;
}

void Queue_voidCircularArrayQueueEnqueue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray, float NewElement)
{
	/*Defining Variables*/
	int IsFull = Queue_s32CircularArrayQueueIsFull(*FrontPtr, *RearPtr, Size);

	/*Check is the Queue is full*/
	if(IsFull == 1)
	{
		/*Do nothing*/
	}
	else
	{
		/*If it is the first insertion*/
		if(*FrontPtr == -1)
		{
			/*Move the two pointers*/
			*FrontPtr = 0;
		}

		/*If we reached the end of the array but still there is a place*/
		if(*RearPtr == (Size - 1))
		{
			*RearPtr = 0;
		}
		else
		{
			*RearPtr = *RearPtr + 1;
		}

		/*Enqueue Operation*/
		QueueArray[*RearPtr] = NewElement;
	}
}

void Queue_voidCircularArrayQueueDequeueEnqueue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray, float NewElement)
{
	/*Defining Variables*/
	int IsFull = Queue_s32CircularArrayQueueIsFull(*FrontPtr, *RearPtr, Size);

	/*Check is the Queue is full*/
	if(IsFull == 1)
	{
		/*Dequeue an element to empty a place*/
		Queue_s32CircularArrayQueueDequeue(FrontPtr, RearPtr, Size, QueueArray);
	}

	/*Enqueue the new element*/

		/*If it is the first insertion*/
		if(*FrontPtr == -1)
		{
			/*Move the two pointers*/
			*FrontPtr = 0;
		}

		/*If we reached the end of the array but still there is a place*/
		if(*RearPtr == (Size - 1))
		{
			*RearPtr = 0;
		}
		else
		{
			*RearPtr = *RearPtr + 1;
		}

		/*Enqueue Operation*/
		QueueArray[*RearPtr] = NewElement;
}

int Queue_s32CircularArrayQueueDequeue(int *FrontPtr, int *RearPtr, int Size, float *QueueArray)
{
	/*Defining Variables*/
	int IsEmpty = Queue_s32CircularArrayQueueIsEmpty(*FrontPtr);
	float FrontElement = 0;

	/*Check if the Queue is empty*/
	if(IsEmpty == 1)
	{
		/*Do nothing*/
	}
	else
	{
		/*Dequeue Operation*/
		FrontElement = QueueArray[*FrontPtr];

		/*If there is only one element in the array*/
		if((*FrontPtr) == (*RearPtr))
		{
			/*Reset front and rear to the initial condition*/
			*FrontPtr = -1;
			*RearPtr = -1;
		}
		/*If we reached the end of the array but still there are elements*/
		else if(*FrontPtr == (Size - 1))
		{
			*FrontPtr = 0;
		}
		else
		{
			*FrontPtr = *FrontPtr + 1;
		}
	}

	/*Return the First element of Queue*/
	return FrontElement;
}

int Queue_s32CircularArrayQueuePeek(int Front, int *QueueArray)
{
	/*Defining Variables*/
	int IsEmpty = Queue_s32CircularArrayQueueIsEmpty(Front);
	int FrontElement = 0;

	/*Check is the queue is empty*/
	if(IsEmpty == 1)
	{
		/*Do nothing*/
	}
	else
	{
		/*Return Last Queue Element*/
		FrontElement = QueueArray[Front];
	}

	/*Return the First element of Queue*/
	return FrontElement;
}

int Queue_s32CircularArrayQueueSize(int Front, int Rear, int Size)
{
	/*Defining Variables*/
	int QueueSize;

	if(Front == -1)
	{
		QueueSize = 0;
	}
	else if(Rear >= Front)
	{
		QueueSize = Rear - Front + 1;
	}
	else if(Front > Rear)
	{
		QueueSize = (Size - Front) + (Rear + 1);
	}

	/*Return StackSize*/
	return QueueSize;
}
