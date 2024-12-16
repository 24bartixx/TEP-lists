#include "MoveSemanticsUnitTests.h"

Tree getTree(string inputStr) {

	Tree tree;

	istringstream stream(inputStr);
	MyResult<Tree, MyError>* myResult = Tree::enter(stream);

	if (myResult->isSuccess()) {
		tree = myResult->getValue();
	}

	return move(tree);
}


// Test 1

const string MoveSemanticsUnitTest1::TREE_STR = "1";

bool MoveSemanticsUnitTest1::run() {
	Tree tree = getTree(MoveSemanticsUnitTest1::TREE_STR);
	Tree movedTree;
	movedTree = move(tree);

	if (!tree.isValid() && movedTree.isValid()) {
		return true;
	}

	return false;
}

string MoveSemanticsUnitTest1::testName() {
	return "Test1: " + TREE_STR;
}

// Test 2

const string MoveSemanticsUnitTest2::TREE_STR = "+ 1 2";

bool MoveSemanticsUnitTest2::run() {
	Tree tree = getTree(MoveSemanticsUnitTest2::TREE_STR);
	Tree movedTree;
	movedTree = move(tree);

	if (!tree.isValid() && movedTree.isValid()) {
		return true;
	}

	return false;
}

string MoveSemanticsUnitTest2::testName() {
	return "Test2: " + TREE_STR;
}

// Test 3

const string MoveSemanticsUnitTest3::TREE_STR = "sin * + 1 a - a / 1 cos b";

bool MoveSemanticsUnitTest3::run() {
	Tree tree = getTree(MoveSemanticsUnitTest3::TREE_STR);
	Tree movedTree;
	movedTree = move(tree);

	if (!tree.isValid() && movedTree.isValid()) {
		return true;
	}

	return false;
}

string MoveSemanticsUnitTest3::testName() {
	return "Test3: " + TREE_STR;
}

// Test 4

const string MoveSemanticsUnitTest4::TREE_STR = "+ + 1";

bool MoveSemanticsUnitTest4::run() {
	Tree tree = getTree(MoveSemanticsUnitTest4::TREE_STR);
	Tree movedTree;
	movedTree = move(tree);

	if (!tree.isValid() && movedTree.isValid()) {
		return true;
	}

	return false;
}

string MoveSemanticsUnitTest4::testName() {
	return "Test4: " + TREE_STR;
}

// Test 5

const string MoveSemanticsUnitTest5::TREE_STR = "";

bool MoveSemanticsUnitTest5::run() {
	Tree tree = getTree(MoveSemanticsUnitTest5::TREE_STR);
	Tree movedTree;
	movedTree = move(tree);

	if (!tree.isValid() && movedTree.isValid()) {
		return true;
	}

	return false;
}

string MoveSemanticsUnitTest5::testName() {
	return "Test5: " + TREE_STR;
}
