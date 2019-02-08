#include <iostream>
using std::cout;
using std::endl;
using std::cin;

struct Node {
	int value;
	Node *next;
};

typedef Node Listn;
typedef Node* Listp;

Listp add_elements_in_sorted_order() {
	int in;
	Listp root = new Listn;

	root->value = 0;
	root->next = new Listn;
	(root->next)->value = 1000;
	(root->next)->next = nullptr;
	cout<<"Enter numbers, 0 or 1000 to stop"<<endl;
	cin >> in;
	while (in > 0 && in < 1000) {
		Listp t, p;
		for (p = root; (p->next)->value < in; p = p->next)
			;
		t = p->next;
		p->next = new Listn;
		(p->next)->value = in;
		(p->next)->next = t;
		cin >> in;
	}
	return root;
}
;

void print_list(Listp top) {

	Listp p;

	while (p) {
		cout << p->value << ' ';
		p = p->next;
	}
	cout << endl;

}

int main() {
	Listp lst = add_elements_in_sorted_order();
	print_list(lst);
	return 0;
}

