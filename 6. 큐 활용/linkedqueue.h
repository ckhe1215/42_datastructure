#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include "simdef.h"

typedef struct QueueNodeType
{
	SimCustomer data;
	struct QueueNodeType* pLink;
} QueueNode;

typedef struct LinkedQueueType
{
	int currentElementCount;
	QueueNode* pFrontNode;
	QueueNode* pRearNode;
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int enqueueLQ(LinkedQueue* pQueue, QueueNode element);
QueueNode *dequeueLQ(LinkedQueue* pQueue);
QueueNode *peekLQ(LinkedQueue* pQueue);
void deleteLinkedQueue(LinkedQueue* pQueue);
int isLinkedQueueEmpty(LinkedQueue* pQueue);
void displayLinkedQueue(LinkedQueue* pQueue);

#define TRUE		1
#define FALSE		0

#endif
