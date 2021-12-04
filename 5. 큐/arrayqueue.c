/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrayqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:55:34 by hkim              #+#    #+#             */
/*   Updated: 2021/12/04 04:40:04 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

ArrayQueue* createArrayQueue(int maxElementCount)
{
	if (maxElementCount <= 0)
	{
		printf("maxElementCount가 너무 작습니다\n");
		return (NULL);
	}
	ArrayQueue *queue = malloc(sizeof(ArrayQueue)); // 이거 꼭 동적할당 해야되나
	if (!queue)
	{
		printf("메모리 할당 실패 \n");
		return (NULL);
	}
	queue->maxElementCount = maxElementCount;
	queue->currentElementCount = 0;
	queue->front = 0;
	queue->rear = 0;
	queue->pElement = malloc(sizeof(ArrayQueueNode) * maxElementCount);
	if (!(queue->pElement))
	{
		printf("메모리 할당 실패 \n");
		return (NULL);
	}
	return queue;
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	if (!pQueue)
		return (FALSE);
	if (isArrayQueueFull(pQueue))
	{
		printf("queue가 가득 찼음\n");
		return (FALSE);
	}
	pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount;
	pQueue->pElement[pQueue->rear] = element; // 이게 맞나
	pQueue->currentElementCount++; // rear가 있어서 사실 cur가 필요없지 않나
	return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	if (isArrayQueueEmpty(pQueue))
	{
		printf("queue가 비어있음\n");
		return (FALSE);
	}
	pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
	ArrayQueueNode* node = &(pQueue->pElement[pQueue->front]);
	pQueue->currentElementCount--;
	return (node);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	if (pQueue->currentElementCount == 0)
	{
		printf("queue가 비어있음\n");
		return (FALSE);
	}
	ArrayQueueNode* node = &(pQueue->pElement[pQueue->front]);
	return (node);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (!pQueue)
		return;
	free(pQueue->pElement);
	pQueue->pElement = NULL;
	free(pQueue);
	pQueue = NULL;
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	return (pQueue->currentElementCount == pQueue->maxElementCount);
	// return ((pQueue->rear + 1) % pQueue->maxElementCount == pQueue->front);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	return (pQueue->currentElementCount == 0);
	// return (pQueue->front == pQueue->rear);
}

int main()
{
	ArrayQueue* queue = createArrayQueue(4);
	printf("isEmpty : %d\n", isArrayQueueEmpty(queue));
	printf("isFull : %d\n", isArrayQueueFull(queue));
	ArrayQueueNode node;
	node.data = 'a';
	enqueueAQ(queue, node);
	node.data = 'b';
	enqueueAQ(queue, node);
	node.data = 'c';
	enqueueAQ(queue, node);
	node.data = 'd';
	enqueueAQ(queue, node);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("%c\n", dequeueAQ(queue)->data);
	node.data = 'e';
	enqueueAQ(queue, node);
	node.data = 'f';
	enqueueAQ(queue, node);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("isEmpty : %d\n", isArrayQueueEmpty(queue));
	printf("isFull : %d\n", isArrayQueueFull(queue));
}
