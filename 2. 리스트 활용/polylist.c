/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polylist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:55:53 by bokim             #+#    #+#             */
/*   Updated: 2021/11/25 18:24:15 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polylist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *createLinkedList()
{
	LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
	linkedList->currentElementCount = 0;
	linkedList->headerNode.pLink = NULL;
	return (linkedList);
}

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

int removeLLElement(LinkedList *pList, int position)
{
	if (position >= 0 && position <= pList->currentElementCount)
	{
		ListNode *preNode = 0;
		if (position == 0)
			preNode = &(pList->headerNode);
		else
			preNode = getLLElement(pList, position - 1);
		ListNode *node = getLLElement(pList, position);
		preNode->pLink = node->pLink;
		free(node);
		pList->currentElementCount--;
	}
	else
	{
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

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
	if (pList->currentElementCount > 0)
	{
		for (int i = 0; i < pList->currentElementCount; i++)
		{
			printf("[%d] : %d %d\n", i, getLLElement(pList, i)->coef, getLLElement(pList, i)->deg);
		}
		printf("--------\n");
	}
	else
	{
		printf("No elements\n");
	}
}

void polySum(LinkedList *list1, LinkedList *list2){
	// 두 리스트를 다 돌면서 최대 차수 찾기
	int maxDeg = 0;
	for (int i = 0; i < list1->currentElementCount; i++){
		if (getLLElement(list1, i)->deg > maxDeg)
			maxDeg = getLLElement(list1, i)->deg;
	}
	for (int i = 0; i < list2->currentElementCount; i++){
		if (getLLElement(list2, i)->deg > maxDeg)
			maxDeg = getLLElement(list2, i)->deg;
	}
	LinkedList *answer = createLinkedList();
	ListNode node;
	for (int i = maxDeg; i >= 0; i--){
		int coef = 0;
		for (int j = 0; j < list1->currentElementCount; j++){
			if (getLLElement(list1, j)->deg == i){
				coef += getLLElement(list1, j)->coef;
			}
		}
		for (int j = 0; j < list2->currentElementCount; j++){
			if (getLLElement(list2, j)->deg == i){
				coef += getLLElement(list2, j)->coef;
			}
		}
		if (coef != 0)
		{
			node.deg = i;
			node.coef = coef;
			addLLElement(answer, answer->currentElementCount, node);
		}
	}
	displayLinkedList(answer);
}

int main()
{
/*
6x^6 + 4x^5 	   + 2x^2
	   1x^5 + 2x^4 + 3x^2 + 4
*/
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	ListNode node;

	if (list1 != NULL || list2 != NULL)
	{
		node.coef = 6;
		node.deg = 6;
		addLLElement(list1, 0, node);
		node.coef = 4;
		node.deg = 5;
		addLLElement(list1, 1, node);
		node.coef = 2;
		node.deg = 2;
		addLLElement(list1, 2, node);

		node.coef = 1;
		node.deg = 5;
		addLLElement(list2, 0, node);
		node.coef = 2;
		node.deg = 4;
		addLLElement(list2, 1, node);
		node.coef = 3;
		node.deg = 2;
		addLLElement(list2, 2, node);
		node.coef = 4;
		node.deg = 0;
		addLLElement(list2, 3, node);

		polySum(list1, list2);
	}

	return 0;
}
