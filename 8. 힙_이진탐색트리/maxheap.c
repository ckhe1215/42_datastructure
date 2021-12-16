#include "maxheap.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap* createMaxHeap(int maxElementCount)
{
	MaxHeap* pHeap;

	if (maxElementCount <= 0)
		return (NULL);
	pHeap = malloc(sizeof(MaxHeap));
	if (!pHeap)
		return (NULL);
	pHeap->maxElementCount = maxElementCount;
	pHeap->currentElementCount = 0;
	pHeap->pElement = malloc(sizeof(MaxHeapNode) * (maxElementCount + 1));
	if (!pHeap->pElement)
		return (NULL);
	return (pHeap);
}

int insertMaxHeap(MaxHeap* pHeap, MaxHeapNode element)
{
	int i;

	if (!pHeap || isMaxHeapFull(pHeap))
		return (FALSE);
	pHeap->currentElementCount++;
	pHeap->pElement[pHeap->currentElementCount] = element;
	i = pHeap->currentElementCount;
	while (i > 1 && pHeap->pElement[i].data > pHeap->pElement[i / 2].data)
	{
		MaxHeapNode temp;
		temp = pHeap->pElement[i];
		pHeap->pElement[i] = pHeap->pElement[i / 2];
		pHeap->pElement[i / 2] = temp;
		i /= 2;
	}
	return (TRUE);
}

MaxHeapNode removeMaxHeap(MaxHeap* pHeap)
{
	MaxHeapNode pReturn;
	int i;

	if (!pHeap || isMaxHeapEmpty(pHeap))
		return ;
	pReturn = pHeap->pElement[1];
	pHeap->pElement[1] = pHeap->pElement[pHeap->currentElementCount];
	pHeap->currentElementCount--;
	i = 1;
	while (i * 2 <= pHeap->currentElementCount)
	{
		int max;
		max = i * 2;
		if (i * 2 + 1 <= pHeap->currentElementCount
			&& pHeap->pElement[i * 2].data < pHeap->pElement[i *  2 + 1].data)
			max++;
		if (pHeap->pElement[1].data < pHeap->pElement[max].data)
		{
			MaxHeapNode temp;
			temp = pHeap->pElement[1];
			pHeap->pElement[1] = pHeap->pElement[max];
			pHeap->pElement[max] = temp;
		}
		else
			break;
	}
	return (pReturn);
}

void deleteMaxHeap(MaxHeap* pHeap)
{
	if (!pHeap)
		return ;
	free(pHeap->pElement);
	free(pHeap);
}

int isMaxHeapFull(MaxHeap* pHeap)
{
	if (!pHeap)
		return (FALSE);
	return (pHeap->currentElementCount == pHeap->maxElementCount);
}

int isMaxHeapEmpty(MaxHeap* pHeap)
{
	if (!pHeap)
		return (FALSE);
	return (pHeap->currentElementCount == 0);
}

int main()
{
	MaxHeap* pHeap;
	MaxHeapNode pNode;

	pHeap = createMaxHeap(5);
	printf("%d\n", isMaxHeapEmpty(pHeap));
	printf("%d\n", isMaxHeapFull(pHeap));
	pNode.data = 6;
	insertMaxHeap(pHeap, pNode);
	pNode.data = 20;
	insertMaxHeap(pHeap, pNode);
	pNode.data = 4;
	insertMaxHeap(pHeap, pNode);
	pNode.data = 2;
	insertMaxHeap(pHeap, pNode);
	pNode.data = 12;
	insertMaxHeap(pHeap, pNode);
	printf("%d\n", removeMaxHeap(pHeap).data);
	printf("%d\n", removeMaxHeap(pHeap).data);
	printf("%d\n", removeMaxHeap(pHeap).data);
	printf("%d\n", removeMaxHeap(pHeap).data);
	printf("%d\n", removeMaxHeap(pHeap).data);
	// for (int i = 1; i <= pHeap->currentElementCount; i++) {
	// 	printf("%d ", pHeap->pElement[i].data);
	// }
	// printf("\n");
	printf("%d\n", isMaxHeapEmpty(pHeap));
	printf("%d\n", isMaxHeapFull(pHeap));
	deleteMaxHeap(pHeap);
}
