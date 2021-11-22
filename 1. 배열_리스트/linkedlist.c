/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:04:16 by bokim             #+#    #+#             */
/*   Updated: 2021/11/23 00:38:41 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* createLinkedList(){
	LinkedList *linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->currentElementCount = 0;
	linkedList->headerNode.pLink = NULL;
	return (linkedList);
}

int addLLElement(LinkedList* pList, int position, ListNode element){
	if (position >= 0 && position <= pList->currentElementCount){
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
	else {
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

int removeLLElement(LinkedList* pList, int position){
	if (position >= 0 && position <= pList->currentElementCount){
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++){
			preNode = preNode->pLink;
		}
		preNode->pLink = preNode->pLink->pLink;
		pList->currentElementCount--;
	}
	else {
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (TRUE);
}

ListNode* getLLElement(LinkedList* pList, int position){
	if (position >= 0 && position <= pList->currentElementCount){
		ListNode *preNode = &(pList->headerNode);
		for (int i = 0; i < position; i++){
			preNode = preNode->pLink;
		}
		return (preNode->pLink);
	}
	else {
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
}

void clearLinkedList(LinkedList* pList){
	pList->headerNode.pLink = 0;
	pList->currentElementCount = 0;
}

int getLinkedListLength(LinkedList* pList){
	return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList){
	free(pList);
	pList = NULL;
}

void displayLinkedList(LinkedList* pList){
	int i = 0;

	if (pList != NULL) {
		printf("현재 원소 개수 : %d\n", pList->currentElementCount);
		for (i = 0; i < pList->currentElementCount; i++) {
			printf("[%d], %d\n", i, getLLElement(pList, i)->data);
		}
	}
	else {
		printf("원소가 없습니다.\n");
	}
}

int	main(){
	int i = 0;
	int arrayCount = 0;

	LinkedList* pList = NULL;
	ListNode* pNode = NULL;
	ListNode node;
	pList = createLinkedList();

	if (pList != NULL) {
		node.data = 1;
		addLLElement(pList, 0, node);
		node.data = 3;
		addLLElement(pList, 1, node);
		node.data = 5;
		addLLElement(pList, 2, node);
		displayLinkedList(pList);
		removeLLElement(pList, 0);
		displayLinkedList(pList);
		deleteLinkedList(pList);
	}

	return 0;
}
