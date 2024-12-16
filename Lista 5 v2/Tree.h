#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <utility> // pair

#include "Node.h"

using namespace std;

class Tree {
public:
	Tree();
	Tree(Node* newRoot, map<string, pair<int, int>> newVariables);
	Tree(const Tree& otherTree);
	Tree(Tree&& other);

	~Tree();

	static MyResult<Tree, MyError>* enter(istringstream& inputStream);

	string toString() const;
	string vars();
	MyResult<double, MyError> comp(istringstream& inputStream);
	MyResult<void, MyError> join(istringstream& inputStream);
	int leaves();

	bool isValid() const;

	Tree operator=(const Tree& other);
	Tree operator+(const Tree& other);

	Tree operator=(Tree&& other);

private:
	Node* root;

	/*
		two ints in pair ->
		first - number of variables with string name
		second - value
	*/
	map<string, pair<int, int>> variablesNames;

	
	void appendVariables(map<string, pair<int, int>> otherVaraibles);
	void moveFrom(Tree& other);
	void clear();
};

#endif
