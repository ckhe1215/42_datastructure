/*
신장트리 : 그래프 내에 있는 모든 정점을 연결하고 사이클이 없는 그래프
-> n개의 정점이 있다면 신장 트리의 간선 수는 n - 1개
최소 비용 신장 트리 : 각 간선이 가지고 있는 가중치의 합이 최소가 되는 신장트리
== 가중치 무방향 그래프에서 모든 정점을 연결할 때 최소 비용으로 연결할 수 있는 방법을 찾는 알고리즘
최소비용 신장트리는 여러개 존재할 수 있다

크루스칼 알고리즘
: 간선을 중심으로 트리를 구성
: 가중치가 작은 간선부터 연결
: 만약 n번째로 가중치가 작은 간선을 연결했을때 사이클이 생기면 연결하지 않음

프림 알고리즘
: 정점을 중심으로 트리를 구성
: 시작 정점에서 연결된 간선 중 가장 가중치가 작은 간선을 트리에 포함시킴
: 만들어진 트리에서 가중치가 작은 간선을 계속 포함시킴
*/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

void bubbleSort(LinkedList* pList)
{
	if (!pList)
		return ;
	for (int i = 0; i < pList->currentElementCount; i++)
	{
		for (int j = i; j < pList->currentElementCount; j++)
		{
			if (getLLElement(pList, i)->weight > getLLElement(pList, j)->weight)
			{
				int temp_from, temp_to, temp_weight;
				temp_from = getLLElement(pList, i)->from;
				temp_to = getLLElement(pList, i)->to;
				temp_weight = getLLElement(pList, i)->weight;
				getLLElement(pList, i)->from = getLLElement(pList, j)->from;
				getLLElement(pList, i)->to = getLLElement(pList, j)->to;
				getLLElement(pList, i)->weight = getLLElement(pList, j)->weight;
				getLLElement(pList, j)->from = temp_from;
				getLLElement(pList, j)->to = temp_to;
				getLLElement(pList, j)->weight = temp_weight;
			}
		}
	}
}

int getParent(int *kruskal, int n)
{
	if (!kruskal)
		return (-1);
	if (kruskal[n] == n)
		return (n);
	return (getParent(kruskal, kruskal[n]));
}

void unionParent(int *kruskal, int a, int b)
{
	if (!kruskal)
		return ;
	int parentA = getParent(kruskal, a);
	int parentB = getParent(kruskal, b);
	if (parentA < parentB)
		kruskal[parentB] = parentA;
	else
		kruskal[parentA] = parentB;

}

int findParent(int* kruskal, int from, int to)
{
	if (!kruskal)
		return (FALSE);
	return (getParent(kruskal, from) == getParent(kruskal, to));
}

int main()
{
	LinkedList* edgeList;
	ListNode node;
	int* kruskal;

	edgeList = createLinkedList();
	node.from = 0;
	node.to = 1;
	node.weight = 4;
	addLLElement(edgeList, 0, node);
	node.from = 1;
	node.to = 2;
	node.weight = 2;
	addLLElement(edgeList, 1, node);
	node.from = 0;
	node.to = 2;
	node.weight = 3;
	addLLElement(edgeList, 2, node);
	node.from = 2;
	node.to = 3;
	node.weight = 1;
	addLLElement(edgeList, 3, node);
	node.from = 3;
	node.to = 4;
	node.weight = 1;
	addLLElement(edgeList, 4, node);
	node.from = 3;
	node.to = 5;
	node.weight = 5;
	addLLElement(edgeList, 5, node);
	node.from = 4;
	node.to = 5;
	node.weight = 6;
	addLLElement(edgeList, 6, node);
	displayLinkedList(edgeList);

	bubbleSort(edgeList);
	displayLinkedList(edgeList);

	kruskal = malloc(sizeof(int) * edgeList->currentElementCount);
	if (!kruskal)
		return (0);
	for (int i = 0; i < edgeList->currentElementCount; i++)
		kruskal[i] = i;
	for (int i = 0; i < edgeList->currentElementCount; i++)
	{
		if (!findParent(kruskal, getLLElement(edgeList, i)->from, getLLElement(edgeList, i)->to))
		{
			printf("%d - %d\n", getLLElement(edgeList, i)->from, getLLElement(edgeList, i)->to);
			unionParent(kruskal, getLLElement(edgeList, i)->from, getLLElement(edgeList, i)->to);
		}
	}
}
