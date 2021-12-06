/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkeddeque.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 04:28:44 by hkim              #+#    #+#             */
/*   Updated: 2021/12/06 18:29:52 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkeddeque.h"
#include <stdio.h>
#include <stdlib.h>

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
		return (FALSE);
	DequeNode* node = malloc(sizeof(DequeNode));
	if (!node)
	{
		printf("메모리 할당 실패\n");
		return (FALSE);
	}
	*node = element;
	node->pLLink = NULL;
	node->pRLink = pDeque->pFrontNode;
	if (pDeque->pFrontNode)
		pDeque->pFrontNode->pLLink = node;
	else
		pDeque->pRearNode = node;
	pDeque->pFrontNode = node;
	pDeque->currentElementCount++;
	return (TRUE);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	if (!pDeque)
		return (FALSE);
	DequeNode* node = malloc(sizeof(DequeNode));
	if (!node)
	{
		printf("메모리 할당 실패\n");
		return (FALSE);
	}
	*node = element;
	node->pRLink = NULL;
	if (pDeque->currentElementCount == 0) // 덱이 비어있을 때
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
	pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
	node->pLLink = NULL;
	if (pDeque->currentElementCount == 1)
	{
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
	if (!pDeque)
		return (NULL);
	if (pDeque->currentElementCount == 0)
		return (NULL);
	DequeNode* node = pDeque->pRearNode;
	pDeque->pRearNode = pDeque->pRearNode->pLLink;
	node->pLLink = NULL;
	if (pDeque->currentElementCount == 1)
		pDeque->pFrontNode = NULL;
	else
		pDeque->pRearNode->pRLink = NULL;
	pDeque->currentElementCount--;
	return (node);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	if (!pDeque)
		return (NULL);
	if (pDeque->currentElementCount == 0)
		return (NULL);
	DequeNode* node = pDeque->pFrontNode;
	return (node);
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
	if (!pDeque)
		return (NULL);
	if (pDeque->currentElementCount == 0)
		return (NULL);
	DequeNode* node = pDeque->pRearNode;
	return (node);
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
	if (!pDeque)
		return ;
	while (pDeque->pRearNode)
	{
		DequeNode *node = pDeque->pRearNode->pLLink;
		free(pDeque->pRearNode);
		pDeque->pRearNode = node;
	}
	free(pDeque);
	pDeque = NULL;
}

int isLinkedDequeFull(LinkedDeque* pDeque)
{
	// ..?
}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	if (!pDeque)
		return (FALSE);
	return (pDeque->pFrontNode == NULL);
}

int main()
{
	LinkedDeque *deque = createLinkedDeque();
	DequeNode node;
	node.data = 'a';
	insertFrontLD(deque, node);
	node.data = 'b';
	insertRearLD(deque, node);
	node.data = 'a';
	insertFrontLD(deque, node);
	node.data = 'b';
	insertRearLD(deque, node);
	printf("%c\n", peekFrontLD(deque)->data);
	printf("%c\n", peekRearLD(deque)->data);
	printf("%d\n", isLinkedDequeEmpty(deque));
	printf("%c\n", deleteRearLD(deque)->data);
	printf("%c\n", deleteRearLD(deque)->data);
	printf("%c\n", deleteFrontLD(deque)->data);
	printf("%c\n", deleteFrontLD(deque)->data);
	printf("%d\n", isLinkedDequeEmpty(deque));
	deleteLinkedDeque(deque);
}
