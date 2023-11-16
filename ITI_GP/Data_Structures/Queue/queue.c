#include "../../Common/STD_TYPES.h"

#include "queue.h"
#include <util/delay.h>

void Queue_voidCircularArrayQueueInit(sint32 *FrontPtr, sint32 *RearPtr)
{
	/*Initializing Front and Rear*/
	*FrontPtr = -1;
	*RearPtr = -1;
}

sint32 Queue_s32CircularArrayQueueIsFull(sint32 Front, sint32 Rear, sint32 Size)
{
	/*Defining Variables*/
	sint32 IsFull;

	/*Check if the Queue is full*/
	if(((Front == 0) && (Rear == (Size - 1))) || (Front == Rear + 1))
	{
		IsFull = 1;
	}
	else
	{
		IsFull = 0;
	}

	/*Return State of the Queue*/
	return IsFull;
}

sint32 Queue_s32CircularArrayQueueIsEmpty(sint32 Front)
{
	/*Defining Variables*/
	sint32 IsEmpty;

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

void Queue_voidCircularArrayQueueEnqueue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray, f32 NewElement)
{
	/*Defining Variables*/
	sint32 IsFull = Queue_s32CircularArrayQueueIsFull(*FrontPtr, *RearPtr, Size);

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

void Queue_voidCircularArrayQueueDequeueEnqueue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray, f32 NewElement)
{
	/*Defining Variables*/
	sint32 IsFull = Queue_s32CircularArrayQueueIsFull(*FrontPtr, *RearPtr, Size);

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

sint32 Queue_s32CircularArrayQueueDequeue(sint32 *FrontPtr, sint32 *RearPtr, sint32 Size, f32 *QueueArray)
{
	/*Defining Variables*/
	sint32 IsEmpty = Queue_s32CircularArrayQueueIsEmpty(*FrontPtr);
	f32 FrontElement = 0;

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

sint32 Queue_s32CircularArrayQueuePeek(sint32 Front, sint32 *QueueArray)
{
	/*Defining Variables*/
	sint32 IsEmpty = Queue_s32CircularArrayQueueIsEmpty(Front);
	sint32 FrontElement = 0;

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

sint32 Queue_s32CircularArrayQueueSize(sint32 Front, sint32 Rear, sint32 Size)
{
	/*Defining Variables*/
	sint32 QueueSize;

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

//void CircularArrayQueueDisplay(sint32 Front, sint32 Rear, sint32 Size, sint32 *QueueArray)
//{
//	/*Defining Variables*/
//	sint32 i;
//	sint32 IsEmpty = CircularArrayQueueIsEmpty(Front);
//
//	if(IsEmpty != 1)
//	{
//		/*if the Rear precedes the Front*/
//		if(Rear >= Front)
//		{
//			/*Pirnting the queue elements*/
//			for(i = Front; i <= Rear; i++)
//			{
//				printf("%d\t", QueueArray[i]);
//			}
//		}
//
//		/*Else if the Front precedes the Rear*/
//		else if(Rear < Front)
//		{
//			/*Pirnting the queue elements*/
//			for(i = Front; i < Size; i++)
//			{
//				printf("%d\t", QueueArray[i]);
//			}
//
//			for(i = 0; i <= Rear; i++)
//			{
//				printf("%d\t", QueueArray[i]);
//			}
//		}
//
//		/*Printing New Line*/
//		printf("\n");
//	}
//}
