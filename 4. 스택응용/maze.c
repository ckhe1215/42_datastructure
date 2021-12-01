#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

LinkedStack* createLinkedStack()
{
	LinkedStack *stack = (LinkedStack *)malloc(sizeof(LinkedStack));
	if (!stack)
	{
		fprintf(stderr, "메모리 할당 실패");
		exit(1);
	}
	stack->currentElementCount = 0;
	stack->pTopElement = NULL;
	return (stack);
}

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos,
				MapPosition endPos, LinkedStack *pStack)
{
	LinkedStack *path = createLinkedStack();
	int dx[4] = {-1, 0, 0, 1};
	int dy[4] = {0, -1, 1, 0};
	pushLSMapPosition(pStack, startPos);
	mazeArray[startPos.col][startPos.row] = 2;
	while (!isLinkedStackEmpty(pStack))
	{
		MapPosition temp = popLSMapPosition(pStack);
		int x = temp.col;
		int y = temp.row;
		pushLSMapPosition(path, temp);
		for (int i = 0; i < 4; i++) {
			int new_x = dx[i] + x;
			int new_y = dy[i] + y;
			if (new_x >= 0 && new_x < HEIGHT && new_y >= 0 && new_y <= WIDTH && mazeArray[new_x][new_y] == 0)
			{
				MapPosition pos;
				pos.col = new_x;
				pos.row = new_y;
				mazeArray[new_x][new_y] = 2;
				pushLSMapPosition(pStack, pos);
				if (new_x == endPos.col && new_y == endPos.row)
				{
					pushLSMapPosition(path, endPos);
					showPath(path, mazeArray);
					return ;
				}
			}
		}
	}
	printf("Invalid map\n");
}

int pushLSMapPosition(LinkedStack* pStack, MapPosition data)
{
	if (!pStack)
		return (FALSE);
	StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
	if (!newNode)
		return (FALSE);
	newNode->pos = data;
	newNode->pLink = pStack->pTopElement;
	pStack->pTopElement = newNode;
	pStack->currentElementCount++;
	return (TRUE);
}

MapPosition popLSMapPosition(LinkedStack* pStack)
{
	if (!pStack)
		exit(1);
	if (pStack->currentElementCount > 0)
	{
		StackNode *node = pStack->pTopElement;
		MapPosition pos = node->pos;
		pStack->pTopElement = pStack->pTopElement->pLink;
		pStack->currentElementCount--;
		free(node);
		node = NULL;
		return (pos);
	}
	else
	{
		printf("Empty stack\n");
	}
}

StackNode* peekLSMapPosition(LinkedStack* pStack)
{
	if (!pStack)
		return (NULL);
	if (pStack->currentElementCount > 0)
	{
		StackNode *node = pStack->pTopElement;
		return (node);
	}
	else
	{
		printf("Empty stack\n");
	}
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->currentElementCount == 0);
}

void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (mazeArray[i][j] == 2)
				mazeArray[i][j] = 0;
		}
	}
	while (!isLinkedStackEmpty(pStack))
	{
		MapPosition pos = popLSMapPosition(pStack);
		mazeArray[pos.col][pos.row] = 2;
	}
	printMaze(mazeArray);
}

void printMaze(int mazeArray[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%d ", mazeArray[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	LinkedStack *stack = createLinkedStack();
	int mazeArray[HEIGHT][WIDTH] = {
		0, 0, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0
	};
	MapPosition start;
	MapPosition end;
	start.col = 0;
	start.row = 0;
	end.col = 7;
	end.row = 7;
	findPath(mazeArray, start, end, stack);
}
