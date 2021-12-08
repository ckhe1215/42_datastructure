#include "linkedqueue.h"
#include <stdlib.h>
#include <stdio.h>

LinkedQueue* createLinkedQueue()
{
	LinkedQueue* pQueue;

	pQueue = malloc(sizeof(LinkedQueue));
	if (!pQueue)
		return (NULL);
	return (pQueue);
}

int enqueueLQ(LinkedQueue* pQueue, QueueNode element)
{
	QueueNode* pNode;

	if (!pQueue)
		return (FALSE);
	pNode = malloc(sizeof(QueueNode));
	if (!pNode)
		return (FALSE);
	*pNode = element;
	if (isLinkedQueueEmpty(pQueue))
	{
		pQueue->pFrontNode = pNode;
		pQueue->pRearNode = pNode;
	}
	else
	{
		pQueue->pRearNode->pLink = pNode;
		pQueue->pRearNode = pNode;
	}
	pQueue->currentElementCount++;
	return (TRUE);
}

QueueNode *dequeueLQ(LinkedQueue* pQueue)
{
	QueueNode *pReturn;

	if (!pQueue || isLinkedQueueEmpty(pQueue))
		return (NULL);
	pReturn = pQueue->pFrontNode;
	pQueue->pFrontNode = pQueue->pFrontNode->pLink;
	pReturn->pLink = NULL;
	if (pQueue->currentElementCount == 1)
	{
		pQueue->pRearNode = NULL;
	}
	pQueue->currentElementCount--;
	return (pReturn);
}

QueueNode *peekLQ(LinkedQueue* pQueue)
{
	if (!pQueue || isLinkedQueueEmpty(pQueue))
		return (NULL);
	return (pQueue->pFrontNode);
}

void deleteLinkedQueue(LinkedQueue* pQueue)
{
	if (!pQueue)
		return ;
	while (pQueue->pFrontNode)
	{
		free(dequeueLQ(pQueue));
	}
	free(pQueue);
}

int isLinkedQueueEmpty(LinkedQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	return (pQueue->currentElementCount == 0);
}

void displayLinkedQueue(LinkedQueue* pQueue)
{
	QueueNode* pNode;

	if (!pQueue)
		return ;
	pNode = pQueue->pFrontNode;
	while (pNode)
	{
		printf("%d\n", pNode->data.arrivalTime);
		pNode = pNode->pLink;
	}
}

// int main()
// {
// 	LinkedQueue* queue = createLinkedQueue();
// 	QueueNode node;
// 	node.data = 'a';
// 	enqueueLQ(queue, node);
// 	node.data = 'b';
// 	enqueueLQ(queue, node);
// 	node.data = 'c';
// 	enqueueLQ(queue, node);
// 	node.data = 'd';
// 	enqueueLQ(queue, node);
// 	printf("%c\n", dequeueLQ(queue)->data);
// 	printf("%c\n", peekLQ(queue)->data);
// 	node.data = 'e';
// 	enqueueLQ(queue, node);
// 	displayLinkedQueue(queue);
// }
