using namespace std;
#include "bst.hpp"
#include <iostream>
#include <stdlib.h>



bst::bst() { // empty constructor
	root = NULL;
}

bst::bst(string f, string l, int n, string j) { // constructor that forms the root
	root = new bstNode(f,l, n, j);
}

bool bst::insert(string f, string l, int n, string j) {
	/* Inserts a student name into the BST alphabetically based on last name and then first name.
	 */
	bstNode *current = root;
	bstNode *nodeToGoTo = root;
	while (nodeToGoTo != NULL) {
		current = nodeToGoTo;
		if (current->s->last == l) {
			if (current->s->first > f) {
				nodeToGoTo = current->left;
			} else {
				nodeToGoTo = current->right;
			}
		} else if (current->s->last > l) {
			nodeToGoTo = current->left;
		} else {
			nodeToGoTo = current->right;
		}
	}
	bstNode *newNode = new bstNode(f, l, n, j);
	if (current == NULL) {
		root = newNode;
	} else {
		if (current->s->last == l) {
			if (current->s->first > f) {
				current->left = newNode;
			} else {
				current->right = newNode;
			}
		} else if (current->s->last > l) {
			current->left = newNode;
		} else {
			current->right = newNode;
		}
		newNode->parent = current;
		setHeight(current);
	}
	return true;
}

bstNode* bst::find(string l,string f) {
	/* Finds whether a student with the last name l and first
	name f is in the tree is in the tree, and, if it is, returns the node holding that
	student.
	*/
	bstNode *current = root;
	while (current != NULL) {
		if (current->s->last == l) {
			if (current->s->first > f) {
				current = current->left;
			} else if (current->s->first < f) {
				current = current->right;
			} else {
				break;
			}
		} else if (current->s->last > l) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return current;
}

void bst::printTreeIO(bstNode *n) {
	/*recursive function that prints out the data in the tree
	in order
	*/
	if (n != NULL) {
		printTreeIO(n->left);
		n->printNode();
		printTreeIO(n->right);
	}
}

void bst::printTreePre(bstNode *n) {
	/*a recursive function that prints out the data in the
	tree in pre-order
	*/
	if (n != NULL) {
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void bst::printTreePost(bstNode *n) {
	/*a recursive function that prints out the data in
	the tree in post-order
	*/
	if (n != NULL) {
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}

bstNode* bst::remove(string l, string f) {
	/*this method removes a node from the tree, and
	returns that node. There are 3 cases when you remove a node: either the node being
	removed has no children (left or right), in which case this method calls the method
	removeNoKids, the node you are removing has only one child, in which case the method
	calls removeOneKid (with a Boolean flag set to true if there is a left child, and
	false if there is a right child), or the node being removed has both a left and a
	right child, in which you replace the node being removed with the appropriate
	replacement child, and then remove the node used as a replacement by calling either
	removeNoKids or removeOneKid, depending on which is appropriate.
	NOTE: I used the rightmost of the left child as a replacement. To get my output, you
	must do the same.
	*/
	bstNode *nodeRemoved = find(l,f);
	if (nodeRemoved->left == NULL && nodeRemoved->right == NULL) {
		setHeight(removeNoKids(nodeRemoved));
	} else if (nodeRemoved->left != NULL && nodeRemoved->right == NULL) {
		setHeight(removeOneKid(nodeRemoved, true));
	} else if (nodeRemoved->left == NULL && nodeRemoved->right != NULL) {
		setHeight(removeOneKid(nodeRemoved, false));
	} else {
		bstNode *replacement = nodeRemoved;
		replacement = replacement->left;
		while(replacement->right != NULL) {
			replacement = replacement->right;
		}
		nodeRemoved->s = replacement->s;
		if (replacement->left == NULL && replacement->right == NULL) {
			setHeight(removeNoKids(replacement));
		} else if (replacement->right == NULL) {
			setHeight(removeOneKid(nodeRemoved, true));
		} else {
			setHeight(removeOneKid(nodeRemoved, false));
		}
	}
	return nodeRemoved;
}

bstNode* bst::removeNoKids(bstNode *tmp) {
	/*for removing a node with no children*/
	bstNode *parent = tmp->parent;
	if (tmp == parent->left) {
		parent->left = NULL;
	} else {
		parent->right = NULL;
	}
	delete tmp;
	return parent;
}

bstNode* bst::removeOneKid(bstNode *tmp, bool leftFlag) {
	/*or removing a node with one
	child, with the leftFlag indicating whether the node’s child is either the left child
	or the right child.
	*/
	bstNode *newChild;
	if (leftFlag) {
		newChild = tmp->left;
	} else {
		newChild = tmp->right;
	}
	bstNode *parent = tmp->parent;
	if (tmp == parent->left) {
		parent->left = newChild;
	} else {
		parent->right = newChild;
	}
	newChild->parent = parent;
	delete tmp;
	return parent;
}

void bst::setHeight(bstNode *n)  {
	/*This method sets the heights of the nodes in a tree.
	Once a node is inserted, only the node’s ancestors can have their height changed.
	Thus you should set the height of the node being inserted (to 1) and then adjust the
	heights of the node’s parent, grandparent, etc. up until either the height of the
	node doesn’t change or you hit the root.
	*/
	bool done = false;
	while(!done) {
		int greater;
		if (n->right == NULL && n->left == NULL) {
			greater = 0;
		}
		else if(n->right == NULL) {
			greater = n->left->height;
		} else if(n->left == NULL) {
			greater = n->right->height;
		} else {
			if (n->left->height > n->right->height) {
				greater = n->left->height;
			} else {
				greater = n->right->height;
			}
		}
		n->height = greater + 1;
		if (n == root) {
			done = true;
			break;
		}
		n = n->parent;
	}
}

void bst::clearTree() { //clears out an old tree
	//This calls the recursive clearTree with the root node
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	} else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void bst::clearTree(bstNode *tmp) {
	if (tmp == NULL) {
		return;
	} else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}

void bst::printTreeIO() { // Just the start – you must write the recursive version
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}
void bst::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}
void bst::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}
