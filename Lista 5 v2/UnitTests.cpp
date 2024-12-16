#include "UnitTests.h"

void UnitTests::runMySmartPointerUnitTests() {
	cout << "\n===== MySmartPointer Unit Tests =====\n";

	printUnitTestResult(MySmartPointerUnitTest1::testName(), MySmartPointerUnitTest1::run());
	printUnitTestResult(MySmartPointerUnitTest2::testName(), MySmartPointerUnitTest2::run());
	printUnitTestResult(MySmartPointerUnitTest3::testName(), MySmartPointerUnitTest3::run());

	cout << endl;
}

void UnitTests::runMoveSemanticsUnitTests() {
	cout << "\n===== Move Semantics Unit Tests =====\n";

	printUnitTestResult(MoveSemanticsUnitTest1::testName(), MoveSemanticsUnitTest1::run());
	printUnitTestResult(MoveSemanticsUnitTest2::testName(), MoveSemanticsUnitTest2::run());
	printUnitTestResult(MoveSemanticsUnitTest3::testName(), MoveSemanticsUnitTest3::run());
	printUnitTestResult(MoveSemanticsUnitTest4::testName(), MoveSemanticsUnitTest4::run());
	printUnitTestResult(MoveSemanticsUnitTest5::testName(), MoveSemanticsUnitTest5::run());

	cout << endl;
}

void UnitTests::runAll() {
	runMySmartPointerUnitTests();
	runMoveSemanticsUnitTests();
}

void UnitTests::printUnitTestResult(string testName, bool testResult) {
	cout << "\n\t" << testName << endl;
	if (testResult) {
		cout << GREEN << "\t\tTest passed!\n" << RESET;
	}
	else {
		cout << RED << "\t\tTest failed!\n" << RESET;
	}
}
