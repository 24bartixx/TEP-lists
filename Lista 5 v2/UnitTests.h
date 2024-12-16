#ifndef TESTS_H
#define TESTS_H

#include "MySmartPointerUnitTests.h"
#include "MoveSemanticsUnitTests.h"

#include <iostream>
#include <string>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace std;

class UnitTests {
public:
	static void runMySmartPointerUnitTests();
	static void runMoveSemanticsUnitTests();
	static void runAll();
private:
	static void printUnitTestResult(string testName, bool testResult);
};

#endif