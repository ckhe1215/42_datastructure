#ifndef _MAX_HEAP_
#define _MAX_HEAP_

typedef struct MaxHeapNodeType
{
	int data;
} MaxHeapNode;

typedef struct MaxHeapType
{
	int maxElementCount;
	int currentElementCount;
	MaxHeapNode *pElement;
} MaxHeap;

MaxHeap* createMaxHeap(int maxElementCount);
int insertMaxHeap(MaxHeap* pHeap, MaxHeapNode element);
MaxHeapNode removeMaxHeap(MaxHeap* pHeap);
void deleteMaxHeap(MaxHeap* pHeap);
int isMaxHeapFull(MaxHeap* pHeap);
int isMaxHeapEmpty(MaxHeap* pHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif
