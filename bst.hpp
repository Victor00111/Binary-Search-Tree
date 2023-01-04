#ifndef bst_HPP_
#define bst_HPP_

#include "bstNode.hpp"
using namespace std;

class bst {
	bstNode *root;
public:
	bst();
	bst(string f, string l, int n, string j);
	bool insert(string f, string l, int n, string j);
	bstNode *find(string l, string f);
	void printTreeIO();
	void printTreeIO(bstNode *n);
	void printTreePre();
	void printTreePre(bstNode *n);
	void printTreePost();
	void printTreePost(bstNode *n);
	void clearTree();
	void clearTree(bstNode *tmp);
	bstNode *removeNoKids(bstNode *tmp);
	bstNode *removeOneKid(bstNode *tmp, bool leftFlag);
	bstNode *remove(string f, string l);
	void setHeight(bstNode *n);
};

#endif /* BST_HPP_ */
