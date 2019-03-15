#include <iostream>
using std::cout;
using std::endl;


struct Node {
	int row, col;
	int value;
	Node* next;
	Node(int _row, int _col, int _val) {
		row = _row;
		col = _col;
		value = _val;
		next = nullptr;
	}
};

struct SparseMatrix {
	Node* start;
	int row_count;
	int col_count;
	SparseMatrix(int rows, int cols) {
		row_count = rows;
		col_count = cols;
		start = nullptr;
	}
};

void add_element(SparseMatrix& matrix, int row, int col, int value) {
	Node * current = matrix.start;
	Node* new_node = new Node(row, col, value);
	if (!current) {
		matrix.start = new_node;
		return;
	}
	while(current->next) {
		if ( (row < current->next->row) ||
				(row == current->next->row &&
				col < current->next->col ) ) {
			if (value== 0) { return; }
			new_node->next = current->next;
			current->next = new_node;
			return;
		} else if (row == current->next->row &&
				col == current->next->col) {
			if (value == 0) {
				Node* tmp = current->next;
				current->next = current->next->next;
				delete tmp;
				return;
			} else {
				current->next->value = value;
				return;
			}
		}
		current = current->next;
	}
	current->next = new_node;
}

void print_matrix_as_list(SparseMatrix const& matrix) {
	Node* current = matrix.start;
	while(current) {
		cout<<"("<<current->row<<","<<current->col<<"):"<<current->value<<endl;
		current=current->next;
	}
}



int main() {
	SparseMatrix matrix(5,7);
	add_element(matrix, 0, 0, 12);
	add_element(matrix, 1, 2, 23);
	add_element(matrix, 2, 1, 34);
	add_element(matrix, 4, 5, 45);
	add_element(matrix, 0, 1, 56);
	add_element(matrix, 0, 2, 0);

	print_matrix_as_list(matrix);
	cout<<"Change value"<<endl;
	add_element(matrix, 2, 1, 43);
	add_element(matrix, 1, 2, 0);
	print_matrix_as_list(matrix);
	return 0;
}



