#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <string>

class UnitTest {
public:
	virtual bool run() = 0;
	virtual std::string testName() = 0;
};

#endif