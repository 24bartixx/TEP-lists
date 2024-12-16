#ifndef MY_ERROR_H
#define MY_ERROR_H

#include <string>

using namespace std;

class MyError {
public:

	static const string INCORRECT_INPUT;
	static const string LACKING_VALUES;
	static const string	INCORRECT_VALUE;
	static const string	EXCESSIVE_ARGUMENTS;
	static const string FAILED_TO_CONVERT_TO_INT;
	static const string DIVISION_BY_0;
	static const string INCORRECT_NUMBER_OF_INPUTS;
	static const string OPEN_FILE_ERROR;

	explicit MyError(const string& newErrorMessage);
	string getErrorMessage() const;

private:
	string errorMessage;
};

#endif
