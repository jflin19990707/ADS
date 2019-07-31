#include <iostream>
#include <string>
#include <time.h>

#define KTIMES 1000//Number of cycles, time of recording small N
#define CLK_TCK CLOCKS_PER_SEC

using namespace std;

typedef struct node *Ptr;
struct node//define huffman tree 
{
	bool leaf;// whether leaf or not;
	int weight;// used to sort;
	int depth;//depth;
	Ptr left;
	Ptr right;
};

struct cf//use to establish problem huffman tree
{
	char character;
	int freq;
};

struct cc//use to eatablish answer huffman tree
{
	char anscharacter;
	int freq;
	string code;
};
//heap operation:
void percup(Ptr *list, int i);//used in insert heap
void ptrcdown(Ptr *list, int i);//used in deletemin
Ptr deletemin(Ptr *list);
void insert(Ptr *list, Ptr node);

int compute(Ptr tree);//compute PWL
Ptr buildprotree(int N, cf* pro);//build problem huffman tree
Ptr buildanstree(int N, cc *ans);//build answer huffman tree
void deletetree(Ptr tree);// delete huffman tree

clock_t start, stop;//used to record operation time
double duration[KTIMES];

int main()
{
	srand((unsigned)time(NULL));//reset clock time
	long long ticks = 0;
	double totaltime = 0;

	int N;
	int M, count = 1;
	int *result;
	cin >> N;//get N
	cf *pro;
	Ptr protree;
	Ptr anstree;
	int proPWL;
	cc *ans;
	int ansPWL;

	while(N != 0)//used to One-time processing of multi-clock data
	{
		N = N <= 63 ? N : 63;
		pro = new cf[N];
		for (int i = 0; i < N; i++)//Initialization
		{
			cin >> pro[i].character;
//			cout << pro[i].character << " ";
			cin >> pro[i].freq;
//			cout << pro[i].freq << " ";
		}
//		cout << endl;
		for (int e = 0; e < KTIMES; e++)//Cyclic time measurement
		{
			start = clock();
	    	protree = buildprotree(N, pro);//build problem tree
//	    	cout << "Build!" << endl;
	    	proPWL = compute(protree);//compute problem PWL
			stop = clock();//compute build tree and compute PWL time
			ticks = ticks + stop - start;
			duration[e] = ((double)(stop - start)) / CLK_TCK;
			totaltime = totaltime + duration[e];
		}
		cout << "Build huffman codes and compute PWL: " << totaltime / KTIMES << endl;
		cout << "Ticks: " << ticks << endl;
		ans = new cc[N];
		cin >> M;
		result = new int[M];
		for (int i = 0; i < M; i++)
		{
			for (int k = 0; k < N; k++)//Initialization
			{
				cin >> ans[k].anscharacter;
				for (int j = 0; j < N; j++)
				{
					if (pro[j].character == ans[k].anscharacter)//get the frequence from problem Initialization
					{
						ans[k].freq = pro[j].freq;
						break;
					}
				}
				cin >> ans[k].code;
			}
//			cout << "1" << endl;
            anstree = buildanstree(N, ans);//build tree
//			cout << "2" << endl;
	    	ansPWL = compute(anstree);//conpute PWL
	    	if (ansPWL == proPWL) result[i] = 1;//if problem PWL==answer PWL, the answer is right
			else result[i] = 0;
		}
		cout << "Case " << count << ":" << endl;
		for (int i = 0; i < M; i++)
		{
			if (result[i] == 1) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
		count++;
		cin >> N;
	}
	system("PAUSE");
}

void percup(Ptr *list, int i)//heap up
{
	Ptr nownode = list[i];
	int p;
	for (p = i; list[p / 2]->weight > nownode->weight; p = p / 2)//from up to down, if bigger
	{
		list[p] = list[p / 2];//up the smaller
	}
	list[p] = nownode;//set the node
}

void ptrcdown(Ptr *list, int i)//heap down
{
	Ptr nownode = list[i];
	int p = i;
	int child = p * 2;
	for (p = i; p * 2 <= list[0]->depth; p = child)//from down to up, if not out of range
	{
		child = p * 2;
		if (child + 1 <= list[0]->depth&&list[child + 1]->weight < list[child]->weight)//get the smaller child
		{
			child++;
		}
		if (list[child]->weight < nownode->weight)//if bigger bobble down
		{
			list[p] = list[child];
		}
		else break;
	}
	list[p] = nownode;
}

Ptr deletemin(Ptr *list)//delete min
{
	Ptr min = list[1];
	int N = list[0]->depth;
	list[0]->depth--;
	list[1] = list[N];//get the last to the first , bobble down
	list[N] = NULL;
	ptrcdown(list, 1);
	return min;
}

void insert(Ptr *list, Ptr node)//insrtion
{
	list[0]->depth++;
	list[list[0]->depth] = node;
	percup(list, list[0]->depth);//bobble up
}

int compute(Ptr tree)//conpute PWL
{
	if (tree == NULL || (tree->left == NULL && tree->right == NULL))
	{
		return 0;
	}
	else
	{
		Ptr queue[63], p;//use tail queue front to get the depth*weight
		int front = 0;
		int tail = 0;
		int PWL = 0;
		p = tree;
		p->depth = 0;
		queue[tail++] = p;
		while (tail != front)
		{
			p = queue[front++];
			if (front == 63) front = 0;
			if (p->leaf)//if leaf, conpute
			{
				PWL = PWL + p->weight*p->depth;
			}
			else
			{
				if (p->right == NULL || p->left == NULL)//It ends before the end, indicating that the establishment is incorrect.
				{
					return -1;
				}
				else
				{
					p->right->depth = p->depth + 1;//set the right/left child depth 
					p->left->depth = p->right->depth;
					queue[tail++] = p->left;//set into the queue
					if (tail == 63) tail = 0;//loop to use
					else tail = tail;
					queue[tail++] = p->right;//set into the queue
					if (tail == 63) tail = 0;
					else tail = tail;
				}
			}
		}
	return PWL;
	}
}

Ptr buildprotree(int N, cf* pro)//build heap
{
	Ptr *heap, ptr, ptr1, ptr2;
	heap = new Ptr[N + 1];
	for (int i = 0; i < N + 1; i++)//Initialization
	{
		ptr = new node;
		if (i == 0) ptr->depth = N;//heap[0] used to insert
		else ptr->depth = 0;//Initialization depth
		ptr->leaf = true;
		ptr->left = NULL;
	    ptr->right = NULL;
		if (i == 0) ptr->weight = -1e8;//Setting an Impossible Value
		else ptr->weight = pro[i - 1].freq;
		heap[i] = ptr;
	}

	for (int i = N / 2; i > 0; i--) ptrcdown(heap, i);//Sort heaps from small to large

	while (heap[0]->depth > 1)//build heap trees by heaps
	{
		ptr1 = deletemin(heap);//get the first smallest
		ptr2 = deletemin(heap);//get the second smallest
		ptr = new node;
		ptr->weight = ptr1->weight + ptr2->weight;//get the new node weight
		ptr->leaf = false;
		ptr->left = ptr1;//link the old one to the new one
		ptr->right = ptr2;
		ptr->depth = 0;
		insert(heap, ptr);//insert heap into heaps
	}
	ptr = heap[1];
	delete[]heap;
	return ptr;
}

Ptr buildanstree(int N, cc *ans)
{
	Ptr tree = new node;
	Ptr ptr;
	string nowstring;
	tree->leaf = false;
	tree->left = NULL;
	tree->right = NULL;
	for (int i = 0; i < N; i++)
	{
		ptr = tree;
		nowstring = ans[i].code;
		for (int j = 0; j < nowstring.length(); j++)
		{
			if (nowstring.at(j) == '0')//0-> is left
			{
				if (ptr->left == NULL)
				{
					ptr->left = new node;//initialization
					ptr = ptr->left;
					ptr->left = NULL;
					ptr -> right = NULL;
					if (j + 1 == nowstring.length())//if loop into the last one character
					{
						ptr->leaf = true;// set is leaf
						ptr->weight = ans[i].freq;//set weight
						break;
					}
					else
					{
						ptr->leaf = false;
					}
				}
				else if (ptr->left->leaf == true)//not null and not the string ends but is leaf, not the huffman code answer
				{
					deletetree(tree);
					return NULL;
				}
				else//loop in
				{
					ptr = ptr->left;
				}
			}
			else//1-> is right
			{
				if (ptr->right == NULL)
				{
					ptr->right = new node;//initialization
					ptr = ptr->right;
					ptr->left = NULL;
					ptr->right = NULL;
					if (j + 1 == nowstring.length())//if loop into the last one character
					{
						ptr->leaf = true;// set is leaf
						ptr->weight = ans[i].freq;//set weight
						break;
					}
					else
					{
						ptr->leaf = false;
					}
				}
				else if (ptr->right->leaf == true)//not null and not the string ends but is leaf, not the huffman code answer
				{
					deletetree(tree);
				}
				else
				{
					ptr = ptr->right;
				}
			}
		}
	}
	return tree;
}

void deletetree(Ptr tree)//delete tree
{
	if (tree->left != NULL) deletetree(tree->left);
	if (tree->right != NULL) deletetree(tree->right);
	delete(tree);
}
