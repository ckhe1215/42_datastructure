/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkeddeque.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 04:28:44 by hkim              #+#    #+#             */
/*   Updated: 2021/12/04 23:25:32 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkeddeque.h"
#include <stdio.h>
#include <stdlib.h>

/*
typedef struct DequeNodeType
{
	char data;
	struct DequeNodeType* pRLink;
	struct DequeNodeType* pLLink;
} DequeNode;

typedef struct LinkedDequeType
{
	int currentElementCount;	// 현재 원소의 개수
	DequeNode* pFrontNode;		// Front 노드의 포인터
	DequeNode* pRearNode;		// Rear 노드의 포인터
} LinkedDeque;
*/

LinkedDeque* createLinkedDeque()
{
	LinkedDeque* deque = malloc(sizeof(LinkedDeque));
	if (!deque)
	{
		printf("메모리 할당 실패\n");
		return (NULL);
	}
	deque->currentElementCount = 0;
	deque->pFrontNode = NULL;
	deque->pRearNode = NULL;
	return (deque);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	if (!pDeque)
		return (NULL);
	DequeNode* node = malloc(sizeof(DequeNode));
	if (!node)
	{
		printf("메모리 할당 실패\n");
		return (FALSE);
	}
	*node = element;
	node->pLLink = NULL;
	node->pRLink = pDeque->pFrontNode; // 덱이 비어있으면?
	if (pDeque->pFrontNode)
		pDeque->pFrontNode->pLLink = node;
	pDeque->pFrontNode = node;
	pDeque->currentElementCount++;
	return (TRUE);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	if (!pDeque)
		return (NULL);
	DequeNode* node = malloc(sizeof(DequeNode));
	if (!node)
	{
		printf("메모리 할당 실패\n");
		return (FALSE);
	}
	*node = element;
	node->pRLink = NULL;
	if (pDeque->pRearNode == NULL) // 덱이 비어있을 때
	{
		node->pLLink = NULL;
		pDeque->pFrontNode = node;
	}
	else
	{
		node->pLLink = pDeque->pRearNode;
		pDeque->pRearNode->pRLink = node;
	}
	pDeque->pRearNode = node;
	pDeque->currentElementCount++;
	return (TRUE);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	if (!pDeque)
		return (NULL);
	if (pDeque->currentElementCount == 0)
		return (NULL);
	DequeNode* node = pDeque->pFrontNode;
	node->pRLink = NULL;
	pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
	if (pDeque->currentElementCount == 1)
	{
		pDeque->pFrontNode = NULL;
		pDeque->pRearNode = NULL;
	}
	else
	{
		pDeque->pFrontNode->pLLink = NULL;
	}
	pDeque->currentElementCount--;
	return (node);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{

}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{

}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{

}

void deleteLinkedDeque(LinkedDeque* pDeque)
{

}

int isLinkedDequeFull(LinkedDeque* pDeque)
{

}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{

}

int main()
{

}
