#include "simutil.h"
#include <stdlib.h>
#include <stdio.h>

#define ENDTIME 15

int main()
{
	int t;
	int pServiceUserCount = 0;
	int pTotalWaitTime = 0;
	LinkedQueue* pArrivalQueue;
	LinkedQueue* pWaitQueue;
	QueueNode* serviceNode;

	t = 0;
	pArrivalQueue = createLinkedQueue();
	pWaitQueue = createLinkedQueue();
	insertCutomer(0, 3, pArrivalQueue);
	insertCutomer(2, 2, pArrivalQueue);
	insertCutomer(4, 1, pArrivalQueue);
	insertCutomer(6, 1, pArrivalQueue);
	insertCutomer(8, 3, pArrivalQueue);
	while (t < ENDTIME)
	{
		// 도착 큐에서 하나 peek해서 현재시간이 도착시간이면 대기큐에 넣는다
		if (peekLQ(pArrivalQueue) && peekLQ(pArrivalQueue)->data.arrivalTime == t)
			processArrival(t, pArrivalQueue, pWaitQueue);
		if (serviceNode)
			serviceNode = processServiceNodeEnd(t, serviceNode, &pServiceUserCount, &pTotalWaitTime);
		if (!serviceNode || serviceNode->data.status != start)
			serviceNode = processServiceNodeStart(t, pWaitQueue);
		printWaitQueueStatus(t, pWaitQueue);
		t++;
	}
	printReport(pWaitQueue, pServiceUserCount, pTotalWaitTime);
}
