#include <iostream>
using namespace std;

typedef struct Node {
	int dat;
	Node *next;
} Listn, *Listp;

struct List {
	Node* first;
	Node* last;
	List() {
		first=last=nullptr;
	}
};

struct PseudoHashList {
	static const int MAX_BUCKETS = 1000;
	List buckets[MAX_BUCKETS];
};

void index(Listp x[100]);
void lprint(Listp);


void add_item_to_list(List& list, int item) {
	Node* new_node = new Node;
	new_node->dat = item;
	new_node->next = nullptr;

	if (list.last) {
		list.last->next = new_node;
		list.last = new_node;
	} else {
		list.first = list.last = new_node;
	}

}

int pseudo_hash(int number) {
	return number % PseudoHashList::MAX_BUCKETS;
}

void add_item(PseudoHashList & list, int item) {
	int hash = pseudo_hash(item);
	add_item_to_list(list.buckets[hash], item);
}

void print_list(List const & list) {
	Node* curr_node = list.first;
	while(curr_node) {
		cout<<curr_node->dat<<" ";
		curr_node = curr_node->next;
	}
}

bool is_empty_list(List const & list) {
	return list.first == nullptr;
}

void print_pseudo_hash_list(PseudoHashList const & list) {
	for(int i=0; i<PseudoHashList::MAX_BUCKETS;i++ ){
		List const & curr_list = list.buckets[i];
		if (!is_empty_list(curr_list)) {
			cout<<i<<": ";
			print_list(curr_list);
			cout<<endl;
		}
	}
}

void input_into_hash(PseudoHashList & list) {
	cout << "Enter list (0 to end) : " << endl;
	while(true) {
		int curr_val;
		cin>> curr_val;
		if (curr_val == 0) {break;}
		add_item(list, curr_val);
	}
}

Node* find_in_list(List const& list, int value) {
	Node* result = list.first;
	while (result) {
		if (result->dat == value) { return result;}
		result= result->next;
	}
	return result;
}

bool contains(PseudoHashList const & list, int value) {
	int hash = pseudo_hash(value);
	if (find_in_list(list.buckets[hash],value)) {
		return true;
	} else {
		return false;
	}
}

int main() {

	PseudoHashList list;
	input_into_hash(list);
	print_pseudo_hash_list(list);

	int find_val;
	cout<<"Enter a value for search:";
	cin>>find_val;
	if (contains(list,find_val)) {
		cout<<"Value found in list"<<endl;
	} else {
		cout<<"Value not found"<<endl;
	}

	return 0;



	Listp xx[100];
	index(xx);
	cout << "Rezult list : " << endl;
	for (int i = 0; i < 100; i++)
		if (xx[i]) {
			cout << i << " : ";
			lprint(xx[i]);
			cout << endl;
		}
	//system("pause");
	return 0;
}
//-------------------------------------------------------
//формування індексного зберігання
void index(Listp x[100]) {
	Listp t;
	int inp, i;
	for (i = 0; i < 100; i++)
		x[i] = nullptr;  //порожня структура
	//побудова сукупності циклічних списків з покажчиками в x[i]
	cout << "List : " << endl;
	cin >> inp;
	while (inp) {
		if (x[i = inp % 100]) {
			t = new Node;
			t->dat = inp;
			t->next = x[i]->next;
			x[i]->next = t;
			x[i] = t;
		} else {
			x[i] = new Node;
			x[i]->dat = inp;
			x[i]->next = x[i];
		}
		cin >> inp;
	}
	cout << endl;
	//перетворення циклічних списків у звичайні
	for (i = 0; i < 100; i++)
		if (t = x[i]) {
			x[i] = t->next;
			t->next = NULL;
		}
}
//-------------------------------------------------------
//виведення списку
void lprint(Listp p) {
	while (p) {
		cout << p->dat << ' ';
		p = p->next;
	}
}
