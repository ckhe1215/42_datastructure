/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:00:34 by bokim             #+#    #+#             */
/*   Updated: 2021/11/23 16:11:59 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- 배열
메모리 상에 순차적으로 값이 저장되는 자료구조
논리적 저장 순서와 물리적 저장 순서가 일치
생성 시에 지정한 크기로 고정됨

인덱스를 활용해 원하는 위치의 데이터를 빠르게 검색할 수 있음
-> 검색시 시간복잡도 O(1)
대신 특정 위치에 값을 삽입하거나 삭제할 때는 다른 요소들을 shift 해주어야해서 비효율적
-> 삽입, 삭제 시간복잡도 O(n)
*/

#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

ArrayList*	createArrayList(int maxElementCount){
	ArrayList *arrayList = (ArrayList*)malloc(sizeof(ArrayList));

	arrayList->maxElementCount = maxElementCount;
	arrayList->currentElementCount = 0;
	arrayList->pElement = (ArrayListNode *)malloc(maxElementCount * sizeof(ArrayListNode));
	return (arrayList);
}

void	deleteArrayList(ArrayList *pList){
	free(pList->pElement);
	pList->pElement = NULL;
	free(pList);
	pList = NULL;
}

int isArrayListFull(ArrayList* pList){
	return (pList->maxElementCount == pList->currentElementCount);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element){
	if (position < 0 || position > pList->currentElementCount){
		fprintf(stderr, "Wrong position\n");
		exit(1);
	}
	else if (!isArrayListFull(pList)){
		for (int i = pList->currentElementCount; i > position; i--){
			pList->pElement[i] = pList->pElement[i - 1];
		}
		pList->pElement[position] = element;
		pList->currentElementCount++;
		return (TRUE);
	}
	else {
		fprintf(stderr, "List is full!\n");
		exit(1);
	}
}

int removeALElement(ArrayList* pList, int position){
	for (int i = position; i < pList->currentElementCount; i++) {
		if (i < pList->maxElementCount)
			pList->pElement[i] = pList->pElement[i + 1];
	}
	pList->currentElementCount--;
	return (TRUE);
}

ArrayListNode* getALElement(ArrayList* pList, int position){
	if (position < 0 || position >= pList->currentElementCount){
		fprintf(stderr, "Invalid access\n");
		exit(1);
	}
	return (&(pList->pElement[position]));
}

void displayArrayList(ArrayList* pList){
	for (int i = 0; i < pList->currentElementCount; i++){
		printf("%d\n", pList->pElement[i].data);
	}
}

void clearArrayList(ArrayList* pList){
	for (int i = 0; i < pList->maxElementCount; i++){
		pList->pElement[i].data = 0;
	}
	pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList){
	return (pList->currentElementCount);
}

int	main(void){
	ArrayList* arrayList = createArrayList(7);
	ArrayListNode node1, node2, node3;
	node1.data = 1;
	node2.data = 2;
	node3.data = 3;

	addALElement(arrayList, 0, node1);
	addALElement(arrayList, 1, node2);
	addALElement(arrayList, 2, node3);
	printf("getArrayListLength= %d\n", getArrayListLength(arrayList));
	clearArrayList(arrayList);
	displayArrayList(arrayList);
}
