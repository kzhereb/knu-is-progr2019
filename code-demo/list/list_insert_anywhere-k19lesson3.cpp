#include <iostream>
using namespace std;

struct Node {
	int dat;
	Node *next;
	Node *prev;
};
//-------------------------
Node *first(int);
void add(Node **, int);
void add_ref(Node *&, int);
Node *find(Node * const, int);
bool remove(Node **, Node **, int);
Node *insert(Node * const, Node **, int, int);
void lprint(Node *);
void ldel(Node *);
//-------------------------

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

	cout << "int **" << endl;
	int ** pptr = &ptr;
	cout << pptr << endl;
	cout << *pptr << endl;
	cout << **pptr << endl;

	**pptr = 23;
	cout << pptr << endl;
	cout << *pptr << endl;
	cout << **pptr << endl;

	*pptr = new int(25);
	cout << pptr << endl;
	cout << *pptr << endl;
	cout << **pptr << endl;

	int* ptr2 = new int(32);
	pptr = &ptr2;
	cout << pptr << endl;
	cout << *pptr << endl;
	cout << **pptr << endl;

}


// index points to a gap between elements
// negative index: same as 0
// big positive index: same as length
Node* find_by_index(Node* const p_begin, int index) {
	if (index<0) {
		return p_begin;
	}
	int counter = 0;
	Node* tmp = p_begin;
	while (tmp) {
		if (counter == index) {
			return tmp;
		}
		tmp = tmp->next;
		counter++;
	}
	return nullptr;
}

// [0:1]->[1:2]->...->[9:10]->nullptr
//0      1      2    9      10
//      new_node   found
Node* insert_anywhere(Node*& p_begin, Node*& p_end, int index, int value) {

	Node* found = find_by_index(p_begin, index);
	Node* new_node = new Node;
	new_node->dat = value;
	new_node->next = found;
	if (found) {
		new_node->prev = found->prev;
		if (found->prev) {
			found->prev->next = new_node;
		} else {
			p_begin = new_node;
		}
		found->prev = new_node;
	} else {
		p_end->next = new_node;
		new_node->prev = p_end;

		p_end = new_node;
	}

	return new_node;
}

int main() {
//	pointers_demo();
//	return 0;

	int nn, k, m;
	//визначаємось з кількістю елементів
	//cout << "Number = ";
	//cin >> nn;
	nn = 10;
	cout << endl;
	Node *pbeg = first(1); //формування першого елемента списку
	Node *pend = pbeg;     //список складаєтьсчя з одного елемента
	Node *p;
	//додавання елементів в кінець списку 2, 3, ..., nn
//  for (int i = 2; i <= nn; i++) add(&pend, i);
	for (int i = 2; i <= nn; i++)
		add_ref(pend, i);
	lprint(pbeg);  //виведення списку

	Node* found = find_by_index(pbeg, 3);
	cout << "found: " << found->dat << endl;

	cout << "insert anywhere end" << endl;
	insert_anywhere(pbeg, pend, 10, 3456);
	lprint(pbeg);

	cout << "insert anywhere" << endl;
	insert_anywhere(pbeg, pend, 1, 1234);
	lprint(pbeg);

	cout << "insert anywhere beginning" << endl;
	insert_anywhere(pbeg, pend, 0, 2345);
	lprint(pbeg);


	cout << "insert anywhere negative" << endl;
	insert_anywhere(pbeg, pend, -10, 4567);
	lprint(pbeg);

	//вставка елемента k після елемента m
	cout << "Insert = ";
	cin >> k;
	cout << endl;
	cout << "After = ";
	cin >> m;
	cout << endl;
	p = insert(pbeg, &pend, m, k);
	lprint(pbeg);  //виведення списку
	//вилучення елемента k
	cout << "Delete = ";
	cin >> k;
	cout << endl;
	if (!remove(&pbeg, &pend, k))
		cout << "no find " << endl;
	lprint(pbeg);  //виведення списку
	ldel(pbeg);  //знищення списку
	//system("pause");
	return 0;
}
//--------------------------------------------------------
//формування першого елемента списку
Node *first(int d) {
	Node *pv = new Node;
	pv->dat = d;
	pv->next = NULL;
	pv->prev = NULL;
	return pv;
}
//--------------------------------------------------------
//додавання елементів в кінець списку 2, 3, ..., nn
void add(Node **pend, int d) {
	Node *pv = new Node;
	pv->dat = d;
	pv->next = NULL;
	pv->prev = *pend;
	(*pend)->next = pv;
	*pend = pv;
}

//--------------------------------------------------------
//додавання елементів в кінець списку 2, 3, ..., nn
void add_ref(Node *& pend, int d) {
	Node *pv = new Node;
	pv->dat = d;
	pv->next = NULL;
	pv->prev = pend;
	pend->next = pv;
	pend = pv;
}
//--------------------------------------------------------
//пошук елемента за ключем
Node *find(Node * const pbeg, int d) {
	Node *pv = pbeg;
	while (pv) {
		if (pv->dat == d)
			break;
		pv = pv->next;
	}
	return pv;
}
//-------------------------------------------------------
//вилучення елемента
bool remove(Node **pbeg, Node **pend, int key) {
	if (Node *pkey = find(*pbeg, key)) {
		if (pkey == *pbeg) {
			*pbeg = (*pbeg)->next;
			(*pbeg)->prev = NULL;
		} else if (pkey == *pend) {
			*pend = (*pend)->prev;
			(*pend)->next = NULL;
		} else {
			(pkey->prev)->next = pkey->next;
			(pkey->next)->prev = pkey->prev;
		}
		delete pkey;
		return true;
	}
	return false;
}
//-------------------------------------------------------
//вставка елемента
Node *insert(Node * const pbeg, Node **pend, int key, int d) {
	if (Node *pkey = find(pbeg, key)) {
		Node *pv = new Node;
		pv->dat = d;
		pv->next = pkey->next; //зв`язок нового вузла з наступним
		pv->prev = pkey;  //зв`язок нового вузла з попереднім
		pkey->next = pv;  //зв`язок попереднього з новим вузлом
		//зв`язок наступного з новим вузлом
		if (pkey != *pend)
			(pv->next)->prev = pv;
		else
			*pend = pv;  //якщо вузол стає останнім, змінюємо покажчик на кінець
		return pv;
	}
	return NULL;  //місце для вставки не було знайдено
				  //можна було б реалізовувати іншу обробку
				  //наприклад, вставку в кінець списку,
				  //передбачивши можливу порожність списку
}
//-------------------------------------------------------
//виведення списку
void lprint(Node *pbeg) {
	Node *pv = pbeg;
	while (pv) {
		cout << pv->dat << ' ';
		pv = pv->next;
	}
	cout << endl;
}
//-------------------------------------------------------
//знищення списку
void ldel(Node *pbeg) {
	Node *pv;
	while (pbeg) {
		pv = pbeg;
		pbeg = pbeg->next;
		delete pv;
	}
}
