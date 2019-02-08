#include <iostream>
using namespace std;

namespace k19lesson2 {
struct Node {
	int dat;
	Node *next;
};

typedef Node Listn;
typedef Node* Listp;

//Listn, *Listp;

//typedef double real;
//	real x = 0.1;
//	cout<<x*x*x<<endl;

Listp create_list();
Listp add_item_to_list(Listp, int);
void print_list(Listp);
void delete_list(Listp);

void pointers_demo() {
	int i = 5;
	int* ptr = &i;
	cout << *ptr << endl;
	cout << ptr << endl;
	*ptr = 6;
	cout << *ptr << endl;
	cout << ptr << endl;
	int j = 7;
	ptr = &j;
	cout << *ptr << endl;
	cout << ptr << endl;
	ptr = nullptr;
	//cout<<*ptr<<endl;
	cout << ptr << endl;
	ptr = new int(12);
	cout << *ptr << endl;
	cout << ptr << endl;
	*ptr = 15;
	cout << *ptr << endl;
	cout << ptr << endl;
}

void demo_struct_pointer() {
	Node some_node;
	some_node.dat = 5;
	some_node.next = nullptr;
	cout << some_node.dat << endl;
	Node* some_node_ptr = new Node;
	some_node_ptr->dat = 6;
	(*some_node_ptr).dat = 7;
	some_node_ptr->next = nullptr;
	cout << some_node_ptr->dat << endl;
}

void demo_delete() {
	Node* some_node_ptr = new Node;
	some_node_ptr->dat = 6;
	cout << some_node_ptr->dat << endl;
	cout << some_node_ptr << endl;
	delete some_node_ptr;
	cout << some_node_ptr->dat << endl;
	cout << some_node_ptr << endl;
}

int main_2() {

	Node* p;
	//p = create_list(1, 2, 3); //побудова списку
	p = create_list();

	print_list(p);
//
//	p->next->dat = 5;
//
//	print_list(p);           //друкування елементів
//	delete_list(p);            //знищення списку

	return 0;
}

//version 1

Listp create_list() {
	Listp real_start, list_start, current_node;

	int d;
	real_start = list_start = new Listn;
	while (cin >> d) {
		current_node = new Listn;
		list_start->dat = d;
		list_start->next = current_node;
		list_start = current_node;
	}
	list_start->next = NULL;
	return real_start;
}

//побудова списку з 3 елементів

// list_start{1}->node{2}->node{3}->nullptr

Listp create_list(int d1, int d2, int d3) {
	Listp list_start, current_node;

	list_start = new Listn;
	list_start->dat = d3;
	list_start->next = nullptr;

	current_node = new Listn;
	current_node->dat = d2;
	current_node->next = list_start;
	list_start = current_node;

	current_node = new Listn;
	current_node->dat = d1;
	current_node->next = list_start;
	list_start = current_node;

	return list_start;
}

//друкування 3-елементного списку
void print_list(Listp p) {
	cout << p->dat << ' ';
	p = p->next;
	cout << p->dat << ' ';
	p = p->next;
	cout << p->dat << endl;
}

//знищення 3-елементного списку
void delete_list(Listp p) {
	Listp t;
	t = p->next;
	delete p;
	p = t;
	t = p->next;
	delete p;
	p = t;
	delete p;
}

}
