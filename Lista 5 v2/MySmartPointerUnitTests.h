#ifndef MY_SMART_POINTER_TESTS_H
#define MY_SMART_POINTER_TESTS_H

#include "UnitTest.h"
#include "MySmartPointer.h"

#include <iostream>
#include <string>

using namespace std;

class MySmartPointerUnitTest1 : public UnitTest {
public:
	static bool run();
	static string testName();
private:
	static bool createPointer(int* pointer);
};

class MySmartPointerUnitTest2 : public UnitTest {
public:
	static bool run();
	static string testName();
private:
	static bool createPointer1(int* pointer);
	static bool createPointer2(MySmartPointer<int> mySmartPointer);
};

class MySmartPointerUnitTest3 : public UnitTest {
public:
	static bool run();
	static string testName();
private:
	class InnerClass {
	public:
		InnerClass(int newValue) : value(newValue) {}
		int increment() { return ++value; }
		int getValue() { return value; }
	private:
		int value;
	};

	static bool createPointer1(InnerClass* pointer);
	static bool createPointer2(MySmartPointer<InnerClass> mySmartPointer);
	static bool createPointer3(MySmartPointer<InnerClass> mySmartPointer);
	static bool createPointer4(MySmartPointer<InnerClass> mySmartPointer);

};

#endif