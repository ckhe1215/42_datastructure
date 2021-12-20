#include "arraygraph.h"
#include "arrayqueue.h"
#include <stdlib.h>
#include <stdio.h>

// 그래프 생성
ArrayGraph* createArrayGraph(int maxVertexCount)
{
	ArrayGraph* pGraph;

	pGraph = malloc(sizeof(ArrayGraph));
	if (!pGraph)
		return (NULL);
	pGraph->maxVertexCount = maxVertexCount;
	pGraph->currentVertexCount = 0;
	pGraph->graphType = GRAPH_UNDIRECTED;
	pGraph->ppAdjEdge = malloc(sizeof(int *) * maxVertexCount);
	if (!pGraph->ppAdjEdge)
		return (NULL);
	for (int i = 0; i < maxVertexCount; i++)
	{
		pGraph->ppAdjEdge[i] = malloc(sizeof(int) * maxVertexCount);
		if (!pGraph->ppAdjEdge[i])
			return (NULL);
	}
	pGraph->pVertex = malloc(sizeof(int) * maxVertexCount);
	if (!pGraph->pVertex)
		return (NULL);
	return (pGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph* pGraph;

	pGraph = malloc(sizeof(ArrayGraph));
	if (!pGraph)
		return (NULL);
	pGraph->maxVertexCount = maxVertexCount;
	pGraph->currentVertexCount = 0;
	pGraph->graphType = GRAPH_DIRECTED;
	pGraph->ppAdjEdge = malloc(sizeof(int *) * maxVertexCount);
	if (!pGraph->ppAdjEdge)
		return (NULL);
	for (int i = 0; i < maxVertexCount; i++)
	{
		pGraph->ppAdjEdge[i] = malloc(sizeof(int) * maxVertexCount);
		if (!pGraph->ppAdjEdge[i])
			return (NULL);
	}
	pGraph->pVertex = malloc(sizeof(int) * maxVertexCount);
	if (!pGraph->pVertex)
		return (NULL);
	return (pGraph);
}

// 그래프 삭제
void deleteArrayGraph(ArrayGraph* pGraph)
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
int isEmptyAG(ArrayGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	return (pGraph->currentVertexCount == 0);
}

// 노드 추가
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	pGraph->pVertex[vertexID] = USED;
	pGraph->currentVertexCount++;
	return (TRUE);
}

// 간선 추가
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!pGraph)
		return (FALSE);
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
	if (pGraph->graphType = GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = 1;
	return (TRUE);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (!pGraph)
		return (FALSE);
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
	if (pGraph->graphType = GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
	return (TRUE);
}

// 노드의 유효성 점검.
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	if (vertexID >= pGraph->maxVertexCount)
		return (FALSE);
	return (pGraph->pVertex[vertexID] == USED);
}

// 노드 제거
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		removeEdgeAG(pGraph, vertexID, i);
	pGraph->pVertex[vertexID] = NOT_USED;
	pGraph->currentVertexCount--;
}

// 간선 제거
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!pGraph)
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
	return (TRUE);
}

// 그래프 정보 출력
void displayArrayGraph(ArrayGraph* pGraph)
{
	if (!pGraph)
		return ;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		for (int j = 0; j < pGraph->maxVertexCount; j++)
		{
			if (pGraph->ppAdjEdge[i][j] != 0)
				printf("%d - %d [%d]\n", i, j, pGraph->ppAdjEdge[i][j]);
		}
	}
}

void dfs(ArrayGraph* pGraph, int* visit, int n)
{
	if (visit[n] == FALSE)
	{
		visit[n] = TRUE;
		printf("%d ", n);
	}
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (pGraph->ppAdjEdge[n][i] != 0 && visit[i] == FALSE)
			dfs(pGraph, visit, i);
	}
}

void bfs(ArrayGraph* pGraph, int* visit, int n)
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
		for (int i = 0; i < pGraph->maxVertexCount; i++)
		{
			if (pGraph->ppAdjEdge[tmp][i] != 0 && visit[i] == FALSE)
			{
				node.data = i;
				enqueueAQ(pQueue, node);
				visit[i] = TRUE;
			}
		}
	}
}

int main()
{
	ArrayGraph* pGraph;
	int visit[8] = {0};
	int visit2[8] = {0};

	pGraph = createArrayGraph(8);
	addVertexAG(pGraph, 0);
	addVertexAG(pGraph, 1);
	addVertexAG(pGraph, 2);
	addVertexAG(pGraph, 3);
	addVertexAG(pGraph, 4);
	addVertexAG(pGraph, 5);
	addVertexAG(pGraph, 6);
	addVertexAG(pGraph, 7);
	addEdgeAG(pGraph, 0, 1);
	addEdgeAG(pGraph, 0, 2);
	addEdgeAG(pGraph, 1, 3);
	addEdgeAG(pGraph, 1, 4);
	addEdgeAG(pGraph, 2, 5);
	addEdgeAG(pGraph, 2, 6);
	addEdgeAG(pGraph, 4, 5);
	addEdgeAG(pGraph, 3, 7);
	// for (int i = 0; i < 8; i++)
	// 	removeVertexAG(pGraph, i);
	displayArrayGraph(pGraph);
	dfs(pGraph, visit, 0);
	printf("\n");
	bfs(pGraph, visit2, 0);
	printf("\n");
}
