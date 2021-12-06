/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrayqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:55:34 by hkim              #+#    #+#             */
/*   Updated: 2021/12/06 20:59:13 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

/*
큐 : 선입선출 자료구조. 먼저 들어간게 먼저나옴

배열로 구현한 선형 큐 단점
: 앞에서부터 원소들을 꺼내면 front가 뒤로 밀림
: 뒤의 원소들을 매번 앞으로 가져와야하기 때문에 비효율적

선형큐의 단점을 개선한 원형 큐
: 모듈러 연산으로 배열이 다 차면 앞에서부터 다시 저장

시간복잡도
: 위치가 정해져있기 때문에 삽입/삭제 O(1)
*/

ArrayQueue* createArrayQueue(int maxElementCount)
{
	ArrayQueue *queue;

	if (maxElementCount <= 0)
	{
		printf("maxElementCount가 너무 작습니다\n");
		return (NULL);
	}
	queue = malloc(sizeof(ArrayQueue));
	if (!queue)
	{
		printf("메모리 할당 실패 \n");
		return (NULL);
	}
	queue->maxElementCount = maxElementCount;
	queue->currentElementCount = 0;
	queue->front = 0;
	queue->rear = queue->maxElementCount - 1;
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
	pQueue->pElement[pQueue->rear] = element;
	pQueue->currentElementCount++;
	return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
	ArrayQueueNode* node;

	if (!pQueue)
		return (FALSE);
	if (isArrayQueueEmpty(pQueue))
	{
		printf("queue가 비어있음\n");
		return (FALSE);
	}
	node = &(pQueue->pElement[pQueue->front]);
	pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
	pQueue->currentElementCount--;
	return (node);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	ArrayQueueNode* node;

	if (!pQueue)
		return (FALSE);
	if (pQueue->currentElementCount == 0)
	{
		printf("queue가 비어있음\n");
		return (FALSE);
	}
	node = &(pQueue->pElement[pQueue->front]);
	return (node);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (!pQueue)
		return;
	free(pQueue->pElement);
	free(pQueue);
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	return (pQueue->currentElementCount == pQueue->maxElementCount);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	return (pQueue->currentElementCount == 0);
}

void displayArrayQueue(ArrayQueue* pQueue)
{
	if (!pQueue)
		return ;
	for (int i = 0; i < pQueue->currentElementCount; i++)
	{
		printf("%c\n", pQueue->pElement[(pQueue->front + i) % pQueue->currentElementCount].data);
	}
}

int main()
{
	ArrayQueue* queue;
	ArrayQueueNode node;

	queue = createArrayQueue(4);
	printf("isEmpty : %d\n", isArrayQueueEmpty(queue));
	printf("isFull : %d\n", isArrayQueueFull(queue));
	node.data = 'a';
	enqueueAQ(queue, node);
	node.data = 'b';
	enqueueAQ(queue, node);
	node.data = 'c';
	enqueueAQ(queue, node);
	node.data = 'd';
	enqueueAQ(queue, node);
	printf("%c\n", dequeueAQ(queue)->data);
	printf("%c\n", peekAQ(queue)->data);
	node.data = 'e';
	enqueueAQ(queue, node);

	printf("-----\n");
	displayArrayQueue(queue);
	printf("isEmpty : %d\n", isArrayQueueEmpty(queue));
	printf("isFull : %d\n", isArrayQueueFull(queue));
	printf("-----\n");

	dequeueAQ(queue);
	dequeueAQ(queue);
	dequeueAQ(queue);
	dequeueAQ(queue);

	printf("-----\n");
	displayArrayQueue(queue);
	printf("isEmpty : %d\n", isArrayQueueEmpty(queue));
	printf("isFull : %d\n", isArrayQueueFull(queue));
	printf("-----\n");
	deleteArrayQueue(queue);
}
