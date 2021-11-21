#include "arraylist.h"
#include <stdlib.h>

ArrayList* createArrayList(int maxElementCount)
{
	ArrayList *arrayList;

	arrayList->maxElementCount = maxElementCount;
	arrayList->currentElementCount = 0;
	arrayList->pElement = malloc(sizeof(ArrayListNode) * maxElementCount);
}

void deleteArrayList(ArrayList* pList)
{

}

int isArrayListFull(ArrayList* pList)
{

}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
	if (position >= pList->maxElementCount)
	{
		ArrayListNode *tempArr;
		tempArr = malloc(sizeof(ArrayListNode) * (pList->maxElementCount * 2));
		for (int i = 0; i < pList->currentElementCount; i++) {
			tempArr[i] = pList->pElement[i];
		}
		free(pList->pElement);
		pList->pElement = tempArr;
		pList->maxElementCount *= 2;
		addALElement(pList, position, element);
		// 혹은 resize 함수 만들고 while 문에서 계속 호출
	}
	else if (position < pList->currentElementCount)
	{
		if (pList->currentElementCount == pList->maxElementCount)
		{
			// resize
		}
		// 한 칸 씩 뒤로 미룬다
	}
	else
	{
		pList->pElement[position] = element;
		pList->currentElementCount++;
	}
}

int removeALElement(ArrayList* pList, int position)
{

}

ArrayListNode* getALElement(ArrayList* pList, int position)
{

}

void displayArrayList(ArrayList* pList)
{

}

void clearArrayList(ArrayList* pList)
{

}

int getArrayListLength(ArrayList* pList)
{

}

int main()
{

}
