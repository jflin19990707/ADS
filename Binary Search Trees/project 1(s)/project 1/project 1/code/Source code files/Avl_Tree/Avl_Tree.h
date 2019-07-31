#ifndef _Avl_Tree_H
#define _Avl_Tree_H
typedef struct AvlNode *Pos;
typedef struct AvlNode *AvlTree;

struct AvlNode {
	int Element;
	AvlTree Left;
	AvlTree Right;
	int height;
};

Pos FindMin(AvlTree T);
//Find out the minimum and return the pointer.

Pos FindMax(AvlTree T);
//Find out the maximum and return the pointer.

AvlTree Init_Tree(AvlTree T);
//Make an empty tree.

bool isExisted(int X, AvlTree T);
//Element X is in the tree->return 1.

AvlTree Insert(int X, AvlTree T);
//Insert an element into the avl tree.

AvlTree Delete(int X, AvlTree T);
//Delete a certain element in the avl tree.

void Traverse(AvlTree T);
//Print the preorder,inorder,postorder traversal.

#endif
