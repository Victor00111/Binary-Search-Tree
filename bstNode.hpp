#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_
using namespace std;

#include "Student.hpp"
#include <iostream>
#include <stdlib.h>

class bstNode {
	friend class bst;
	bstNode *parent;
	bstNode *left;
	bstNode *right;
	int height;
	Student *s;
public:
	bstNode();
	bstNode(string firstName, string lastName, int favNum, string joke);
	~bstNode();
	void printNode();
};

#endif /* BSTNODE_HPP_ */
