#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>

BinTree* makeBinTree(BinTreeNode rootNode)
{
	BinTree* pBinTree;

	pBinTree = malloc(sizeof(BinTree));
	if (!pBinTree){
		printf("bintree 할당 실패\n");
		return (NULL);
	}
	pBinTree->pRootNode = malloc(sizeof(BinTreeNode));
	if (!pBinTree->pRootNode)
	{
		printf("root node 할당실패\n");
		return (NULL);
	}
	*(pBinTree->pRootNode) = rootNode;
	return (pBinTree);
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
	if (!pBinTree)
		return (NULL);
	return (pBinTree->pRootNode);
}

BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	if (!pParentNode)
		return (NULL);
	pParentNode->pLeftChild = malloc(sizeof(BinTreeNode));
	if (!pParentNode->pLeftChild)
		return (NULL);
	*(pParentNode->pLeftChild) = element;
	return (pParentNode);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	if (!pParentNode)
		return (NULL);
	pParentNode->pRightChild = malloc(sizeof(BinTreeNode));
	if (!pParentNode->pRightChild)
		return (NULL);
	*(pParentNode->pRightChild) = element;
	return (pParentNode);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
	if (!pNode)
		return (NULL);
	return (pNode->pLeftChild);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
	if (!pNode)
		return (NULL);
	return (pNode->pRightChild);
}

void deleteBinTree(BinTree* pBinTree)
{
	deleteBinTreeNode(pBinTree->pRootNode);
	free(pBinTree);
	pBinTree = NULL;
}

void deleteBinTreeNode(BinTreeNode* pNode)
{
	free(pNode->pLeftChild);
	pNode->pLeftChild = NULL;
	free(pNode->pRightChild);
	pNode->pRightChild = NULL;
	free(pNode);
	pNode = NULL;
}

void preorderTraversalBinTree(BinTreeNode* pNode)
{
	if (!pNode)
		return ;
	printf("%c ", pNode->data);
	if (pNode->pLeftChild)
		preorderTraversalBinTree(pNode->pLeftChild);
	if (pNode->pRightChild)
		preorderTraversalBinTree(pNode->pRightChild);
}

void inorderTraversalBinTree(BinTreeNode* pNode)
{
	if (!pNode)
		return ;
	if (pNode->pLeftChild)
		inorderTraversalBinTree(pNode->pLeftChild);
	printf("%c ", pNode->data);
	if (pNode->pRightChild)
		inorderTraversalBinTree(pNode->pRightChild);
}

void postorderTraversalBinTree(BinTreeNode* pNode)
{
	if (!pNode)
		return ;
	if (pNode->pLeftChild)
		postorderTraversalBinTree(pNode->pLeftChild);
	if (pNode->pRightChild)
		postorderTraversalBinTree(pNode->pRightChild);
	printf("%c ", pNode->data);
}

int main()
{
	BinTree* pBinTree;
	BinTreeNode pBinTreeNode;

	pBinTreeNode.visited = 0;
	pBinTreeNode.pLeftChild = NULL;
	pBinTreeNode.pRightChild = NULL;
	pBinTreeNode.data = 'A';
	pBinTree = makeBinTree(pBinTreeNode);
	pBinTreeNode.data = 'B';
	insertLeftChildNodeBT(pBinTree->pRootNode, pBinTreeNode);
	pBinTreeNode.data = 'C';
	insertRightChildNodeBT(pBinTree->pRootNode, pBinTreeNode);
	pBinTreeNode.data = 'D';
	insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild, pBinTreeNode);
	pBinTreeNode.data = 'E';
	insertRightChildNodeBT(pBinTree->pRootNode->pLeftChild, pBinTreeNode);
	pBinTreeNode.data = 'F';
	insertLeftChildNodeBT(pBinTree->pRootNode->pRightChild, pBinTreeNode);
	pBinTreeNode.data = 'G';
	insertRightChildNodeBT(pBinTree->pRootNode->pRightChild, pBinTreeNode);
	pBinTreeNode.data = 'H';
	insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild->pLeftChild, pBinTreeNode);
	pBinTreeNode.data = 'I';
	insertRightChildNodeBT(pBinTree->pRootNode->pLeftChild->pLeftChild, pBinTreeNode);
	pBinTreeNode.data = 'J';
	insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild->pRightChild, pBinTreeNode);
	pBinTreeNode.data = 'K';
	insertRightChildNodeBT(pBinTree->pRootNode->pRightChild->pLeftChild, pBinTreeNode);
	pBinTreeNode.data = 'L';
	insertLeftChildNodeBT(pBinTree->pRootNode->pRightChild->pRightChild, pBinTreeNode);
	pBinTreeNode.data = 'M';
	insertRightChildNodeBT(pBinTree->pRootNode->pRightChild->pRightChild, pBinTreeNode);
	// printf("%c\n", getRootNodeBT(pBinTree)->data);
	// printf("%c\n", getLeftChildNodeBT(pBinTree->pRootNode)->data);
	// printf("%c\n", getRightChildNodeBT(pBinTree->pRootNode)->data);
	printf("====preorder====\n");
	preorderTraversalBinTree(pBinTree->pRootNode);
	printf("\n");
	printf("====Inorder====\n");
	inorderTraversalBinTree(pBinTree->pRootNode);
	printf("\n");
	printf("====postorder====\n");
	postorderTraversalBinTree(pBinTree->pRootNode);
	printf("\n");
}
