#include "Splay_Tree.h"
#include <iostream>
using namespace std;

SplayTree Init_Tree(SplayTree T) {
	if (T != NULL) {
		Init_Tree(T->Left);
		Init_Tree(T->Right);
		delete T;
	}
	return NULL;
}

//Functions of Traversal
void PrintNode(SplayTree T) {
	cout << T->Element << " ";
}

void PreorderTraverse(SplayTree T) {
	PrintNode(T);
	if (T->Left) PreorderTraverse(T->Left);
	if (T->Right) PreorderTraverse(T->Right);
}

void InorderTraverse(SplayTree T) {
	if (T->Left) InorderTraverse(T->Left);
	PrintNode(T);
	if (T->Right) InorderTraverse(T->Right);
}

void PostorderTraverse(SplayTree T) {
	if (T->Left) PostorderTraverse(T->Left);
	if (T->Right) PostorderTraverse(T->Right);
	PrintNode(T);
}

void Traverse(SplayTree T) {
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

bool isExisted(int X, SplayTree T) {
	if (T == NULL) return 0;
	if (X == T->Element) return 1;
	if (X > T->Element) return isExisted(X, T->Right);
	if (X < T->Element) return isExisted(X, T->Left);
}

Pos FindMin(SplayTree T) {
	if (T != NULL)
		while (T->Left != NULL) T = T->Left;
	return T;
}

Pos FindMax(SplayTree T) {
	if (T != NULL)
		while (T->Right != NULL) T = T->Right;
	return T;
}

Pos p1;
SplayTree Insert(int X, SplayTree T) {
	T = InsertNode(X, T);
	return Splay(p1);
}

SplayTree InsertNode(int X, SplayTree T) {
	//Return a one-node tree.
	if (T == NULL) {
		T = new SplayNode;
		T->Element = X;
		T->height = 0;
		T->Left = T->Right = NULL;
		T->Father = NULL; 
		p1 = T;
	}
	else if (X < T->Element) {
		T->Left = InsertNode(X, T->Left);//Recursive Insertion to the Left.
		T->Left->Father = T;
	}
	else if (X > T->Element) {
		T->Right = InsertNode(X, T->Right);//Recursive Insertion to the Right.
		T->Right->Father = T;
	}
	return T;
}

Pos AccessNode(int X, SplayTree T) {
	if (X == T->Element) return T;
	if (X > T->Element) return AccessNode(X, T->Right);
	if (X < T->Element) return AccessNode(X, T->Left);
}

Pos Access(int X, SplayTree T) {
	Pos p;
	p = AccessNode(X, T);
	return Splay(p);
}

//Functions of rotation
//clockwise
void Zig(Pos x) {
	Pos tmp;
	if (x->Father->Father) {
		if(x->Father->Father->Right == x->Father)
		x->Father->Father->Right = x;
		else x->Father->Father->Left = x;
	}
	tmp = x->Father->Father;
	x->Father->Father = x;
	if (x->Right) {
		x->Right->Father = x->Father;
	}
	x->Father->Left = x->Right;
	x->Right = x->Father;
	x->Father = tmp;
}

//unclockwise
void Zag(Pos x) {
	Pos tmp;
	if (x->Father->Father) {
		if(x->Father->Father->Left == x->Father)
		x->Father->Father->Left = x;
		else x->Father->Father->Right = x;
	}
	tmp = x->Father->Father;
	x->Father->Father = x;
	if (x->Left) {
		x->Left->Father = x->Father;
	}
	x->Father->Right = x->Left;
	x->Left = x->Father;
	x->Father = tmp;
}

SplayTree Splay(Pos x) {
	if (x->Father == NULL) return x;
	//Nonrecursive solution
	//To splay the current node to the root.
	while (x->Father != NULL) {
		Pos p = x->Father;
		Pos gp = p->Father;
		//The grandparent is still existed.
		if (gp != NULL) {
			//LL
			if (gp->Left == p && p->Left == x) {
				Zig(p); Zig(x);
			}
			//RR
			else if (gp->Right == p && p->Right == x) {
				Zag(p); Zag(x);
			}
			//LR
			else if (gp->Left == p && p->Right == x) {
				Zag(x); Zig(x);
			}
			//RL
			else if (gp->Right == p && p->Left == x) {
				Zig(x); Zag(x);
			}
		}
		//Parent is the root.
		else {
			if (p->Left == x) {
				Zig(x);
			}
			else {
				Zag(x);
			}
		}
		if (x->Father == NULL) return x;
	}

}

Pos p2 = NULL;

SplayTree DeleteNode(int X, SplayTree T) {
	Pos tmp;
	if (X < T->Element) T->Left = DeleteNode(X, T->Left);
	else if (X > T->Element) T->Right = DeleteNode(X, T->Right);
	/*
		The element to be deleted has been found.
		case: Two children.
	*/
	else if (T->Left&&T->Right) {
		/*Replace with smallest in right subtree*/
		tmp = FindMin(T->Right);
		T->Element = tmp->Element;
		T->Right = DeleteNode(T->Element, T->Right);
	}
	/*case: One or zero children*/
	else {
		tmp = T;
		if (T->Left == NULL) {
			if (T->Right) T->Right->Father = T->Father;
			T = T->Right;

		}
		else if (T->Right == NULL) {
			if (T->Left) T->Left->Father = T->Father;
			T = T->Left;
		}
		p2 = T;
		delete tmp;
	}

	return T;
}

SplayTree Delete(int X, SplayTree T) {
	T = Access(X, T);
	T = DeleteNode(X, T);
	return T;
}


