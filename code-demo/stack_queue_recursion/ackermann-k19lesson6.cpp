#include <iostream>
using namespace std;


struct mem {
	int ns, xs, ys;
};

struct stack_ackermann {
	static const int M = 100;
	mem st[M];
	int p = M;
};

int acc(int, int, int);
void push(stack_ackermann &, int, int, int);
void peek(stack_ackermann const &,int &, int &, int &);
void pop(stack_ackermann &,int &, int &, int &);
int accrec(int, int, int);
int smacc(int, int);

int main_k19lesson6() {
	int n, x, y;
	cout << "Function Ackermann n= x= y=" << endl;
	cin >> n >> x >> y;
	cout << endl;
	cout << "Recursive = " << accrec(n, x, y) << endl;
	cout << "Stack     = " << acc(n, x, y) << endl;
	//system("pause");
	return 0;
}
//--------------------------------
//рекурсивна функція Аккермана
int accrec(int n, int x, int y) {
	return (n && y ? accrec(n - 1, accrec(n, x, y - 1), x) : smacc(n, x));
}
//--------------------------------
//функція Аккермана при n=0|y=0
int smacc(int n, int x) {
	switch (n) {
	case 0:
		return x + 1;
	case 1:
		return x;
	case 2:
		return 0;
	case 3:
		return 1;
	default:
		return 2;
	}
}

bool stack_empty(stack_ackermann const & stack) {
	return stack.p >= stack.M;
}

//--------------------------------
//нерекурсивна функція Аккермана
int acc(int ni, int xi, int yi) {
	int t, n, x, y;
	stack_ackermann stack;
	push(stack, ni, xi, yi);
	do {
		peek(stack, n, x, y);
		if (n > 0 && y > 0)
			push(stack, n, x, y - 1);
		else {
			t = smacc(n, x);
			++stack.p;
			if (!stack_empty(stack)) {
				pop(stack, n, x, y);
				push(stack, n - 1, t, x);
			}
		}
	} while (!stack_empty(stack));
	return t;
}
//--------------------------------

//--------------------------------
//додавання в стек st нової трійки
void push(stack_ackermann & stack, int ni, int xi, int yi) {
	if (stack.p--) {
		stack.st[stack.p].ns = ni;
		stack.st[stack.p].xs = xi;
		stack.st[stack.p].ys = yi;
	} else
		cout << "Stack full" << endl;
}
//--------------------------------
//читання з стека st трійки
void peek(stack_ackermann const & stack, int & n, int & x, int & y) {
	n = stack.st[stack.p].ns;
	x = stack.st[stack.p].xs;
	y = stack.st[stack.p].ys;
}

void pop(stack_ackermann & stack, int & n, int & x, int & y) {
	peek(stack, n, x, y);
	stack.p++;
}
