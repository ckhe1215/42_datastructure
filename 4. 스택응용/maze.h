#ifndef _MAZE_
#define _MAZE_

#define HEIGHT 8
#define WIDTH 8

typedef struct MapPosition {
	int col;
	int row;
} MapPosition;

typedef struct StackNodeType
{
	struct MapPosition pos;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	// 현재 원소의 개수
	StackNode* pTopElement;		// Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos,
				MapPosition endPos, LinkedStack *pStack);
int pushLSMapPosition(LinkedStack* pStack, MapPosition data);
MapPosition popLSMapPosition(LinkedStack* pStack);
StackNode* peekLSMapPosition(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH]);
void printMaze(int mazeArray[HEIGHT][WIDTH]);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif


