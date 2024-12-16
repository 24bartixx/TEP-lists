#include "MyResultSaver.h"

using namespace std;

const string MyResultSaver::GENERIC_TYPE_NOT_SAVED = "Generic type was not saved!";
const string MyResultSaver::SAVED_ERRORS = "Errors saved to the file!";
const string MyResultSaver::SAVED_TREE = "Tree saved to the file!";

MyResultSaver::MyResultSaver(string newPath) : firstTime(true), path(newPath) {}



void MyResultSaver::resetSaver() {
	firstTime = true;
}