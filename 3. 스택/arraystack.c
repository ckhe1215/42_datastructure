/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraystack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:05:45 by hkim              #+#    #+#             */
/*   Updated: 2021/11/28 16:07:06 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraystack.h"
#include <stdio.h>
#include <stdlib.h>

ArrayStack* createArrayStack(int maxElementCount)
{
	ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
	if (!stack)
	{
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	if (maxElementCount < 0)
	{
		printf("스택 크기는 0보다 커야함\n");
	}
	stack->maxElementCount = maxElementCount;
	stack->currentElementCount = 0;
	stack->pElement = (ArrayStackNode *)malloc(sizeof(ArrayStackNode) * maxElementCount);
	if (!stack->pElement)
	{
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	return (stack);
}

int pushAS(ArrayStack* pStack, ArrayStackNode element)
{
	if (!pStack)
		return (FALSE);
	if (pStack->currentElementCount < pStack->maxElementCount)
	{
		pStack->pElement[pStack->currentElementCount] = element;
		pStack->currentElementCount++;
	}
	else
	{
		fprintf(stderr, "Full stack\n");
		exit(1);
	}
	return (TRUE);
}

ArrayStackNode* popAS(ArrayStack* pStack)
{
	if (!pStack)
		return (FALSE);
	if (pStack->currentElementCount > 0)
	{
		ArrayStackNode *node = &(pStack->pElement[pStack->currentElementCount - 1]);
		pStack->currentElementCount--;
		return (node);
	}
	else
	{
		fprintf(stderr, "Empty stack\n");
		exit(1);
	}
	return (FALSE);
}

ArrayStackNode* peekAS(ArrayStack* pStack)
{
	if (!pStack)
		return (NULL);
	if (pStack->currentElementCount > 0)
	{
		ArrayStackNode *node = &(pStack->pElement[pStack->currentElementCount - 1]);
		return (node);
	}
	else
	{
		fprintf(stderr, "Empty stack\n");
		exit(1);
	}
	return (FALSE);
}

void deleteArrayStack(ArrayStack* pStack)
{
	if (!pStack)
		return ;
	free(pStack->pElement);
	pStack->pElement = NULL;
	free(pStack);
	pStack = NULL;
}

int isArrayStackFull(ArrayStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->currentElementCount == pStack->maxElementCount);
}

int isArrayStackEmpty(ArrayStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->currentElementCount == 0);
}

int main()
{
	ArrayStack *stack = createArrayStack(5);
	ArrayStackNode node;
	node.data = 'A';
	pushAS(stack, node);
	node.data = 'B';
	pushAS(stack, node);
	node.data = 'C';
	pushAS(stack, node);
	node.data = 'D';
	pushAS(stack, node);
	printf("%c\n", popAS(stack)->data);
	printf("%c\n", popAS(stack)->data);
	printf("%c\n", popAS(stack)->data);
	printf("%c\n", popAS(stack)->data);
	node.data = 'A';
	pushAS(stack, node);
	printf("%c\n", peekAS(stack)->data);
	printf("%c\n", peekAS(stack)->data);
}
