#include <iostream>
#include <cassert>
using std::cout;
using std::endl;


struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int val, TreeNode* lef=nullptr, TreeNode* rig=nullptr) {
		value = val;
		left = lef;
		right = rig;
	}
};

bool insert(TreeNode** root, int val) {
	if (*root == nullptr) {
		*root = new TreeNode(val);
		return true;
	}
	if (val<(*root)->value) {
		return insert(&((*root)->left),val);
	} else if (val>(*root)->value) {
		return insert(&((*root)->right),val);
	}
	return false;
}

TreeNode** find_prev(TreeNode* root) {
	assert(root!=nullptr);
	assert(root->left!=nullptr);

	TreeNode** cur = &(root->left);
	while((*cur)->right) {
		*cur = (*cur)->right;
	}
	return cur;
}

void remove(TreeNode** root, int val) {
	if(*root==nullptr) {
		return;
	}
	if (val<(*root)->value) {
		remove(&((*root)->left),val);
	} else if (val>(*root)->value) {
		remove(&((*root)->right),val);
	} else {
		if ((*root)->left) {
			if ((*root)->right) { //both children
				TreeNode** prev_node = find_prev(*root);
				(*root)->value = (*prev_node)->value;
				TreeNode* tmp = (*prev_node)->left;
				delete * prev_node;
				*prev_node = tmp;
			} else { //only left child
				TreeNode* tmp = (*root)->left;
				delete *root;
				*root = tmp;
			}
		} else {
			if ((*root)->right) { //only right child
				TreeNode* tmp = (*root)->right;
				delete *root;
				*root = tmp;
			} else { //no children
				delete *root;
				*root = nullptr;
			}
		}
	}
}

void print_inorder(const TreeNode * root, bool is_top=true) {
	if (!root) {
		if (is_top) {cout<<"Empty tree"<<endl;}
		return;
	}
	print_inorder(root->left,false);
	cout<<root->value<<" ";
	print_inorder(root->right,false);
	if (is_top) {cout<<endl;}
}







int main() {
	TreeNode* root = nullptr;
	insert(&root,5);
	insert(&root,8);
	insert(&root,1);
	insert(&root,16);
	insert(&root,0);
	insert(&root,7);

	print_inorder(root);

	remove(&root,5);
	print_inorder(root);
	remove(&root,8);
	print_inorder(root);
	return 0;
}
