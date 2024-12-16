#include "MyError.h"

using namespace std;

const string MyError::INCORRECT_INPUT = "Incorrect input!";
const string MyError::LACKING_VALUES = "Lacking values!";
const string MyError::INCORRECT_VALUE = "Incorrect value input!Setting default value to node!";
const string MyError::EXCESSIVE_ARGUMENTS = "Excessive arguments!";
const string MyError::FAILED_TO_CONVERT_TO_INT = "Failed to convert to int!";
const string MyError::DIVISION_BY_0 = "Division by 0!";
const string MyError::INCORRECT_NUMBER_OF_INPUTS = "Incorrect number of inputs!";
const string MyError::OPEN_FILE_ERROR = "Error opening the file!";

MyError::MyError(const string& newErrorMessage) : errorMessage(newErrorMessage) {}

string MyError::getErrorMessage() const {
    return errorMessage;
}