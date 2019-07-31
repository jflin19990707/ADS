#include <iostream>
#ifndef _Splay_Tree_H
#define _Splay_Tree_H
typedef struct SplayNode *Pos;
typedef struct SplayNode *SplayTree;

struct SplayNode {
	int Element;
	SplayTree Left;
	SplayTree Right;
	SplayTree Father;
	int height;
};

Pos AccessNode(int X, SplayTree T);
//Access one node and return its pointer.

Pos Access(int X, SplayTree T);
//Access one node and splay the tree.

Pos FindMin(SplayTree T);
//Find out the minimum and return the pointer.

Pos FindMax(SplayTree T);
//Find out the maximum and return the pointer.

SplayTree Init_Tree(SplayTree T);
//Make an empty tree.

bool isExisted(int X, SplayTree T);
//Element X is in the tree->return 1.

SplayTree Insert(int X, SplayTree T);
//Insert an element into the splay tree and splay it.

SplayTree InsertNode(int X, SplayTree T);
//Insert an element into the splay tree.

SplayTree Delete(int X, SplayTree T);
//Delete a certain element in the splay tree.

SplayTree Splay(Pos T);
//Splay a certain element to the root.

void Traverse(SplayTree T);
//Print the preorder, inorder, postorder traversal.

#endif
