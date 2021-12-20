#include <stdlib.h>
#include <stdio.h>
#include "linkedgraph.h"
#include "arrayqueue.h"

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount)
{
	LinkedGraph *pGraph;

	pGraph = malloc(sizeof(LinkedGraph));
	if (!pGraph)
		return (NULL);
	pGraph->maxVertexCount = maxVertexCount;
	pGraph->currentVertexCount = 0;
	pGraph->currentEdgeCount = 0;
	pGraph->graphType = GRAPH_UNDIRECTED;
	pGraph->ppAdjEdge = malloc(sizeof(LinkedList) * maxVertexCount);
	if (!pGraph->ppAdjEdge)
		return (NULL);
	for (int i = 0; i < maxVertexCount; i++)
		pGraph->ppAdjEdge[i] = createLinkedList();
	pGraph->pVertex = malloc(sizeof(int) * maxVertexCount);
	if (!pGraph->pVertex)
		return (NULL);
	return (pGraph);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
	LinkedGraph *pGraph;

	pGraph = malloc(sizeof(LinkedGraph));
	if (!pGraph)
		return (NULL);
	pGraph->maxVertexCount = maxVertexCount;
	pGraph->currentVertexCount = 0;
	pGraph->currentEdgeCount = 0;
	pGraph->graphType = GRAPH_DIRECTED;
	pGraph->ppAdjEdge = malloc(sizeof(LinkedList) * maxVertexCount);
	if (!pGraph->ppAdjEdge)
		return (NULL);
	for (int i = 0; i < maxVertexCount; i++)
		pGraph->ppAdjEdge[i] = createLinkedList();
	pGraph->pVertex = malloc(sizeof(int) * maxVertexCount);
	if (!pGraph->pVertex)
		return (NULL);
	return (pGraph);
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{
	if (!pGraph)
		return ;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		free(pGraph->ppAdjEdge[i]);
	free(pGraph->ppAdjEdge);
	free(pGraph->pVertex);
	free(pGraph);
}

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->currentVertexCount == 0);
}

// 노드 추가
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	pGraph->pVertex[vertexID] = USED;
	pGraph->currentVertexCount++;
	return (TRUE);
}

// 간선 추가
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	ListNode element;

	if (!pGraph)
		return (FALSE);
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	element.data = toVertexID;
	element.weight = 1;
	element.pLink = NULL;
	addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, element);
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		element.data = fromVertexID;
		addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[toVertexID]->currentElementCount, element);
	}
	pGraph->currentEdgeCount++;
	return (TRUE);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	ListNode element;

	if (!pGraph)
		return (FALSE);
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	element.data = toVertexID;
	element.weight = weight;
	element.pLink = NULL;
	addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, element);
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		element.data = fromVertexID;
		addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[toVertexID]->currentElementCount, element);
	}
	pGraph->currentEdgeCount++;
	return (TRUE);
}

// 노드의 유효성 점검.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	if (vertexID >= pGraph->maxVertexCount)
		return (FALSE);
	return (pGraph->pVertex[vertexID] == USED);
}

// 노드 제거
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		removeEdgeLG(pGraph, vertexID, i);
	pGraph->pVertex[vertexID] = NOT_USED;
	pGraph->currentVertexCount--;
}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	int pos;
	if (!pGraph)
		return (FALSE);
	deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		deleteGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
	pGraph->currentEdgeCount--;
	return (TRUE);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
	int pos;

	if (!pList)
		return ;
	pos = findGraphNodePosition(pList, delVertexID);
	if (pos >= 0)
		removeLLElement(pList, pos);
}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
	int pos;
	ListNode* node;

	pos = 0;
	if (!pList)
		return (-1);
	node = pList->headerNode.pLink;
	while (node)
	{
		if (node->data == vertexID)
			return (pos);
		pos++;
		node = node->pLink;
	}
	return (-1);
}

// 간선 개수 반환
int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->currentEdgeCount);
}

// 노드 개수 반환
int getVertexCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->currentVertexCount);
}

// 최대 노드 개수 반환
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->maxVertexCount);
}

// 그래프 종류 반환.
int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->graphType);
}

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{
	if (!pGraph)
		return ;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		for (int j = 0; j < pGraph->ppAdjEdge[i]->currentElementCount; j++)
		{
			printf("%d - %d [%d]\n", i, getLLElement(pGraph->ppAdjEdge[i], j)->data, getLLElement(pGraph->ppAdjEdge[i], j)->weight);
		}
	}
}

void dfs(LinkedGraph* pGraph, int *visit, int n)
{
	if (visit[n] == FALSE)
	{
		visit[n] = TRUE;
		printf("%d ", n);
	}
	for (int i = 0; i < pGraph->ppAdjEdge[n]->currentElementCount; i++)
	{
		int next = getLLElement(pGraph->ppAdjEdge[n], i)->data;
		if (visit[next] == FALSE)
			dfs(pGraph, visit, next);
	}
}

void bfs(LinkedGraph* pGraph, int* visit, int n)
{
	ArrayQueue* pQueue;
	ArrayQueueNode node;

	pQueue = createArrayQueue(pGraph->maxVertexCount);
	node.data = n;
	enqueueAQ(pQueue, node);
	visit[n] = TRUE;
	while (!isArrayQueueEmpty(pQueue))
	{
		int tmp = dequeueAQ(pQueue)->data;
		printf("%d ", tmp);
		for (int i = 0; i < pGraph->ppAdjEdge[tmp]->currentElementCount; i++)
		{
			int next = getLLElement(pGraph->ppAdjEdge[tmp], i)->data;
			if (visit[next] == FALSE)
			{
				node.data = next;
				enqueueAQ(pQueue, node);
				visit[next] = TRUE;
			}
		}
	}
}

int main()
{
	LinkedGraph* pGraph;
	int visit[8] = {0};
	int visit2[8] = {0};

	pGraph = createLinkedGraph(8);
	addVertexLG(pGraph, 0);
	addVertexLG(pGraph, 1);
	addVertexLG(pGraph, 2);
	addVertexLG(pGraph, 3);
	addVertexLG(pGraph, 4);
	addVertexLG(pGraph, 5);
	addVertexLG(pGraph, 6);
	addVertexLG(pGraph, 7);
	addEdgeLG(pGraph, 0, 1);
	addEdgeLG(pGraph, 0, 2);
	addEdgeLG(pGraph, 1, 3);
	addEdgeLG(pGraph, 1, 4);
	addEdgeLG(pGraph, 2, 5);
	addEdgeLG(pGraph, 2, 6);
	addEdgeLG(pGraph, 4, 5);
	addEdgeLG(pGraph, 3, 7);
	// removeEdgeLG(pGraph, 0, 1);
	// removeEdgeLG(pGraph, 0, 2);
	// removeEdgeLG(pGraph, 1, 3);
	// removeEdgeLG(pGraph, 1, 4);
	// removeEdgeLG(pGraph, 2, 5);
	// removeEdgeLG(pGraph, 2, 6);
	// removeEdgeLG(pGraph, 4, 5);
	// removeEdgeLG(pGraph, 3, 7);
	// displayLinkedGraph(pGraph);
	dfs(pGraph, visit, 0);
	printf("\n");
	bfs(pGraph, visit2, 0);
	printf("\n");
}
