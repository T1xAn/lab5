#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <queue> 
using namespace std;
struct node {
	int numb;
	node* next;
};
struct graf {
	node** nodes;
	int size;
};

struct qeuestr {
	int numb;
	qeuestr* next;
};

void Bfg9000_matrix(int** arr, int size, int* versh, int num ){
	clock_t start, end;
	
	int i;
	queue <int> q;
	versh[num] = 1;
	q.push(num);
	start = clock();
	while(!q.empty()){
		i = q.front();
		q.pop();
		cout << " " << i << "-> " ;
		for(int j = 0; j < size; j++){
		if(arr[i][j] == 1 && versh[j] == 0){
			q.push(j);
			versh[j] = 1;
		}
	}
}
	end = clock();
	double time = difftime(end, start) / CLOCKS_PER_SEC;
	cout << endl << time << endl;
}

void Bfg9000_spisok(graf* grafon, int size, int* versh, int num ){
	int i;
	cout << "  " ;
	queue <int> q;
	versh[num] = 1;
	q.push(num);
	node* buf;
	while(!q.empty()) {
		num = q.front();
		buf = grafon->nodes[num];
		q.pop();
		cout << " " << num << "-> ";
		while (buf != NULL) {
			if (versh[buf->numb] == 0) {
				q.push(buf->numb);
				versh[buf->numb] = 1;
			}
			buf = buf->next;
		}
	}
}

void spisok_q(int** arr, int size, int* versh, int num) {
	int i;
	clock_t start, end;
	qeuestr* create;
	qeuestr* buf;
	qeuestr* head = new qeuestr;
	versh[num] = 1;
	head->numb = num;
	head->next = NULL;
	start = clock();
	while (head != NULL) {
		i = head->numb;
		cout << " " << i << "-> ";
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 1 && versh[j] == 0) {
				qeuestr* create = new qeuestr;
				create->numb = j;
				create->next = NULL;
				buf = head;
				while (buf->next != NULL) {
					buf = buf->next;
				}
				buf->next = create;
				versh[j] = 1;
			}
		}
		buf = head->next;
		delete(head);
		head = buf;
	}
	end = clock();
	double time = difftime(end, start) / CLOCKS_PER_SEC;
	cout << endl << time << endl;
}

graf* sozdat(int versh) {

	graf* grafon = new graf;
	grafon->size = versh;
	grafon->nodes = new node* [versh];
	for (int i = 0; i < versh; i++) {
		grafon->nodes[i] = NULL;
	}
	return grafon;
}
node* sozdatnode(int index) {
	node* newnode = new node;
	newnode->numb = index;
	newnode->next = NULL;
	return newnode;
}

void addgran(graf* grafon, int from, int to) {
	node* newnode = sozdatnode(from);
	if (grafon->nodes[to] == 0) {
		grafon->nodes[to] = newnode;
		newnode = NULL;
	}
	node* buf = grafon->nodes[to];
	while (buf->next != NULL) {
		buf = buf->next;
	}
	buf->next = newnode;

	newnode = sozdatnode(to);
	if (grafon->nodes[from] == 0) {
		grafon->nodes[from] = newnode;
		return;
	}
	buf = grafon->nodes[from];
	while (buf->next != NULL) {
		buf = buf->next;
	}
	buf->next = newnode;
}
void main(){
srand(time(0));
setlocale (LC_ALL, "Russian");
int size;

cout << "   ¬ведите размерность матрицы: "<< " ";
cin >> size;
cout << endl;

int** arr = new int* [size];

for (int count = 0; count < size; ++count)
	arr[count] = new int[size];

for(int row = 0;row< size;row++){
	arr[row][row] = 0;
	for(int col = row+1;col< size;col++){
		arr[row][col] = rand()%2;
		arr [col][row] = arr[row][col];
	}
}
cout << "   ";
for(int row = 0;row < size;row++)
{
	for(int col = 0; col < size;col++){
cout << arr[row][col] << " " ;
	}
cout << endl << "   ";
}
cout << endl;

auto versh = new int[size];
for (int i = 0; i < size; i++)
	versh[i] = 0;
cout << "   ¬ведите номер вершины, с которой хотите начать обход: ";
int num;
cin >> num;
cout << endl << "   ";


Bfg9000_matrix(arr, size, versh ,num);

	system("pause");

cout << endl << endl << "   ќбход в глубину списков смежности" << endl;
cout << "   " << endl;

graf* grafon = sozdat(size);
int j = 1;
for (int i = 0; i < size; i++) {
	for (j; j < size; j++) {
		if (arr[i][j] == 1) {
			addgran(grafon, i, j);
		}
	}
	j = j - size + i + 1;
}
cout << "   ";
for (int i = 0; i < size; i++) {
	node* temp = grafon->nodes[i];
	cout << i;

	while (temp) {
		cout << " -> " << temp->numb;
		temp = temp->next;
	}
	cout << endl << "   ";
}
cout << "   ¬ведите номер вершины, с которой хотите начать обход: ";
num = 0;
cin >> num;

for (int i = 0; i < size; i++)
	versh[i] = 0;
Bfg9000_spisok(grafon, size, versh, num);


cout << endl << endl << "   ќбход в глубину c очередью составленной списками" << endl;
cout << "   ¬ведите номер вершины, с которой хотите начать обход: ";
num = 0;
cin >> num;
for (int i = 0; i < size; i++)
	versh[i] = 0;
spisok_q(arr, size, versh, num);



system("pause");
}

