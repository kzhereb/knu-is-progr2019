/*
 * treeorder-k19lesson12.cpp
 *
 *  Created on: Apr 12, 2019
 *      Author: KZ
 */

#include <iostream>
#include <random>

#include <ctime>
using std::cout;
using std::endl;

const float PROBABILITY_LEFT = 0.5;
const float PROBABILITY_HERE = 0.5;

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val, TreeNode* _left=nullptr,TreeNode* _right=nullptr) {
		value = val;
		left = _left;
		right = _right;
	}
};

struct Tree {
	TreeNode * root=nullptr;
};

float generate_real() {
	static std::random_device rd; //Will be used to obtain a seed for the random number engine
	static std::seed_seq seed { rd(), (unsigned) time(nullptr) }; // works even if rd() is deterministic
	static std::mt19937 gen(seed); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	return dis(gen);
}
int generate_int(int low, int high) {
	static std::random_device rd; //Will be used to obtain a seed for the random number engine
	static std::seed_seq seed { rd(), (unsigned) time(nullptr) }; // works even if rd() is deterministic
	static std::mt19937 gen(seed); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(low, high);
	return dis(gen);
}


float __generate_real_cstyle() {

	return (float) rand() / RAND_MAX;
}

void insert_into_tree_random(TreeNode* node, int value) {
	if (node->left && node->right) {
		float rnd = generate_real();
		if (rnd < PROBABILITY_LEFT) {
			// insert into left subtree
			insert_into_tree_random(node->left, value);
		} else {
			insert_into_tree_random(node->right, value);
		}
		return;
	}

	if (node->left) {
		float rnd = generate_real();
		if (rnd < PROBABILITY_HERE) {
			TreeNode* new_node = new TreeNode(value);
			node->right = new_node;
		} else {
			insert_into_tree_random(node->left, value);
		}
		return;
	}

	if (node->right) {
		float rnd = generate_real();
		if (rnd < PROBABILITY_HERE) {
			TreeNode* new_node = new TreeNode(value);
			node->left = new_node;
		} else {
			insert_into_tree_random(node->right, value);
		}
		return;
	}

	//Case 4: no children here
	TreeNode* new_node = new TreeNode(value);
	float rnd = generate_real();
	if (rnd < PROBABILITY_LEFT) {
		// insert into left subtree
		node->left = new_node;
	} else {
		node->right = new_node;
	}
	return;

}
void insert_into_tree_random(Tree& tree, int value) {
	if (tree.root) {
		insert_into_tree_random(tree.root, value);
	} else {
		TreeNode* new_node = new TreeNode(value);
		tree.root = new_node;
	}

}

void demo_random() {

	for (int i = 0; i < 10; i++) {
		cout << generate_real() << endl;
	}
	cout << "C-style\n";
	for (int i = 0; i < 10; i++) {
		cout << __generate_real_cstyle() << endl;
	}
}

void print_tree_node(TreeNode* node) {
	if (!node) {
		cout<<".";
		return;
	}
	cout<<node->value<<"(";
	print_tree_node(node->left);
	cout<<", ";
	print_tree_node(node->right);
	cout<<")";

}

void print_tree(const Tree& tree) {
	print_tree_node(tree.root);
}

void print_tree_node_preorder(TreeNode* node) {
	if (!node) return;
	cout<<node->value<<" ";
	print_tree_node_preorder(node->left);
	print_tree_node_preorder(node->right);
}

void print_tree_node_postorder(TreeNode* node) {
	if (!node) return;

	print_tree_node_postorder(node->left);
	print_tree_node_postorder(node->right);
	cout<<node->value<<" ";
}

int main() {
	srand(time(nullptr));

	Tree tree;
	for (int i=0;i<10;i++) {
		insert_into_tree_random(tree,generate_int(0,100));
	}
	print_tree(tree);
	cout<<endl;
	print_tree_node_preorder(tree.root);
	cout<<endl;
	print_tree_node_postorder(tree.root);
	cout<<endl;

	return 0;
}

