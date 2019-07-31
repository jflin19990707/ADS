#include "BST.h"
#include <iostream>
using namespace std;

//Functions of Traversal
void PrintNode(BST T) {
	cout << T->Element << " ";
}

void PreorderTraverse(BST T) {
	PrintNode(T);
	if (T->Left) PreorderTraverse(T->Left);
	if (T->Right) PreorderTraverse(T->Right);
}

void InorderTraverse(BST T) {
	if (T->Left) InorderTraverse(T->Left);
	PrintNode(T);
	if (T->Right) InorderTraverse(T->Right);
}

void PostorderTraverse(BST T) {
	if (T->Left) PostorderTraverse(T->Left);
	if (T->Right) PostorderTraverse(T->Right);
	PrintNode(T);
}

void Traverse(BST T) {
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

bool isExisted(int X, BST T) {
	if (T == NULL) return 0;
	if (X == T->Element) return 1;
	if (X > T->Element) return isExisted(X, T->Right);
	if (X < T->Element) return isExisted(X, T->Left);
}

Pos FindMin(BST T) {
	if (T != NULL)
		while (T->Left != NULL) T = T->Left;
	return T;
}

Pos FindMax(BST T) {
	if (T != NULL)
		while (T->Right != NULL) T = T->Right;
	return T;
}

BST Init_Tree(BST T) {
	if (T != NULL) {
		Init_Tree(T->Left);
		Init_Tree(T->Right);
		delete T;
	}
	return NULL;
}

//Function of insertion
BST Insert(int X, BST T) {
	//Return a one-node tree.
	if (T == NULL) {
		T = new BstNode;
		T->Element = X;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element) {
		T->Left = Insert(X, T->Left);//Recursive Insertion to the Left.
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);//Recursive Insertion to the Right.
	}
	return T;
}

//delete
BST Delete(int X, BST T) {
	Pos tmp;
	if (X < T->Element) T->Left = Delete(X, T->Left);
	else if (X > T->Element) T->Right = Delete(X, T->Right);
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

	return T;
}