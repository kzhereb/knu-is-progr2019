#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

struct Node {
	int value;
	Node * next;
	Node * prev;
};

struct List {
	Node* root;
};

Node* create_node_sequence(int count) {
	assert(count >= 0);
	Node* result = new Node;
	result->value = count;
	result->prev = nullptr;
	if (count == 0) {
		result->next = nullptr;
	} else {
		result->next = create_node_sequence(count - 1);
		result->next->prev = result;
	}
	return result;
}

List* create_list_sequence(int count) {
	List* result = new List;
	result->root = create_node_sequence(count);
	return result;
}

void print_list_node(Node* root) {
	if (root) {
		cout << root->value << " ";
		print_list_node(root->next);
	}
}

void print_list(List* lst) {
	if (lst) {
		print_list_node(lst->root);
		cout << endl;
	} else {
		cout << "Null list!!" << endl;
	}
}

void delete_list_node(Node* node) {
	if (node) {
		delete_list_node(node->next);
		delete node;
	}
}

void delete_list(List* lst) {
	if (lst) {
		delete_list_node(lst->root);
		delete lst;
	}
}

Node* find_number_in_list_node(Node* root, int number) {
	if (root) {
		if (root->value == number) {
			return root;
		}
		return find_number_in_list_node(root->next, number);
	}
	return nullptr;
}

Node* find_number_in_list(List* lst, int number) {
	if (lst) {
		return find_number_in_list_node(lst->root, number);
	}
	return nullptr;

}
//returns true if removed successfully
bool remove_node_from_list(List* lst, Node* node) {
	if (node) {
		if (node->prev) {
			node->prev->next = node->next;
		} else {
			lst->root = node->next;
		}
		if (node->next) {
			node->next->prev = node->prev;
		}
		delete node;
		return true;
	}
	return false;
}

bool add_node_after(Node* found, int value) {
	if (found) {
		Node* new_node = new Node;
		new_node->value=value;
		new_node->next = found->next;
		new_node->prev = found;

		found->next = new_node;
		return true;
	}
	return false;
}

void check_memory_leaks() {
	while (true) {
		List* lst = create_list_sequence(1e4);
		delete_list(lst);

	}
}

int main_k18lesson3() {

	List* lst = create_list_sequence(10);

	print_list(lst);

	//print_list_node(lst->root->next->next);

	Node* found_node = find_number_in_list(lst, 8);
	print_list_node(found_node);
	cout << endl;


	cout<<std::boolalpha;

	found_node->value = 888;
	print_list(lst);

	add_node_after(found_node, 12345);
	print_list(lst);

	cout<<remove_node_from_list(lst, found_node)<<endl;
	print_list(lst);

	found_node = find_number_in_list(lst, 10);
	cout<<remove_node_from_list(lst, found_node)<<endl;
	print_list(lst);

	found_node = find_number_in_list(lst, 0);
	cout<<remove_node_from_list(lst, found_node)<<endl;
	print_list(lst);

	found_node = find_number_in_list(lst, 15);
	cout<<remove_node_from_list(lst, found_node)<<endl;
	print_list(lst);

	delete_list(lst);

	//check_memory_leaks();

	return 0;
}
