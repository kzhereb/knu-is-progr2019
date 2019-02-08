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

Listp larrange(){
  int in;
  Listp t, r = new Listn;
  r->value = 0; r->next = new Listn;
  (r->next)->value = 1000; (r->next)->next = nullptr;
  cin >> in;
  while (in>0 && in<1000) {Listp p;
    for (p=r; (p->next)->value < in; p=p->next);
    t = p->next; p->next = new Listn;
    (p->next)->value = in; (p->next)->next = t;
    cin >> in;} return r;
};

void print_list(Listp top) {

	Listp p;

	while(p) {
		cout << p->value << ' ';
		p=p->next;
	}
	cout << endl;

}


int main() {
	Listp lst = larrange();
	print_list(lst);
	return 0;
}




