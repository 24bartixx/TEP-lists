#include "Tree.h"
#include "Node.h"
#include "HelperMethods.h"

using namespace std;

Tree::Tree() {
	root = new ValueNode(1);
}

Tree::Tree(Node* newRoot, map<string, pair<int, int>> newVariables) : root(newRoot), variablesNames(newVariables) {

}

Tree::Tree(const Tree& otherTree) {
	root = otherTree.root->clone();
	variablesNames = otherTree.variablesNames;
}

Tree::~Tree() {
	clear();
}

MyResult<Tree, MyError>* Tree::enter(istringstream& inputStream) {

	vector<MyError*> errors;
	map<string, pair<int, int>> variables;
	Node* potentialRoot = parseNode(inputStream, variables, errors);

	string str;
	if (inputStream >> str) {
		errors.push_back(new MyError(MyError::EXCESSIVE_ARGUMENTS));
	}

	return errors.empty()
		? new MyResult<Tree, MyError>(MyResult<Tree, MyError>::ok(Tree(potentialRoot, variables)))
		: new MyResult<Tree, MyError>(MyResult<Tree, MyError>::fail(errors));
}

string Tree::toString() const {
	if (root != NULL) {
		return root->toString();
	}

	return "Tree is empty!\n";
}

string Tree::vars() {

	stringstream stream;
	stream << variablesNames.size();
	string toReturn = "Variables (count " + stream.str() + "): ";

	for (map<string, pair<int, int>>::iterator iterator = variablesNames.begin(); iterator != variablesNames.end(); iterator++) {
		if (iterator != variablesNames.begin()) {
			toReturn += ", ";
		}
		toReturn += iterator->first;
	}

	return toReturn;
}

MyResult<double, MyError> Tree::comp(istringstream& stream) {
	string inputStr;
	vector<int> digits;
	while (stream >> inputStr) {
		if (isValue(inputStr)) {
			digits.push_back(convertToDigit(inputStr));
		}
	}
	if (variablesNames.size() == digits.size()) {
		vector<int>::iterator digitsIterator = digits.begin();
		for (map<string, pair<int, int>>::iterator variablesIterator = variablesNames.begin(); variablesIterator != variablesNames.end(); variablesIterator++) {
			variablesIterator->second.second = *digitsIterator;
			digitsIterator++;
		}
		return root->calculateValue(variablesNames);
	}
	else {
		return MyResult<double, MyError>::fail(new MyError(MyError::INCORRECT_NUMBER_OF_INPUTS));
	}
}

MyResult<void, MyError> Tree::join(istringstream& inputStream) {

	vector<MyError*> errors;
	map<string, pair<int, int>> variables;
	Node* potentialSubTreeRoot = parseNode(inputStream, variables, errors);

	string str;
	if (inputStream >> str) {
		errors.push_back(new MyError(MyError::EXCESSIVE_ARGUMENTS));
	}

	if (errors.empty()) {
		if (!root->join(potentialSubTreeRoot, variablesNames)) {
			clear();
			root = potentialSubTreeRoot;
			variablesNames = variables;
		}
		else {
			appendVariables(variables);
		}
	}
	else {
		return MyResult<void, MyError>::fail(errors);
	}

}

/* MODIFICATION */
int Tree::leaves() {
	return root->leaves();
}

bool Tree::isValid() const {
	return root != NULL;
}

void Tree::clear() {
	if (root != NULL) {
		delete root;
	}
	variablesNames.clear();
}

void Tree::appendVariables(map<string, pair<int, int>> otherVariables) {
	for (map<string, pair<int, int>>::iterator otherIterator = otherVariables.begin();
		otherIterator != otherVariables.end(); otherIterator++) {
		if (variablesNames.find(otherIterator->first) != variablesNames.end()) {
			variablesNames[otherIterator->first].first++;
		}
		else {
			variablesNames[otherIterator->first] = make_pair(1, 0);
		}
	}
}

Tree Tree::operator=(const Tree& otherTree) {
	if (this != &otherTree) {
		clear();
		if (otherTree.root != NULL) {
			root = otherTree.root;
		}
		else {
			root = NULL;
			variablesNames.clear();
		}
	}
	return *this;
}

Tree Tree::operator+(const Tree& otherTree) {

	Tree sumTree(*this);

	if (otherTree.root != NULL) {
		Node* clonedJoinNode = otherTree.root->clone();
		if (sumTree.root->join(clonedJoinNode, sumTree.variablesNames)) {
			sumTree.appendVariables(otherTree.variablesNames);
		}
		else {
			sumTree.clear();
			sumTree.root = clonedJoinNode;
			sumTree.variablesNames = otherTree.variablesNames;
		}
	}

	return sumTree;
}

void Tree::moveFrom(Tree& other) {
	if (this != &other) {
		root = other.root;
		variablesNames = other.variablesNames;
		other.root = NULL;
	}
}

Tree::Tree(Tree&& other) {
	// test info (should be deleted for practical usage)
	cout << "\n\t(move construtor used)\n";
	moveFrom(other);
}

Tree Tree::operator=(Tree&& other) {
	// test info (should be deleted for practical usage)
	cout << "\t(move operator used)\n";;
	moveFrom(other);
	return *this;
}
