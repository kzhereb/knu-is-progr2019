#include <iostream>
using namespace std;

namespace k18lesson6 {
const int STACK_SIZE = 100;
struct mem {
	int ns, xs, ys;
};
//int current_index = STACK_SIZE;

struct stack_ackermann {
	mem st[STACK_SIZE];
	int current_index;
	stack_ackermann() {
		current_index = STACK_SIZE;
	}
};

int acc(int, int, int);
void push(stack_ackermann &, int, int, int);
void peek(stack_ackermann const &, int&, int&, int&);
void pop(stack_ackermann &, int&, int&, int&);
int accrec(int, int, int);
int smacc(int, int);

int main_k18lesson6() {
	int n, x, y;

	//cin >> n >> x >> y;
	//cout << endl;
	for (n = 0; n < 6; n++) {
		for (x = 0; x < 5; x++) {
			for (y = 0; y < 5; y++) {
				cout << "Function Ackermann n="<<n<<" x="<<x<<" y="<<y<< endl;
				//cout << "Function value (recursive) = " << accrec(n, x, y)
				//		<< endl;
				try {
					cout << "Function value (stack)     = " << acc(n, x, y) << endl;
				}
				catch (out_of_range& e) {
					cout<<e.what()<<endl;
				}

			}
		}
	}

	//system("pause");
	return 0;
}
//--------------------------------
//рекурсивна функція Аккермана
int accrec(int n, int x, int y) {
	return (n && y ? accrec(n - 1, accrec(n, x, y - 1), x) : smacc(n, x));
}

bool stack_empty(stack_ackermann const & stack) {
	return stack.current_index >= STACK_SIZE;
}

//--------------------------------
//нерекурсивна функція Аккермана
int acc(int ni, int xi, int yi) {
	int t, n, x, y;
	stack_ackermann stack;
	push(stack, ni, xi, yi);
	do {

		peek(stack, n, x, y);
		if (n && y)
			push(stack, n, x, y - 1);
		else {
			t = smacc(n, x);
			++stack.current_index;
			if (!stack_empty(stack)) {
				pop(stack, n, x, y);
				push(stack, n - 1, t, x);
			}
		}
	} while (!stack_empty(stack));
	return t;
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

//--------------------------------
//додавання в стек st нової трійки
void push(stack_ackermann & stack, int ni, int xi, int yi) {
	if (stack.current_index--) {
		stack.st[stack.current_index].ns = ni;
		stack.st[stack.current_index].xs = xi;
		stack.st[stack.current_index].ys = yi;
		//cout<<"added values n="<<ni<<", x="<<xi<<", y="<<yi<<endl;
	} else {
		throw out_of_range("Stack full");
	}
}
//--------------------------------
//читання з стека st трійки
void peek(stack_ackermann const & stack, int& n, int& x, int& y) {
	n = stack.st[stack.current_index].ns;
	x = stack.st[stack.current_index].xs;
	y = stack.st[stack.current_index].ys;
	//cout<<"used values n="<<n<<", x="<<x<<", y="<<y<<endl;
}

void pop(stack_ackermann & stack, int& n, int& x, int& y) {
	peek(stack, n, x, y);
	stack.current_index++;
}

}
