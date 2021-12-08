#include "simutil.h"
#include <stdlib.h>
#include <stdio.h>

void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
	QueueNode pNode;

	if (!pQueue)
		return ;
	pNode.data.arrivalTime = arrivalTime;
	pNode.data.serviceTime = processTime;
	pNode.data.status = arrival;
	pNode.data.startTime = -1;
	pNode.data.endTime = -1;
	pNode.pLink = NULL;
	enqueueLQ(pQueue, pNode);
}

void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
	QueueNode *pNode;

	if (!pArrivalQueue || !pWaitQueue)
		return ;
	pNode = dequeueLQ(pArrivalQueue);
	enqueueLQ(pWaitQueue, *pNode);
}

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
	QueueNode* serviceNode;

	if (!pWaitQueue || isLinkedQueueEmpty(pWaitQueue))
		return (NULL);
	serviceNode = dequeueLQ(pWaitQueue);
	serviceNode->data.startTime = currentTime;
	serviceNode->data.endTime = currentTime + serviceNode->data.serviceTime;
	serviceNode->data.status = start;
	return (serviceNode);
}

QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
						int *pServiceUserCount, int *pTotalWaitTime)
{
	if (!pServiceNode || !pServiceUserCount || !pTotalWaitTime)
		return (NULL);
	if (currentTime == pServiceNode->data.endTime)
	{
		pServiceNode->data.status = end;
		*pTotalWaitTime += pServiceNode->data.startTime - pServiceNode->data.arrivalTime;
		*pServiceUserCount += 1;
	}
	return (pServiceNode);
}

void printSimCustomer(int currentTime, SimCustomer customer)
{
	printf("status : %d\n", customer.status);
	printf("arrive : %d\n", customer.arrivalTime);
	printf("service : %d\n", customer.serviceTime);
}

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
	QueueNode* pNode;

	if (!pWaitQueue)
		return ;
	pNode = pWaitQueue->pFrontNode;
	while (pNode)
	{
		printf("current time : %d\n", currentTime);
		printSimCustomer(currentTime, pNode->data);
		pNode = pNode->pLink;
		printf("=======================\n");
	}
}

void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime)
{
	printf("시간 / 사람 : %d / %d\n", totalWaitTime, serviceUserCount);
	printf("평균 대기시간 : %d\n", totalWaitTime / serviceUserCount);
}
