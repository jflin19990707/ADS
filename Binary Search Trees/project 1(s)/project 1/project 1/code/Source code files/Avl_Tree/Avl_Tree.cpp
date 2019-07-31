#include "Avl_Tree.h"
#include <iostream>
using namespace std;

AvlTree Init_Tree(AvlTree T) {
	if (T != NULL) {
		Init_Tree(T->Left);
		Init_Tree(T->Right);
		delete T;
	}
	return NULL;
}

//Functions of Insert
AvlTree rLeft(AvlTree T);//LL->SingleRotateWithLeft
AvlTree rRight(AvlTree T);//RR->SingleRotateWithRight
AvlTree dRLeft(AvlTree T);//LR->DoubleRotateWithLeft
AvlTree dRRight(AvlTree T);//RL->DoubleRotateWithRight
int getHeight(AvlTree T);//Get the height of a certain tree node.

AvlTree Insert(int X, AvlTree T) {
	//Return a one-node tree.
	if (T == NULL) {
		T = new AvlNode;
		T->Element = X;
		T->height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element) {
		T->Left = Insert(X, T->Left);//Recursive Insertion to the Left.
		if (getHeight(T->Left) - getHeight(T->Right) == 2) {
			//LL
			if (X < T->Left->Element) T = rLeft(T);
			//LR
			else T = dRLeft(T);
		}
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);//Recursive Insertion to the Right.
		if (getHeight(T->Right) - getHeight(T->Left) == 2) {
			//RR
			if (X > T->Right->Element) {
				T = rRight(T);
			}
			//RL
			else {
				T = dRRight(T);
			}
		}
	}
	T->height = getHeight(T->Left) > getHeight(T->Right) ? getHeight(T->Left) + 1 : getHeight(T->Right) + 1;
	return T;
}

AvlTree rLeft(AvlTree T) {
	Pos p;

	p = T->Left;
	T->Left = p->Right;
	p->Right = T;

	T->height = getHeight(T->Left) > getHeight(T->Right) ? getHeight(T->Left) + 1 : getHeight(T->Right) + 1;
	p->height = getHeight(p->Left) > getHeight(p->Right) ? getHeight(p->Left) + 1 : getHeight(p->Right) + 1;
	return p;
}

AvlTree rRight(AvlTree T) {
	Pos p;

	p = T->Right;
	T->Right = p->Left;
	p->Left = T;

	T->height = getHeight(T->Left) > getHeight(T->Right) ? getHeight(T->Left) + 1 : getHeight(T->Right) + 1;
	p->height = getHeight(p->Left) > getHeight(p->Right) ? getHeight(p->Left) + 1 : getHeight(p->Right) + 1;

	return p;
}

AvlTree dRLeft(AvlTree T) {
	T->Left = rRight(T->Left);
	return rLeft(T);
}

AvlTree dRRight(AvlTree T) {
	T->Right = rLeft(T->Right);
	return rRight(T);
}

int getHeight(AvlTree T)
{
	if (T == NULL) return -1;
	else return T->height;
}

//Functions of Traversal
void PrintNode(AvlTree T) {
	cout << T->Element << " ";
}

void PreorderTraverse(AvlTree T) {
	PrintNode(T);
	if (T->Left) PreorderTraverse(T->Left);
	if (T->Right) PreorderTraverse(T->Right);
}

void InorderTraverse(AvlTree T) {
	if (T->Left) InorderTraverse(T->Left);
	PrintNode(T);
	if (T->Right) InorderTraverse(T->Right);
}

void PostorderTraverse(AvlTree T) {
	if (T->Left) PostorderTraverse(T->Left);
	if (T->Right) PostorderTraverse(T->Right);
	PrintNode(T);
}

void Traverse(AvlTree T) {
	if (T == NULL) {
		cout << "EMPTY TREE!" << endl;
		return;
	}
	cout << "Preorder: " << endl;
	PreorderTraverse(T);
	cout << endl;
	cout << "Inorder: " << endl;
	InorderTraverse(T);
	cout << endl;
	cout << "Postorder: " << endl;
	PostorderTraverse(T);
	cout << endl;
}

bool isExisted(int X, AvlTree T) {
	if (T == NULL) return 0;
	if (X == T->Element) return 1;
	if (X > T->Element) return isExisted(X, T->Right);
	if (X < T->Element) return isExisted(X, T->Left);
}

Pos FindMin(AvlTree T) {
	if (T != NULL)
		while (T->Left != NULL) T = T->Left;
	return T;
}

Pos FindMax(AvlTree T) {
	if (T != NULL)
		while (T->Right != NULL) T = T->Right;
	return T;
}

AvlTree Delete(int X, AvlTree T) {
	Pos tmp;
	if (X < T->Element) {
		T->Left = Delete(X, T->Left);
		//The deletion caused unbalance in subtree of root T.
		if (getHeight(T->Right) - getHeight(T->Left) == 2) {
			//RR
			if (getHeight(T->Right->Right) > getHeight(T->Right->Left)) {
				T = rRight(T);
			}
			//RL
			else {
				T = dRRight(T);
			}
		}
	}
	else if (X > T->Element) {
		T->Right = Delete(X, T->Right);
		//The deletion caused unbalance in subtree of root T.
		if (getHeight(T->Left) - getHeight(T->Right) == 2) {
			//LL
			if (getHeight(T->Left->Left) > getHeight(T->Left->Right)) {
				T = rLeft(T);
			}
			//LR
			else {
				T = dRLeft(T);
			}
		}
	}
	/*
		The element to be deleted has been found.
		case: Two children.
	*/
	else if (T->Left&&T->Right) {
		/*Replace with smallest in right subtree*/
		tmp = FindMin(T->Right);
		T->Element = tmp->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	/*case: One or zero children*/
	else {
		tmp = T;
		if (T->Left == NULL) {
			T = T->Right;
		}
		else if (T->Right == NULL) {
			T = T->Left;
		}
		delete tmp;
	}
	if (T != NULL)
		T->height = getHeight(T->Left) > getHeight(T->Right) ? getHeight(T->Left) + 1 : getHeight(T->Right) + 1;
	return T;
}