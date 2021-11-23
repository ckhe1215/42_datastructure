/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:04:16 by bokim             #+#    #+#             */
/*   Updated: 2021/11/23 15:28:52 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- 단순 연결 리스트
인덱스가 없고, 본래 정해져있는 크기가 없다.
배열과 달리 자료의 크기에 유동성이 있고, 인덱스를 통해 관리되지 않으며
이전의 자료에 의해서 다음 자료가 유지되는 형태로 자료가 저장 및 관리된다.

장점 -
자료의 삽입과 삭제가 용이하다.
리스트 내에서 자료의 이동이 필요하지 않다.

단점 -
포인터의 사용으로 인해 저장 공간의 낭비가 있다.
알고리즘이 복잡하다.
특정 자료의 탐색 시간이 많이 소요된다.
*/

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *createLinkedList()
{
	LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
	linkedList->currentElementCount = 0;
	linkedList->headerNode.pLink = NULL;
	return (linkedList);
}

/*
삽입 함수
시간 복잡도 : O(n)
but, 추가하려는 위치의 이전 노드를 안다면 O(1)로 구현 가능
이 함수는 이전 노드를 모르기 때문에 탐색까지 필요로 하므로 O(n)
*/
int addLLElement(LinkedList *pList, int position, ListNode element)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
		*newNode = element;
		newNode->pLink = NULL;
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++)
		{
			preNode = preNode->pLink;
		}
		newNode->pLink = preNode->pLink;
		preNode->pLink = newNode;
		pList->currentElementCount++;
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

/*
제거 함수
시간 복잡도 : O(n)
삽입 함수와 같음
*/
int removeLLElement(LinkedList *pList, int position)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++)
		{
			preNode = preNode->pLink;
		}
		free(preNode->pLink);
		preNode->pLink = preNode->pLink->pLink;
		pList->currentElementCount--;
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

/*
탐색 함수
시간 복잡도 : O(n)
배열에서는 인덱스로 자료를 관리했기 때문에 O(1)이지만,
연결 리스트에는 지정된 인덱스가 없기 때문에 헤더노드부터 찾아가야 한다.
*/
ListNode *getLLElement(LinkedList *pList, int position)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++)
		{
			preNode = preNode->pLink;
		}
		return (preNode->pLink);
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
}

void clearLinkedList(LinkedList *pList)
{
	ListNode *preNode = &(pList->headerNode);
	while (pList->currentElementCount > 0)
	{
		removeLLElement(pList, pList->currentElementCount - 1);
	}
	pList->headerNode.pLink = 0;
}

int getLinkedListLength(LinkedList *pList)
{
	return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList *pList)
{
	clearLinkedList(pList);
	free(pList);
	pList = NULL;
}

void displayLinkedList(LinkedList *pList)
{
	int i = 0;

	if (pList->currentElementCount > 0)
	{
		for (i = 0; i < pList->currentElementCount; i++)
		{
			printf("[%d] : %d\n", i, getLLElement(pList, i)->data);
		}
		printf("--------\n");
	}
	else
	{
		printf("No elements\n");
	}
}

int main()
{
	int i = 0;
	int arrayCount = 0;

	LinkedList *pList = NULL;
	ListNode *pNode = NULL;
	ListNode node;
	pList = createLinkedList();

	if (pList != NULL)
	{
		node.data = 1;
		addLLElement(pList, 0, node);
		node.data = 3;
		addLLElement(pList, 1, node);
		node.data = 5;
		addLLElement(pList, 2, node);
		displayLinkedList(pList);
		removeLLElement(pList, 0);
		displayLinkedList(pList);
		removeLLElement(pList, 0);
		displayLinkedList(pList);
	}

	return 0;
}