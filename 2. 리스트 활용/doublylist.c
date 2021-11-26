/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:10 by bokim             #+#    #+#             */
/*   Updated: 2021/11/25 16:52:37 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 이중 연결리스트
장점
- 접근 편의성
단점
- 추가적 메모리 공간 사용
- 구현이 복잡함
*/

#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>

DoublyList* createDoublyList(){
	DoublyList *doublyList = (DoublyList *)malloc(sizeof(DoublyList));
	doublyList->currentElementCount = 0;
	doublyList->headerNode.pLLink =	&(doublyList->headerNode);
	doublyList->headerNode.pRLink = &(doublyList->headerNode);
	return (doublyList);
}

DoublyListNode* getDLElement(DoublyList* pList, int position){
	DoublyListNode *node = &(pList->headerNode);
	if (position <= pList->currentElementCount / 2) {
		for (int i = 0; i < position + 1; i++) {
			node = node->pRLink;
		}
	}
	else {
		for (int i = 0; i < pList->currentElementCount - position; i++) {
			node = node->pLLink;
		}
	}
	return (node);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element){
	if (position >= 0 && position <= pList->currentElementCount) {
		DoublyListNode *newNode = (DoublyListNode *)malloc(sizeof(DoublyListNode));
		*newNode = element;
		newNode->pRLink = NULL;
		newNode->pLLink = NULL;
		DoublyListNode *preNode = 0;
		if (position == 0)
			preNode = &(pList->headerNode);
		else
			preNode = getDLElement(pList, position - 1);
		newNode->pRLink = preNode->pRLink;
		preNode->pRLink->pLLink = newNode;
		preNode->pRLink = newNode;
		newNode->pLLink = preNode;
		pList->currentElementCount++;
	}
	else {
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

int removeDLElement(DoublyList* pList, int position){
	if (position >= 0 && position <= pList->currentElementCount){
		DoublyListNode *preNode = 0;
		if (position == 0)
			preNode = &(pList->headerNode);
		else
			preNode = getDLElement(pList, position - 1);
		DoublyListNode *node = getDLElement(pList, position);
		preNode->pRLink = node->pRLink;
		node->pRLink->pLLink = preNode;
		free(node);
		pList->currentElementCount--;
	}
	else {
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

void clearDoublyList(DoublyList* pList){
	DoublyListNode *preNode = &(pList->headerNode);
	while (pList->currentElementCount > 0){
		removeDLElement(pList, pList->currentElementCount - 1);
	}
	pList->headerNode.pLLink = preNode;
	pList->headerNode.pRLink = preNode;
}

void deleteDoublyList(DoublyList* pList){
	clearDoublyList(pList);
	free(pList);
	pList = NULL;
}

int getDoublyListLength(DoublyList* pList){
	return (pList->currentElementCount);
}

void displayDoublyList(DoublyList* pList){
	int i = 0;

	if (pList->currentElementCount > 0)
	{
		for (i = 0; i < pList->currentElementCount; i++)
		{
			printf("[%d] : %d\n", i, getDLElement(pList, i)->data);
		}
		printf("--------\n");
	}
	else
	{
		printf("No elements\n");
	}
}

int main(){
	DoublyList *pList = NULL;
	DoublyListNode node;
	pList = createDoublyList();

	if (pList != NULL){
		node.data = 1;
		addDLElement(pList, 0, node);
		node.data = 3;
		addDLElement(pList, 1, node);
		node.data = 5;
		addDLElement(pList, 2, node);
		node.data = 7;
		addDLElement(pList, 3, node);
		node.data = 6;
		addDLElement(pList, 3, node);
		node.data = 4;
		addDLElement(pList, 0, node);
		removeDLElement(pList, 5);
		removeDLElement(pList, 4);
		removeDLElement(pList, 0);
		displayDoublyList(pList);
		removeDLElement(pList, 1);
		displayDoublyList(pList);
	}
}