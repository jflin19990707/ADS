#include "Splay_Tree.h"
#include <iostream>
using namespace std;

int main() {
	int functionID;
	int tmp;

	SplayTree T = NULL;
	cout << "Function Test of SplayTree" << endl;
	cout << "----------" << endl;
	cout << "1.Insert" << endl
		<< "2.Delete" << endl
		<< "3.Access" << endl
		<< "4.Traverse" << endl
		<< "5.Initialize" << endl
		<< "0.Exit" << endl;
	cout << "----------" << endl << endl;
	cout << "Please input functionID:" << endl;

	cin >> functionID;
	cout << "----------" << endl;

	while (functionID) {
		switch (functionID)
		{
		case 1:
			cout << "Please input the element:" << endl;
			cin >> tmp;
			if (isExisted(tmp, T)) {
				cout << "Already existed!" << endl << endl;
				break;
			}
			T = Insert(tmp, T);
			cout << "Insert element " << tmp << " successfully!" << endl << endl;
			break;
		case 2:
			cout << "Please input the element:" << endl;
			cin >> tmp;
			if (!isExisted(tmp, T)) {
				cout << "Not Existed!" << endl << endl;
				break;
			}
			else {
				T = Delete(tmp, T);
				cout << "Delete element " << tmp << " successfully!" << endl << endl;
			}
			break;
		case 3:
			cout << "Please input the element:" << endl;
			cin >> tmp;
			if (isExisted(tmp, T)) {
				T = Access(tmp, T);
				cout << "Accessing complete." << endl << endl;
			}
			else {
				cout << "Not Existed." << endl << endl;
			}
			break;
		case 4:
			Traverse(T);
			cout << endl;
			break;
		case 5:
			T = Init_Tree(T);
			cout << "Successfully initialized." << endl << endl;
			break;
		default:
			cout << "Input Error" << endl << endl;
			break;
		}
		cout << "Please input functionID:" << endl;
		cin >> functionID;
		cout << "----------" << endl;
	}
	return 0;
}