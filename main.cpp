#include<iostream>
#include "BinaryTree.h"
#include "BinaryOrdTree.h"

// Function, which icreases every node of a binary tree with a number
void increaseLeafs(BinaryTree<int> &tree, int number) {
	tree.increaseLeafsWith(number);
}

// Function, which checks if two binary trees are equal
template<class T>
bool equal(const BinaryTree<T>& t1, const BinaryTree<T>& t2) {
	if (t1.empty() && t2.empty()) {
		return true;
	}
	if ((t1.empty() && !t2.empty()) || (!t1.empty() && t2.empty())) {
		return false;
	}
	if (t1.rootTree() != t2.rootTree()) {
		return false;
	}
	return equal(t1.leftTree(), t2.leftTree()) &&
						equal(t1.rightTree(), t2.rightTree());
}

/*
// Function which find the depth of a binary tree
template<class T>
int depth(const BinaryTree<T>& tree) {
	if (tree.empty()) return 0;
	int n, m;
	n = depth(tree.leftTree());
	m = depth(tree.rightTree());
	if (n > m) return n + 1;
	return m + 1;
}
*/

// Function which finds the height of a binary tree
template<class T>
int height(const BinaryTree<T>& tree) {
	if (tree.getRoot() == NULL) {
		return 0;
	}
	if (depth(tree) == 1) {
		return 1;
	}
	return depth(tree) - 1;
}

void testTree() {
	BinaryTree<int> tree1;
	tree1.create();
	std::cout << "Is element 15 in the binary tree: " << tree1.searchForNode(15) << std::endl;
}

int main1() {
	testTree();
	return 0;
}

int main() {
	BinaryOrdTree<int> t3;
	// root
	std::cin >> t3;
	std::cout << t3;
	/*t3.AddNode(10);
	// left tree
	t3.AddNode(7);
	t3.AddNode(8);
	// t3.AddNode(6);
	// rigth tree
	t3.AddNode(12);
	t3.AddNode(15);
	t3.AddNode(20);
	//t3.AddNode(30);
	// t3.AddNode(40);
	*/
	// t3.print();
	std::cout << t3.findMinElement() << std::endl;
	// t3.deleteNode(10);
	// t3.deleteNode(40);
	// t3.print();
	std::cout << "Is the number 40 in the binary ordered tree: ";
	if (t3.searchForNode(10)) {
		std::cout << "yes" << std::endl;
	}


	else {
		std::cout << "no" << std::endl;
	}
	std::cout << "Tree depth: " << depth(t3) << std::endl;
	std::cout << "Tree depth1: " << depth1(t3.getRoot()) << std::endl;
	std::cout << "Is the tree balanced: " << (t3.isBalanced() ? "balanced" : "not balanced") << std::endl;
	return 0;
}










/*
BinaryTree<int> tree2;
std::cout << " ----------------------------- " << std::endl;
std::cout << "The program ended!" << std::endl;
tree1.print();
std::cout << depth(tree1) << std::endl;
tree2 = tree1;
std::cout << std::endl;
tree2.print();
std::cout << depth(tree2) << std::endl;
std::cout << "------------------------------" << std::endl;
tree2.leftTree().print();
tree2.rightTree().print();
std::cout << std::endl;
std::cout << "Are trees equal: " << equal(tree1, tree2) << std::endl;
std::cout << "The height of the first tree: " << height(tree1) << std::endl;
*/