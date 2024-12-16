#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "Tree.h"
#include "MyResultSaver.h"
#include "HelperMethods.h"

using namespace std;

class CLI {
public:
	CLI();
	~CLI();

	void simulateCLI();
private:
	static const string PATH;

	static const string CLI_HEADER;
	static const string UNKNOWN_COMMAND;
	static const string SWITCHED_TREE_INFO;
	static const string CURRENT_TREE_INDEX;
	static const string INDEX_NOT_GIVEN;
	static const string INDEX_OUT_OF_BOUNDS;
	static const string TREE_PRINT;
	static const string TREES_COUNT;
	static const string TREE_CREATED_SUCCESSFULLY;
	static const string TREE_NOT_CREATED_SUCCESSFULLY;
	static const string NO_TREES_INFO;
	static const string COMP_VALUE;
	static const string COMP_FAIL;
	static const string OPEN_FILE_FAIL;
	static const string JOINED_INFO;
	static const string JOIN_TREE_FAIL;
	static const string TREE_REMAINS_THE_SAME;
	static const string LEAVES_COUNT;
	static const string INCORRECT_INPUT;
	static const string TESTED_SUCCESSFULLY;
	static const string TEST_FAIL;

	static const string SWITCH_COMMAND;
	static const string CURRENT_COMMAND;
	static const string COUNT_COMMAND;
	static const string ENTER_COMMAND;
	static const string PRINT_COMMAND;
	static const string VARS_COMMAND;
	static const string COMP_COMMAND;
	static const string JOIN_COMMAND;
	static const string LEAVES_COMMAND;
	static const string TEST_COMMAND;

	int currentTreeIndex;
	vector <MyResult<Tree, MyError>*> trees;
	MyResultSaver saver;

	void processCommand(string command);
	void printErrors(MyResult<Tree, MyError>* errorTree);
	void printTree(MyResult<Tree, MyError>* tree);
	void resetSaver();

	MyResult<int*, int> test(int x, int y);
};

#endif
