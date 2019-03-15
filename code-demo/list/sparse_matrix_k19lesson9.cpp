#include <iostream>

#include <cassert>
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
	Node sentinel(-1,-1,-1);
	sentinel.next = matrix.start;
	Node * current = &sentinel;
	Node* new_node = new Node(row, col, value);
	if (!matrix.start) {
		matrix.start = new_node;
		return;
	}

	while(current->next) {
		if ( (row < current->next->row) ||
				(row == current->next->row &&
				col < current->next->col ) ) {
			if (value== 0) { return; }
			new_node->next = current->next;
			if (current==&sentinel) {
				matrix.start = new_node;
			} else {
				current->next = new_node;
			}
			return;
		} else if (row == current->next->row &&
				col == current->next->col) {
			if (value == 0) {
				Node* tmp = current->next;
				current->next = current->next->next;
				if (current == &sentinel) {
					matrix.start = tmp->next;
				}
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

void plus_element(SparseMatrix& matrix, int row, int col, int value) {
	Node sentinel(-1,-1,-1);
	sentinel.next = matrix.start;
	Node * current = &sentinel;
	Node* new_node = new Node(row, col, value);
	if (!matrix.start) {
		matrix.start = new_node;
		return;
	}

	while(current->next) {
		if ( (row < current->next->row) ||
				(row == current->next->row &&
				col < current->next->col ) ) {
			if (value== 0) { return; }
			new_node->next = current->next;
			if (current==&sentinel) {
				matrix.start = new_node;
			} else {
				current->next = new_node;
			}
			return;
		} else if (row == current->next->row &&
				col == current->next->col) {
			int new_value = value + current->next->value;
			if (new_value == 0) {
				Node* tmp = current->next;
				current->next = current->next->next;
				if (current == &sentinel) {
					matrix.start = tmp->next;
				}
				delete tmp;
				return;
			} else {
				current->next->value = new_value;
				return;
			}
		}
		current = current->next;
	}
	current->next = new_node;
}

void plus_element_old(SparseMatrix& matrix, int row, int col, int value) {
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
			int new_value = value + current->next->value;
			if (new_value == 0) {
				Node* tmp = current->next;
				current->next = current->next->next;
				delete tmp;
				return;
			} else {
				current->next->value = new_value;
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

void print_as_matrix(SparseMatrix const& matrix) {
	if (matrix.row_count>10 || matrix.col_count>10) {
		cout<<"Matrix is too big, use print_matrix_as_list"<<endl;
		return;
	}
	Node* current = matrix.start;
	for(int i=0;i<matrix.row_count;i++) {
		for(int j=0;j<matrix.col_count;j++) {
			if (current == nullptr) {
				cout<<"0 ";
				continue;
			}
			if (i== current->row && j == current->col) {
				cout<<current->value<<" ";
				current=current->next;
			} else {
				cout<<"0 ";
			}

		}
		cout<<endl;
	}

}

SparseMatrix transpose(const SparseMatrix& A) {
	SparseMatrix result(A.col_count,A.row_count);
	Node* current = A.start;
	while (current) {
		add_element(result,current->col, current->row, current->value);
		current=current->next;
	}
	return result;
}


SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B) {
	assert(A.col_count == B.row_count);
	SparseMatrix result(A.row_count, B.col_count);
	Node* curA = A.start;

	while(curA) {
		int row = curA->row;
		int col = curA->col;
		Node* curB = B.start;
		while (curB) {
			if (curB->row == col) {
				plus_element(result,row, curB->col,curA->value*curB->value);
			}
			curB = curB->next;
		}
		curA = curA->next;
	}
	return result;
}

// Bad version

//SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B) {
//	assert(A.col_count == B.row_count);
//	SparseMatrix result(A.row_count, B.col_count);
//	SparseMatrix B_tr = transpose(B);
//
//	Node* curA = A.start;
//	Node* row_start = A.start;
//
//	int prev_row = -1;
//	while (curA) {
//		int row = curA->row;
//		if (row > prev_row) {
//			row_start = curA;
//			Node* curBtr = B_tr.start;
//			while(curBtr) {
//				if (curBtr->row == row) {
//					Node* rowA = row_start;
//					while (rowA && rowA->row == row) {
//
//					}
//				}
//				curB = curB->next;
//			}
//		}
//		prev_row = row;
//
//		curA = curA->next
//
//	}
//
//
//
//	return result;
//}


int main() {
//	SparseMatrix matrix(5,7);
//	add_element(matrix, 0, 0, 12);
//	add_element(matrix, 1, 2, 23);
//	add_element(matrix, 2, 1, 34);
//	add_element(matrix, 4, 5, 45);
//	add_element(matrix, 0, 1, 56);
//	add_element(matrix, 0, 2, 0);
//
//	print_matrix_as_list(matrix);
//	print_as_matrix(matrix);
//	cout<<"Change value"<<endl;
//	add_element(matrix, 2, 1, 43);
//	add_element(matrix, 1, 2, 0);
//	add_element(matrix, 0, 0, 11);
//	print_matrix_as_list(matrix);
//	print_as_matrix(matrix);
//
//	cout<<"Plus element"<<endl;
//	plus_element(matrix,0,0,3);
//	plus_element(matrix,2,1,-43);
//	print_matrix_as_list(matrix);
//
//	cout<<"transposed"<<endl;
//	SparseMatrix transposed = transpose(matrix);
//	print_as_matrix(transposed);

	SparseMatrix A(2,2);
	add_element(A,0,0,2);
	add_element(A,1,1,3);

	SparseMatrix B(2,2);
	add_element(B,0,1,5);
	add_element(B,1,0,7);

	SparseMatrix C = multiply(A,B);
	print_as_matrix(C);
	return 0;
}



