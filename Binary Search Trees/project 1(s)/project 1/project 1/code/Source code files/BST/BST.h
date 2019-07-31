#ifndef _BST_H
#define _BST_H
typedef struct BstNode *Pos;
typedef struct BstNode *BST;

struct BstNode {
	int Element;
	BST Left;
	BST Right;
};

Pos FindMin(BST T);
//Find out the minimum and return the pointer.

Pos FindMax(BST T);
//Find out the maximum and return the pointer.

bool isExisted(int X, BST T);
//Element X is in the tree->return 1.

BST Init_Tree(BST T);
//Make an empty tree.

BST Insert(int X, BST T);
//Insert an element into the BST.

BST Delete(int X, BST T);
//Delete a certain element in the BST.

void Traverse(BST T);
//Print the preorder,inorder,postorder traversal.

#endif

