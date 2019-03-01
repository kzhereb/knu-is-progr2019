#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct Node {
	int dat;
	Node *next;
} Listn, *Listp;

Listp pocket(Listp &, int);
Listp pocket2(Listp &, int);
Listp lform(int);
void lprint(Listp);

int main() {
	Listp pbeg = lform(10); //побудова списку з 100 елементів
	cout << "List before sort:" << endl;
	lprint(pbeg); //виведення списку
	pocket2(pbeg, 5);
	cout << "List after sort:" << endl;
	lprint(pbeg); //виведення списку

	return 0;
}
//-------------------
//розподільне сортування зв`язного списку
Listp pocket(Listp& q, int t) {
	Listp A[10], B[10], r;
	int k, m;
	for (m = 1; t--; m *= 10) {
		for (k = 0; k < 10; k++) //розподіл по кишеням
			A[k] = B[k] = nullptr;
		for (; q; q = q->next) {
			k = (q->dat / m) % 10; // digit of q->dat
			if (!A[k])
				A[k] = q;
			else
				(B[k]->next) = q;
			B[k] = q;
		}
		for (k = 0; !A[k]; k++)
			; //складання непорожніх кишень
		q = A[k];
		r = B[k];
		for (k++; k < 10; k++)
			if (A[k]) {
				r->next = A[k];
				r = B[k];
			}
		r->next = NULL;
	}
	return q;
}

Listp pocket2(Listp& q, int t) {
	Listp pocket_start[10], pocket_end[10], r;
	int k, m;
	for (m = 1; t--; m *= 10) {
		//cout<<m<<", t="<<t<<endl;
		for (k = 0; k < 10; k++) //розподіл по кишеням
			pocket_start[k] = pocket_end[k] = nullptr;
		while(q) {
			k = (q->dat / m) % 10; // digit of q->dat
			//cout<<q->dat<<" ->"<<k<<endl;

			if (!pocket_start[k])
				pocket_start[k] = q;
			else
				pocket_end[k]->next = q;
			pocket_end[k]=q;
			q=q->next;
			pocket_end[k]->next = nullptr;
		}
		Listp last = nullptr;
		for (k=0;k<10;k++) {
			if (!pocket_start[k]) continue;
			if (!last) {
				q = pocket_start[k];
			} else {
				last->next = pocket_start[k];
			}
			r = pocket_start[k];
			while(r) {
				if (r->next == nullptr) {
					last = r;
				}
				r=r->next;
			}

		}
	}
	return q;
}
//-------------------
//побудова списку з N псевдовипадкових чисел
Listp lform(int n) {
	Listp p, t;
	int seed = 16;
	srand(seed);
	t = NULL;
	for (int i = 0; i < n; i++) {
		p = new Node;
		p->dat = rand();
		p->next = t;
		t = p;
	}
	return p;
}
//-------------------
//виведення списку
void lprint(Listp p) {
	while (p) {
		cout << p->dat << ' ';
		p = p->next;
	}
	cout << endl;
}
