#ifndef HELPER_METHODS_H
#define HELPER_METHODS_H

#include "MyResult.h"
#include "MyError.h"

#include <string>
#include <algorithm>
#include <sstream>
#include <utility>

std::string removeSpecialCharacters(std::string str);
std::pair<bool, std::string> filterToNumString(string str);
bool isVariable(std::string str);
bool isValue(std::string str);
int convertToDigit(std::string str);
MyResult<int, MyError> convertToInt(std::string str);

#endif