#include <iostream>
using namespace std;

// top -> next1 -> next2 -> nullptr;
namespace k18lesson1 {
struct Node {
	int data;
	Node *next;
};

using List=Node;
using ListPtr=List*;

//CreateList = PascalCase
//createList = camelCase
//create_list = lower_undercase
//CREATE_LIST = MACROS

ListPtr create_list(int, int, int);
void print_list(ListPtr);
void ldel(ListPtr);

int main_k18lesson1() {
	ListPtr p;

	// top[1] -> next1[2] -> next2[3] -> nullptr;

	p = create_list(1, 2, 3); //побудова списку
	print_list(p);           //друкування елементів
	ldel(p);            //знищення списку
	//system("pause");
	return 0;
}

ListPtr create_node(ListPtr top, int data) {
	ListPtr curr = new List;
	curr->data = data;
	curr->next = top;
	return curr;
}

//побудова списку з 3 елементів
ListPtr create_list(int d1, int d2, int d3) {
	ListPtr p= create_node(nullptr, d3);

	p = create_node(p, d2);

	p = create_node(p, d1);

	return p;
}

//друкування 3-елементного списку
void print_list(ListPtr top) {

	ListPtr p;

	while(p) {
		cout << p->data << ' ';
		p=p->next;
	}
	cout << endl;

//	cout << top->data << ' ';
//	top = top->next;
//	cout << top->data << ' ';
//	top = top->next;
//	cout << top->data << endl;
}

//знищення 3-елементного списку
void ldel(ListPtr p) {
	ListPtr t;
	t = p->next;
	delete p;
	p = t;
	t = p->next;
	delete p;
	p = t;
	delete p;
}
}
