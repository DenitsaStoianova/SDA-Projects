// Task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BinaryTree.h"

int main(int argc, char** argv)
{
	char* fileName = argv[1];

	BinaryTree tree;
	tree.readTreeFromFile(fileName);
	std::cout << tree.isBST() << std::endl;
	std::cout << tree.isBalanced() << std::endl;
	tree.removeWrongNodes();
	tree.writeTreeToFile("resulttree.txt");

	return 0;
}
