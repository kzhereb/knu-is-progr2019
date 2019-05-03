#include <iostream>
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

void print_inorder(const TreeNode * root) {
	if (!root) {
		//cout<<"Empty tree"<<endl;
		return;
	}
	print_inorder(root->left);
	cout<<root->value<<" ";
	print_inorder(root->right);
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
	return 0;
}
