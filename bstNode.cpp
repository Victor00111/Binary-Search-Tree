using namespace std;
#include "bstNode.hpp"
#include <iostream>
#include <stdlib.h>

bstNode::bstNode() {
	parent = NULL;
	left = NULL;
	right = NULL;
	height = 0;
	s = NULL;
}

bstNode::bstNode(string firstName, string lastName, int favNum, string joke) {
	parent = NULL;
	left = NULL;
	right = NULL;
	height = 1;
	s = new Student(firstName, lastName, favNum, joke);
}

bstNode::~bstNode() {
	cout << "Deleted Node" << endl;
}

void bstNode::printNode() {
	cout <<"Height: "<<height<<", Name: "<<s->last<<", "<<s->first<< endl;
	cout << "Joke: "<< s->joke << endl << endl;
	//cout << s->first << ", " << s->last << ", " << s->fav_num << ", " << s->joke << endl;
	//cout << height << endl;
}

