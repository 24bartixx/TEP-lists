#include "HelperMethods.h"

#include <iostream>

using namespace std;

string removeSpecialCharacters(string str) {
	string strWithoutSpecialCharacters;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]) || isalpha(str[i])) {
			strWithoutSpecialCharacters += str[i];
		}
	}
	return strWithoutSpecialCharacters;
}

pair<bool, string> filterToNumString(string str) {
	bool positive = true;
	string returnString = "";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '-' && returnString.empty()) {
			positive = false;
		}
		if (isdigit(str[i])) {
			returnString += str[i];
		}
	}
	return pair<bool, string>(positive, returnString);
}

bool isVariable(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isalpha(str[i])) {
			return true;
		}
	}
	return false;
}

bool isValue(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i])) {
			return true;
		}
	}
	return false;
}

int convertToDigit(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i])) {
			return str[i] - '0';
		}
	}
	// cout << "\nNo digit in value! Setting 1 instead!\n\n";
	return 1;
}

MyResult<int, MyError> convertToInt(string str) {
	pair<bool, string> stringPair = filterToNumString(str);
	istringstream stream(stringPair.second);
	int numberToReturn;
	stream >> numberToReturn;
	if (!stream.fail() && !(!stringPair.first && numberToReturn == INT_MAX)) {
		return MyResult<int, MyError>::ok(stringPair.first ? numberToReturn : -numberToReturn);
	}
	return MyResult<int, MyError>::fail(new MyError(MyError::FAILED_TO_CONVERT_TO_INT));
}
