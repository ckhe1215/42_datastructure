/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedstack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:50:42 by hkim              #+#    #+#             */
/*   Updated: 2021/11/28 16:17:51 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>

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

int pushLS(LinkedStack* pStack, StackNode element)
{
	if (!pStack)
		return (FALSE);
	StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
	*newNode = element;
	newNode->pLink = pStack->pTopElement;
	pStack->pTopElement = newNode;
	pStack->currentElementCount++;
	return (TRUE);
}

StackNode* popLS(LinkedStack* pStack)
{
	if (!pStack)
		return (NULL);
	if (pStack->currentElementCount > 0)
	{
		StackNode *node = pStack->pTopElement;
		pStack->pTopElement = pStack->pTopElement->pLink;
		pStack->currentElementCount--;
		return (node);
	}
	else
	{
		printf("Empty stack\n");
	}
}

StackNode* peekLS(LinkedStack* pStack)
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

void deleteLinkedStack(LinkedStack* pStack)
{
	if (!pStack)
		return ;
	while (pStack->pTopElement)
	{
		StackNode *temp = pStack->pTopElement->pLink;
		free(pStack->pTopElement);
		pStack->pTopElement = temp;
	}
	pStack->pTopElement = NULL;
	free(pStack);
	pStack = NULL;
}

int isLinkedStackFull(LinkedStack* pStack)
{
	// ...?
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->currentElementCount == 0);
}

int main()
{
	LinkedStack *stack = createLinkedStack();
	StackNode node;
	node.data = 'A';
	node.pLink = NULL;
	pushLS(stack, node);
	node.data = 'B';
	pushLS(stack, node);
	printf("%c\n", peekLS(stack)->data);
	printf("%c\n", popLS(stack)->data);
	printf("%c\n", popLS(stack)->data);
	deleteLinkedStack(stack);
}
