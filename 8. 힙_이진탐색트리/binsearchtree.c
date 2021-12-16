#include "binsearchtree.h"
#include <stdlib.h>
#include <stdio.h>

BinSearchTree* createBinSearchTree()
{
	BinSearchTree* pTree;
	pTree = malloc(sizeof(BinSearchTree));
	if (!pTree)
		return (NULL);
	return (pTree);
}

int insertElementBST(BinSearchTree* pBinSearchTree, BinSearchTreeNode element)
{
	BinSearchTreeNode* pNode;
	BinSearchTreeNode* parent;

	if (!pBinSearchTree)
		return (FALSE);
	parent = pBinSearchTree->pRootNode;
	if (!parent)
	{
		pBinSearchTree->pRootNode = malloc(sizeof(BinSearchTreeNode));
		if (!pBinSearchTree->pRootNode)
			return (FALSE);
		*(pBinSearchTree->pRootNode) = element;
		return (TRUE);
	}
	while (parent)
	{
		if (parent->key == element.key)
			return (FALSE);
		else if (parent->key > element.key)
		{
			if (parent->pLeftChild == NULL)
			{
				pNode = malloc(sizeof(BinSearchTreeNode));
				if (!pNode)
					return (FALSE);
				*pNode = element;
				parent->pLeftChild = pNode;
			}
			else
				parent = parent->pLeftChild;
		}
		else
		{
			if (parent->pRightChild == NULL)
			{
				pNode = malloc(sizeof(BinSearchTreeNode));
				if (!pNode)
					return (FALSE);
				*pNode = element;
				parent->pRightChild = pNode;
			}
			else
				parent = parent->pRightChild;
		}
	}
	return (TRUE);
}

int deleteElementBST(BinSearchTree* pBinSearchTree, int key)
{
	BinSearchTreeNode* pParent;
	BinSearchTreeNode* pNode;

	if (!pBinSearchTree)
		return (FALSE);
	pParent = pBinSearchTree->pRootNode;
	if (pParent->key == key)
	{
		pBinSearchTree->pRootNode = NULL;
		return (TRUE);
	}
	while (pParent)
	{
		if (pParent->pLeftChild->key == key)
		{
			pNode = pParent->pLeftChild;
			break;
		}
		else if (pParent->pRightChild->key == key)
		{
			pNode = pParent->pRightChild;
			break;
		}
		else if (pParent->key > key)
			pParent = pParent->pLeftChild;
		else
			pParent = pParent->pRightChild;
	}
	if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL)
	{
		pParent->pLeftChild = NULL;
		pParent->pRightChild = NULL;
		free(pNode);
	}
	else if (pNode->pLeftChild == NULL || pNode->pRightChild == NULL)
	{
		free(pNode);
		if (pNode->pLeftChild == NULL)
		{
			pNode = pNode->pLeftChild;
			pParent->pLeftChild = pNode;
		}
		else
		{
			pNode = pNode->pRightChild;
			pParent->pRightChild = pNode;
		}
	}
	else
	{

	}
	return (TRUE);
}

BinSearchTreeNode* searchRecursiveBST(BinSearchTree* pBinSearchTree, int key)
{
	if (!pBinSearchTree)
		return (NULL);
	return (searchInternalRecursiveBST(pBinSearchTree->pRootNode, key));
}

BinSearchTreeNode* searchInternalRecursiveBST(BinSearchTreeNode* pTreeNode, int key)
{
	if(!pTreeNode)
		return (NULL);
	if (pTreeNode->key > key)
		return (searchInternalRecursiveBST(pTreeNode->pLeftChild,key));
	else if(pTreeNode->key < key)
		return (searchInternalRecursiveBST(pTreeNode->pRightChild,key));
	else
		return (pTreeNode);
}

BinSearchTreeNode* searchBST(BinSearchTree* pBinSearchTree, int key)
{
	BinSearchTreeNode* result;

	if (!pBinSearchTree)
		return (NULL);
	result = pBinSearchTree->pRootNode;
	while (result)
	{
		if (result->key == key)
			break;
		else if (result->key > key)
			result = result->pLeftChild;
		else
			result = result->pRightChild;
	}
	return (result);
}

void deleteBinSearchTree(BinSearchTree* pBinSearchTree)
{
	if (!pBinSearchTree)
		return ;
	if (pBinSearchTree->pRootNode)
		deleteBinSearchTreeInternal(pBinSearchTree->pRootNode);
	free(pBinSearchTree);
}

void deleteBinSearchTreeInternal(BinSearchTreeNode* pTreeNode)
{
	if (!pTreeNode)
		return ;
	if (pTreeNode->pLeftChild)
		deleteBinSearchTreeInternal(pTreeNode->pLeftChild);
	if (pTreeNode->pRightChild)
		deleteBinSearchTreeInternal(pTreeNode->pRightChild);
	free(pTreeNode);
}

void inorderTraversalBinTree(BinSearchTreeNode* pNode)
{
	if (!pNode)
		return ;
	if (pNode->pLeftChild)
		inorderTraversalBinTree(pNode->pLeftChild);
	printf("%d ", pNode->key);
	if (pNode->pRightChild)
		inorderTraversalBinTree(pNode->pRightChild);
}

int main()
{
	BinSearchTree* pTree;
	BinSearchTreeNode node;

	pTree = createBinSearchTree();
	node.key = 1;
	node.value = 'a';
	node.pLeftChild = NULL;
	node.pRightChild = NULL;
	insertElementBST(pTree, node);
	node.key = 2;
	node.value = 'b';
	insertElementBST(pTree, node);
	node.key = 30;
	insertElementBST(pTree, node);
	node.key = 20;
	insertElementBST(pTree, node);
	node.key = 40;
	insertElementBST(pTree, node);
	node.key = 10;
	insertElementBST(pTree, node);
	node.key = 24;
	insertElementBST(pTree, node);
	node.key = 34;
	insertElementBST(pTree, node);
	node.key = 46;
	insertElementBST(pTree, node);
	node.key = 6;
	insertElementBST(pTree, node);
	node.key = 14;
	insertElementBST(pTree, node);
	node.key = 22;
	insertElementBST(pTree, node);
	inorderTraversalBinTree(pTree->pRootNode);
	// printf("%c\n", searchBST(pTree, 1)->value);
	// printf("%c\n", searchBST(pTree, 2)->value);
	printf("%d\n", searchRecursiveBST(pTree, 10)->key);
	deleteBinSearchTree(pTree);
}
