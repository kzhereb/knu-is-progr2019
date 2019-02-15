#include <iostream>

struct stack_node {
	int m;
	int n;
	stack_node* next;
};

struct stack {
	stack_node * top;
	stack() {
		top = nullptr;
	}
};

void push(stack& stack, int m, int n) {
	stack_node * new_node = new stack_node;
	new_node->m = m;
	new_node->n = n;
	new_node->next = stack.top;

	stack.top = new_node;
}

bool is_stack_empty(stack const& stack) {
	return stack.top == nullptr;
}

bool peek(stack const& stack, int & m, int &n) {
	if (is_stack_empty(stack)) {
		return false;
	}
	m = stack.top->m;
	n = stack.top->n;
	return true;
}

bool pop(stack & stack, int & m, int &n) {
	if (peek(stack, m, n)) {
		stack_node * tmp = stack.top;
		stack.top = stack.top->next;
		delete tmp;
		return true;
	}
	return false;
}

void test_memory_leak() {
	stack stack;
	int m, n;
	while (true) {
		push(stack, 1, 2);
		pop(stack, m, n);
	}
}

int ack2_recursive(int m, int n) {
	if (m == 0 || n == 0) {
		return m + n + 1;
	} else {
		return ack2_recursive(m - 1, ack2_recursive(m, n - 1));
	}

}

int ack2_stack(int m, int n) {
	stack stack;
	int result;
	push(stack, m, n);
	do {
		peek(stack, m, n);
		if (m > 0 && n > 0) {
			push(stack, m, n - 1);
		} else {
			result = m + n + 1;
			pop(stack, m, n);
			if (!is_stack_empty(stack)) {
				pop(stack, m, n);
				push(stack, m - 1, result);
			}
		}
	} while (!is_stack_empty(stack));
	return result;
}

int main() {
	using std::cout;
	using std::endl;
	int m = 2, n = 3;
	//test_memory_leak();
	cout << "Recursive m=" << m << " n=" << n << " F=" << ack2_recursive(m, n)
			<< endl;
	cout << "Stack     m=" << m << " n=" << n << " F=" << ack2_stack(m, n)
			<< endl;
	return 0;
}

