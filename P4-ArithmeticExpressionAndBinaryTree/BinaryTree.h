//
// Created by ling on 2022/10/30.
//

#ifndef P4_ARITHMETICEXPRESSIONANDBINARYTREE_BINARYTREE_H
#define P4_ARITHMETICEXPRESSIONANDBINARYTREE_BINARYTREE_H
#include <string>
using std::string;

class BinaryTree {
private:
	struct BinaryTreeNode;
	BinaryTree* root;
public:
	BinaryTree();
	void build(string &exp);
};



#endif //P4_ARITHMETICEXPRESSIONANDBINARYTREE_BINARYTREE_H
