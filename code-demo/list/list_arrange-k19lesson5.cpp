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
		Listp current;
		for (current = root; (current->next)->value < in; current = current->next)
			;

		Listp new_node = new Listn;
		new_node->value = in;
		new_node->next = current->next;
		current->next = new_node;

		cin >> in;
	}
	return root;
}
;

void print_list(Listp top) {

	Listp p = top;

	while (p) {
		cout << p->value << ' ';
		p = p->next;
	}
	cout << endl;

}

int main_k19lesson5() {
	Listp lst = add_elements_in_sorted_order();
	print_list(lst);
	return 0;
}

