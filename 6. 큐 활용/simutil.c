#include "simutil.h"
#include <stdlib.h>

void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
	QueueNode pNode;

	pNode.data.arrivalTime = arrivalTime;
	pNode.data.serviceTime = processTime;
	pNode.data.status = arrival;
	pNode.pLink = NULL;
	enqueueLQ(pQueue, pNode);
}

void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{

}

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{

}

QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
						int *pServiceUserCount, int *pTotalWaitTime)
{

}

void printSimCustomer(int currentTime, SimCustomer customer)
{

}

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{

}

void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime)
{

}
