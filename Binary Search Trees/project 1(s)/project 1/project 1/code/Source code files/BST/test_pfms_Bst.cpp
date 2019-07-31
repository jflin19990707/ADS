#include "BST.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
const int iteration = 200;
using namespace std;

int main() {
	clock_t start, stop;
	BST T = NULL;
	cout << "Test performance of BST." << endl;
	cout << "Iteration: 200" << endl;
	cout << "Case one: Insert N integers in increasing order\
 and delete them in the same order." << endl;
	printf("%-10s", "Datasize");
	printf("%-7s", "Ticks");
	printf("%-14s", "TotalTime(s)");
	printf("%s\n", "Duration(s)");
	cout << "------------------------------------------" << endl;
	for (int n = 1000; n <= 10000; n += 250) {
		int ticks;
		start = clock();
		for (int it = 0; it < iteration; it++) {
			for (int i = 1; i <= n; i++) {
				T = Insert(i, T);
			}
			for (int i = 1; i <= n; i++) {
				T = Delete(i, T);
			}
		}
		stop = clock();
		printf("%-10d", n);
		printf("%-7d", stop - start);
		printf("%-14.6f", (double)(stop - start) / CLK_TCK);
		printf("%.6f\n", (double)(stop - start) / CLK_TCK / iteration);
	}
	cout << endl;


	cout << "Case two: Insert N integers in increasing order\
 and delete them in the reverse order." << endl;
	printf("%-10s", "Datasize");
	printf("%-7s", "Ticks");
	printf("%-14s", "TotalTime(s)");
	printf("%s\n", "Duration(s)");
	cout << "------------------------------------------" << endl;
	for (int n = 1000; n <= 10000; n += 250) {
		int ticks;
		start = clock();
		for (int it = 0; it < iteration; it++) {
			for (int i = 1; i <= n; i++) {
				T = Insert(i, T);
			}
			for (int i = n; i >= 1; i--) {
				T = Delete(i, T);
			}
		}
		stop = clock();
		printf("%-10d", n);
		printf("%-7d", stop - start);
		printf("%-14.6f", (double)(stop - start) / CLK_TCK);
		printf("%.6f\n", (double)(stop - start) / CLK_TCK / iteration);
	}

	cout << endl;

	cout << "Case three: Insert N integers in random order\
 and delete them in random order." << endl;
	printf("%-10s", "Datasize");
	printf("%-7s", "Ticks");
	printf("%-14s", "TotalTime(s)");
	printf("%s\n", "Duration(s)");
	cout << "------------------------------------------" << endl;
	srand(unsigned(time(NULL)));
	for (int n = 1000; n <= 10000; n += 250) {
		//Generate n distinct, random ordered element.
		int *p = new int[n];
		//Initialize the array with 1->n.
		for (int i = 0; i < n; i++) {
			p[i] = i + 1;
		}
		//Randomize the array.
		for (int i = 0; i < n; i++) {
			int tmp;
			int a = rand() % n;
			int b = rand() % n;
			tmp = p[a];
			p[a] = p[b];
			p[b] = tmp;
		}

		//Start processing
		start = clock();
		for (int it = 0; it < iteration; it++) {
			for (int i = 1; i <= n; i++) {
				T = Insert(p[i - 1], T);
			}
			//Randomize the array.
			for (int i = 0; i < n; i++) {
				int tmp;
				int a = rand() % n;
				int b = rand() % n;
				tmp = p[a];
				p[a] = p[b];
				p[b] = tmp;
			}
			for (int i = 1; i <= n; i++) {
				T = Delete(p[i - 1], T);
			}
		}
		stop = clock();
		printf("%-10d", n);
		printf("%-7d", stop - start);
		printf("%-14.6f", (double)(stop - start) / CLK_TCK);
		printf("%.6f\n", (double)(stop - start) / CLK_TCK / iteration);
		delete[]p;
	}
	system("pause");
	return 0;
}
