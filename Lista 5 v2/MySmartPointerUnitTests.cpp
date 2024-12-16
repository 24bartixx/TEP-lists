#include "MySmartPointerUnitTests.h"

// Test 1

bool MySmartPointerUnitTest1::run() {
	int* num = new int;
	*num = 10;

	if (!createPointer(num)) {
		return false;
	}

	return *num != 11;
}

string MySmartPointerUnitTest1::testName() {
	return "Test 1: constructor, destructor, and operator*";
}

bool MySmartPointerUnitTest1::createPointer(int* pointer) {
	MySmartPointer<int> mySmartPointer(pointer);
	if ((*mySmartPointer)++ != 10) {
		return false;
	}
	if (*mySmartPointer != 11) {
		return false;
	}
	return true;
}

// Test 2

bool MySmartPointerUnitTest2::run() {
	int* num = new int;
	*num = -6;

	if (!createPointer1(num)) {
		return false;
	}

	return *num != 4;
}

string MySmartPointerUnitTest2::testName() {
	return "Test 2: constructor, desctructor, operator*, counter";
}

bool MySmartPointerUnitTest2::createPointer1(int* pointer) {
	MySmartPointer<int> mySmartPointer(pointer);
	if (*mySmartPointer != -6) {
		return false;
	}
	if (!createPointer2(mySmartPointer)) {
		return false;
	}
	if (*mySmartPointer != 4) {
		return false;
	}
	return true;
}

bool MySmartPointerUnitTest2::createPointer2(MySmartPointer<int> mySmartPointer) {
	MySmartPointer<int> mySmartPointer2(mySmartPointer);
	if (*mySmartPointer != *mySmartPointer2 || *mySmartPointer2 != -6) {
		return false;
	}
	*mySmartPointer2 += 10;
	if (*mySmartPointer != *mySmartPointer2 || *mySmartPointer2 != 4) {
		return false;
	}
	return true;
}

// Test 3

bool MySmartPointerUnitTest3::run() {
	InnerClass* innerClassPointer = new InnerClass(0);

	if (!createPointer1(innerClassPointer)) {
		return false;
	}

	if(innerClassPointer)

	return innerClassPointer->getValue() != 2;
}

string MySmartPointerUnitTest3::testName() {
	return "Test 3: constructor, desctructor, operator->, counter";
}

bool MySmartPointerUnitTest3::createPointer1(InnerClass* pointer) {
	MySmartPointer<InnerClass> mySmartPointer(pointer);
	if (mySmartPointer->getValue() != 0) {
		return false;
	}
	if (mySmartPointer->increment() != 1) {
		return false;
	}
	if (!createPointer2(mySmartPointer)) {
		return false;
	}
	if (mySmartPointer->getValue() != 3) {
		return false;
	}
	if (!createPointer4(mySmartPointer)) {
		return false;
	}
	if (mySmartPointer->getValue() != 4) {
		return false;
	}
	return true;
}

bool MySmartPointerUnitTest3::createPointer2(MySmartPointer<InnerClass> mySmartPointer) {
	MySmartPointer<InnerClass> mySmartPointer2(mySmartPointer);
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 1) {
		return false;
	}
	if (mySmartPointer2->increment() != 2) {
		return false;
	}
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 2) {
		return false;
	}
	if (!createPointer3(mySmartPointer2)) {
		return false;
	}
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 3) {
		return false;
	}
	return true;
}

bool MySmartPointerUnitTest3::createPointer3(MySmartPointer<InnerClass> mySmartPointer) {
	MySmartPointer<InnerClass> mySmartPointer2(mySmartPointer);
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 2) {
		return false;
	}
	if (mySmartPointer2->increment() != 3) {
		return false;
	}
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 3) {
		return false;
	}
	return true;
}

bool MySmartPointerUnitTest3::createPointer4(MySmartPointer<InnerClass> mySmartPointer) {
	MySmartPointer<InnerClass> mySmartPointer2(mySmartPointer);
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 3) {
		return false;
	}
	if (mySmartPointer2->increment() != 4) {
		return false;
	}
	if (mySmartPointer->getValue() != mySmartPointer2->getValue() || mySmartPointer2->getValue() != 4) {
		return false;
	}
	return true;
}
