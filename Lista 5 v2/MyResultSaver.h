#ifndef MY_RESULT_SAVER_H
#define MY_RESULT_SAVER_H

#include <fstream>

#include "MyResult.h"
#include "MyError.h"
#include "Tree.h"

using namespace std;

class MyResultSaver {
public:
	MyResultSaver(string newPath);

	static const string GENERIC_TYPE_NOT_SAVED;
	static const string SAVED_ERRORS;
	static const string SAVED_TREE;

	template <typename T>
	MyResult<string, MyError> save(MyResult<T, MyError>& toSave);

	template <>
	MyResult<string, MyError> save<Tree>(MyResult<Tree, MyError>& toSave);

	void resetSaver();

private:
	bool firstTime;
	string path;
};

template <typename T>
MyResult<string, MyError> MyResultSaver::save(MyResult<T, MyError>& toSave) {

	if (!toSave.isSuccess()) {
		ofstream file;
		firstTime ? file.open(path) : file.open(path, ios::app);

		if (!file) {
			return MyResult<string, MyError>::fail(new MyError(MyError::OPEN_FILE_ERROR));
		}

		vector<MyError*> errors = toSave.getErrors();
		for (int i = 0; i < errors.size(); i++) {
			file << errors[i]->getErrorMessage() << endl;
		}
		file << endl;

		file.close();
		firstTime = false;
		return MyResult<string, MyError>::ok(SAVED_ERRORS);
	}

	return MyResult<string, MyError>::ok(GENERIC_TYPE_NOT_SAVED);

}

template <>
inline MyResult<string, MyError> MyResultSaver::save<Tree>(MyResult<Tree, MyError>& toSave) {
	ofstream file;
	firstTime ? file.open(path) : file.open(path, ios::app);
	if (!file) {
		return MyResult<string, MyError>::fail(new MyError(MyError::OPEN_FILE_ERROR));
	}
	if (toSave.isSuccess()) {
		file << toSave.getValue().toString() << endl << endl;
	}
	else {
		vector<MyError*> errors = toSave.getErrors();
		for (int i = 0; i < errors.size(); i++) {
			file << errors[i]->getErrorMessage() << endl;
		}
		file << endl;
	}
	file.close();
	firstTime = false;
	return MyResult<string, MyError>::ok(SAVED_TREE);
}

#endif
