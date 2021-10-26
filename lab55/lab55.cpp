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

struct que_node {
	int numb;
	que_node* next;
};
struct quqech {
	que_node* front;
	que_node* back;
	int size;
};

graf* sozdat(int versh) {

	graf* grafon = new graf;
	grafon->size = versh;
	grafon->nodes = new node * [versh];
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

quqech* create_que() {

	quqech* que = new quqech;
	que->size = NULL;
	que->front = NULL;
	que->back = NULL;
	return que;
}
void push(quqech* que, int index) {
	que_node* newnode = new que_node;
	newnode->numb = index;
	newnode->next = NULL;
	if (que->back != NULL) {
		que->back->next = newnode;
		que->back = newnode;
	}
	else
		if (que->front == NULL)
			que->front = newnode;
		else {
			que->back = newnode;
			que->front->next = newnode;
		}
	que->size++;
}
void pop(quqech* que) {
	if (que->size){
		que_node* temp = que->front;
		que->front = que->front->next;
		que->size--;
		delete(temp);
	}
}

void Bfg9000_matrix(int** a, int num, int* versh, int size) {
	queue <int> que;
	versh[num] = 1;
	que.push(num);
	while (!que.empty()) {
		num = que.front();
		cout << num << " -> ";
		que.pop();
		for (int i = 0; i < size; i++) {
			if (a[num][i] == 1 && versh[i] != 1) {
				que.push(i);
				versh[i] = 1;
			}
		}
	}
}

void Bfg9000_spisok(graf* grafon, int size, int* versh, int num ){
	queue <int> q;
	versh[num] = 1;
	q.push(num);
	node* buf;
	while(!q.empty()) {
		num = q.front();
		buf = grafon->nodes[num];
		q.pop();
		cout <<  num << " -> ";
		while (buf != NULL) {
			if (versh[buf->numb] == 0) {
				q.push(buf->numb);
				versh[buf->numb] = 1;
			}
			buf = buf->next;
		}
	}
}

void fuck_you_leatherman(int** a, int num, int* versh, int size) {
	quqech* que = create_que();
	versh[num] = 1;
	push(que, num);
	while (que->size) {
		num = que->front->numb;
		cout << num << " -> ";
		pop(que);
		for (int i = 0; i < size; i++) {
			if (a[num][i] == 1 && versh[i] != 1) {
				push(que, i);
				versh[i] = 1;
			}
		}
	}
}

void leather_club_is_two_blocks_down(int** a, int num, int* versh, int size) {
	int* gym_lockers;
	int last_boy_next_door = 0;
	gym_lockers = (int*)malloc(sizeof(int) * size);
	versh[num] = 1;
	gym_lockers[0] = num;
	while (last_boy_next_door+1) {
		num = gym_lockers[0];
		cout << num << " -> ";
		gym_lockers = &gym_lockers[1];
		last_boy_next_door--;
		for (int i = 0; i < size; i++) {
			if (a[num][i] == 1 && versh[i] != 1) {
				last_boy_next_door++;
				gym_lockers[last_boy_next_door] = i;
				versh[i] = 1;
			}
		}
	}
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

	cout << "   Введите размерность матрицы: "<< " ";
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

	for(int row = 0;row < size;row++){
		for(int col = 0; col < size;col++){
			cout << arr[row][col] << " " ;
		}
		cout << endl << "   ";
	}

	cout << endl;

	auto versh = new int[size];
	for (int i = 0; i < size; i++)
		versh[i] = 0;
	cout << "   Введите номер вершины, с которой хотите начать обход: ";
	int num;
	cin >> num;
	cout << endl << "   ";

	clock_t start, end;
	start = clock();
	Bfg9000_matrix(arr, num, versh, size);
	end = clock();
	cout << endl << endl << "   " << "Время выполнения с очередью queue " << (double)difftime(end, start) / CLOCKS_PER_SEC << endl << endl << "   ";

	system("pause");

	cout << endl << endl << "-----------------------------------------------------------" << endl;
	cout << "   Обход в глубину списков смежности" << endl;
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

	for (int i = 0; i < size; i++)
		versh[i] = 0;

	cout << endl << "   ";
	Bfg9000_spisok(grafon, size, versh, num);

	cout << endl << endl << "   ";
	system("pause");

	cout << endl << endl << "-----------------------------------------------------------" << endl;
	cout << "   Обход в глубину c очередью составленной списками" << endl;

	for (int i = 0; i < size; i++)
		versh[i] = 0;

	cout << endl << "   ";
	start = clock();
	fuck_you_leatherman(arr, num, versh, size);
	end = clock();
	cout << endl << endl << "   Время выполнения с очередью списком " << (double)difftime(end, start) / CLOCKS_PER_SEC << endl << endl << "   ";

	system("pause");

	cout << endl << endl << "-----------------------------------------------------------" << endl;
	cout << "   Обход в глубину c очередью составленной массивом" << endl;

	for (int i = 0; i < size; i++)
		versh[i] = 0;

	cout << endl << "   ";
	start = clock();
	leather_club_is_two_blocks_down(arr, num, versh, size);
	end = clock();
	cout << endl << endl << "   Время выполнения с очередью списком " << (double)difftime(end, start) / CLOCKS_PER_SEC << endl << endl << "   ";

	system("pause");
}