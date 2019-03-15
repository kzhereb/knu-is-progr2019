#include <iostream>

#include <cassert>

using std::cout;
using std::endl;

//Відновлення розрідженої матриці по її
//послідовно-зв`язаному індексному зберіганню
const int MAX_ROWS = 10, MAX_COLUMNS = 40;
typedef struct Node {
	int col, dat;
	Node *next;
} Listn, *Listp;

void add_to_list(Listp& list, int col, int dat) {
	Listp new_node = new Node;
	new_node->col = col;
	new_node->dat = dat;
	new_node->next = nullptr;

	if (list) {
		Listp cur = list;
		if (cur->col>col) {
			new_node->next = cur;
			list = new_node;
			return;
		} else if (cur->col == col) {
			cur->dat = dat;
			return;
		}
		while (cur->next) {
			if (cur->next->col > col) {
				new_node->next = cur->next;
				cur->next = new_node;
				return;
			} else if (cur->next->col == col) {
				cur->next->dat = dat;
				return;
			}
			cur=cur->next;
		}
		cur->next = new_node;
	} else {
		list = new_node;
	}
}

struct SparseMatrix {
	Listp rows[MAX_ROWS];
	int row_count;
	int column_count;
	SparseMatrix(int n_rows, int n_cols) {
		assert(n_rows<=MAX_ROWS);
		assert(n_cols<=MAX_COLUMNS);
		for (int i=0;i<n_rows;i++) {
			rows[i] = nullptr;
		}
		row_count = n_rows;
		column_count = n_cols;
	}
};

void add_element(SparseMatrix& matrix, int row, int col, int value) {
	assert(row<matrix.row_count);
	assert(col<matrix.column_count);

	Listp& row_list = matrix.rows[row];
	add_to_list(row_list,col, value);

}

void print_matrix(SparseMatrix const & matrix ) {
	for (int i=0; i<matrix.row_count;i++) {
		Listp cur = matrix.rows[i];
		for (int j=0; j<matrix.column_count; j++) {
			if (!cur || cur->col>j) {
				cout<<"0 ";
				continue;
			}
			if(cur->col == j) {
				cout<<cur->dat<<" ";
				cur=cur->next;
			}
		}
		cout<<endl;
	}
}

void IndMtr(SparseMatrix const& matrix, int result[][MAX_COLUMNS]) {
	Listp p;
	int i, j;
	for (i = 0; i < matrix.row_count; i++)
		for (j = 0; j < matrix.column_count; j++)
			result[i][j] = 0;
	for (i = 0; i < matrix.row_count; i++) {
		p = matrix.rows[i];
		while (p) {
			result[i][p->col] = p->dat;
			p = p->next;
		}
	}
}

void print_array_matrix(int result[][MAX_COLUMNS], int row_count, int column_count) {
	for (int i=0; i<row_count;i++) {
		for (int j=0; j<column_count; j++) {
			cout<<result[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main() {
	//cout << "Nothing works yet" << endl;
	SparseMatrix matrix(5,7);
	add_element(matrix,0,0,10);
	add_element(matrix,1,3, 12);
	add_element(matrix,1,0, 45);
	add_element(matrix,4,6,-23);
	add_element(matrix,0,5,14);

	print_matrix(matrix);
	cout<<"Change element on same index"<<endl;
	add_element(matrix,0,5,42);
	print_matrix(matrix);
	cout<<"Regular matrix"<<endl;
	int arr_matrix[MAX_ROWS][MAX_COLUMNS];
	IndMtr(matrix, arr_matrix);
	print_array_matrix(arr_matrix,5,7);

	return 0;
}

