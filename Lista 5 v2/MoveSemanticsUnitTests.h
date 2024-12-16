#ifndef MOVE_SEMANTICS_UNIT_TESTS_H
#define MOVE_SEMANTICS_UNIT_TESTS_H

#include "UnitTest.h"
#include "Tree.h"
#include "MyResult.h"

#include <string>

static Tree getTree(string inputStr);

class MoveSemanticsUnitTest1 : UnitTest {
public:
	static bool run();
	static string testName();
private:
	static const string TREE_STR;
};

class MoveSemanticsUnitTest2 : UnitTest {
public:
	static bool run();
	static string testName();
private:
	static const string TREE_STR;
};

class MoveSemanticsUnitTest3 : UnitTest{
public:
	static bool run();
	static string testName();
private:
	static const string TREE_STR;
};

class MoveSemanticsUnitTest4 : UnitTest {
public:
	static bool run();
	static string testName();
private:
	static const string TREE_STR;
};

class MoveSemanticsUnitTest5 : UnitTest {
public:
	static bool run();
	static string testName();
private:
	static const string TREE_STR;
};

#endif
