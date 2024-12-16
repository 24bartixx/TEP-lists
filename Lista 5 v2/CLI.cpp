#include "CLI.h"
#include "HelperMethods.h"

const string CLI::PATH = "tree.txt";

const string CLI::CLI_HEADER = "Tree prompt> ";
const string CLI::UNKNOWN_COMMAND = "Unknown command!";
const string CLI::SWITCHED_TREE_INFO = "Switched tree to index: ";
const string CLI::CURRENT_TREE_INDEX = "Current tree index: ";
const string CLI::INDEX_NOT_GIVEN = "Index was not given!";
const string CLI::TREES_COUNT = "Trees count: ";
const string CLI::INDEX_OUT_OF_BOUNDS = "Index out of bounds!";
const string CLI::TREE_PRINT = "Tree: ";
const string CLI::TREE_CREATED_SUCCESSFULLY = "Tree created successfully!";
const string CLI::TREE_NOT_CREATED_SUCCESSFULLY = "The tree couldn't be created!";
const string CLI::NO_TREES_INFO = "There are no trees!";
const string CLI::COMP_VALUE = "Calculated value: ";
const string CLI::COMP_FAIL = "Couldn't calculate!";
const string CLI::OPEN_FILE_FAIL = "Couldn't open file to save trees";
const string CLI::JOINED_INFO = "Trees merged successfully!";
const string CLI::JOIN_TREE_FAIL = "Failed to merge trees!";
const string CLI::TREE_REMAINS_THE_SAME = "The tree has not been changed!";
const string CLI::LEAVES_COUNT = "Leaves count: ";
const string CLI::INCORRECT_INPUT = "Incorrect input!";
const string CLI::TESTED_SUCCESSFULLY = "Tested successfully: ";
const string CLI::TEST_FAIL = "Test failed: ";

const string CLI::SWITCH_COMMAND = "switch";
const string CLI::CURRENT_COMMAND = "current";
const string CLI::COUNT_COMMAND = "count";
const string CLI::ENTER_COMMAND = "enter";
const string CLI::PRINT_COMMAND = "print";
const string CLI::VARS_COMMAND = "vars";
const string CLI::COMP_COMMAND = "comp";
const string CLI::JOIN_COMMAND = "join";
const string CLI::LEAVES_COMMAND = "leaves";
const string CLI::TEST_COMMAND = "test";

CLI::CLI() : saver(MyResultSaver(PATH)), currentTreeIndex(-1) {

}

CLI::~CLI() {

	for (int i = 0; i < trees.size(); i++) {
		delete trees[i];
	}
	trees.clear();

}

void CLI::simulateCLI() {
	string command;
	while (true) {
		cout << CLI_HEADER;
		getline(cin, command);
		cout << endl;
		processCommand(command);
		cout << endl;
		//#include <thread>
		//#include <chrono>
		// this_thread::sleep_for(chrono::seconds(1));
	}
}

void CLI::processCommand(string entireCommand) {
	istringstream stream(entireCommand);
	string command;
	if (stream >> command) {
		command = removeSpecialCharacters(command);

		if (command == SWITCH_COMMAND) {
			string newCurrentIndexString;
			if (stream >> newCurrentIndexString) {
				if (isValue(newCurrentIndexString)) {

					MyResult<int, MyError> result = convertToInt(newCurrentIndexString);

					if (result.isSuccess()) {
						int newIndex = result.getValue();
						if (newIndex >= 0 && newIndex < trees.size()) {
							// trees[currentTreeIndex] = trees[newIndex];
							currentTreeIndex = newIndex;
							cout << "\t" << SWITCHED_TREE_INFO << newIndex << endl << endl;
							printTree(trees[currentTreeIndex]);
						}
						else {
							cout << "\t" << INDEX_OUT_OF_BOUNDS << endl;
							if (currentTreeIndex == -1) {
								cout << "\t" << NO_TREES_INFO << endl;
							}
							else {
								cout << "\t" << TREES_COUNT << trees.size() << endl;
								cout << "\n\t" << CURRENT_TREE_INDEX << currentTreeIndex << endl;
								printTree(trees[currentTreeIndex]);
							}
						}
					}
					else {
						cout << "\t " << result.getErrors()[0]->getErrorMessage() << endl;
					}
				}
				else {
					cout << "\t" << INDEX_NOT_GIVEN << endl << endl;
					cout << "\t" << CURRENT_TREE_INDEX << currentTreeIndex << endl << endl;
					printTree(trees[currentTreeIndex]);
				}
			}
			else {
				cout << "\t" << INDEX_NOT_GIVEN << endl;
				if (currentTreeIndex != -1) {
					cout << "\t" << CURRENT_TREE_INDEX << currentTreeIndex << endl;
					printTree(trees[currentTreeIndex]);
				}
			}
		}
		else if (command == CURRENT_COMMAND) {
			if (trees.empty()) {
				cout << "\t" << NO_TREES_INFO << endl;
			}
			else {
				cout << "\t" << CURRENT_TREE_INDEX << currentTreeIndex << endl << endl;
				printTree(trees[currentTreeIndex]);
			}
		}
		else if (command == COUNT_COMMAND) {
			cout << "\t" << TREES_COUNT << trees.size() << endl;
		}
		else if (command == ENTER_COMMAND) {
			trees.push_back(Tree::enter(stream));
			currentTreeIndex = trees.size() - 1;
			printTree(trees.back());
			MyResult<string, MyError> saveResult = saver.save(*trees.back());
			if (saveResult.isSuccess()) {
				cout << endl << "\t" << saveResult.getValue() << endl;
			}
			else {
				cout << endl << "\t" << saveResult.getErrors()[0]->getErrorMessage() << endl;
			}
		}
		else if (command == PRINT_COMMAND) {

			if (currentTreeIndex != -1) {
				printTree(trees[currentTreeIndex]);
			}
			else {
				cout << "\t" << NO_TREES_INFO << endl;
			}

		}
		else if (command == VARS_COMMAND) {

			if (currentTreeIndex != -1) {
				if (trees[currentTreeIndex]->isSuccess()) {
					cout << "\t" << trees[currentTreeIndex]->getValue().vars() << endl;
				}
				else {
					cout << "\t" << TREE_NOT_CREATED_SUCCESSFULLY << endl;
				}
			}
			else {
				cout << "\t" << NO_TREES_INFO << endl;
			}

		}
		else if (command == COMP_COMMAND) {
			if (currentTreeIndex != -1) {
				if (trees[currentTreeIndex]->isSuccess()) {
					MyResult<double, MyError> result = trees[currentTreeIndex]->getValue().comp(stream);
					if (result.isSuccess()) {
						cout << "\t" << COMP_VALUE << result.getValue() << endl;
					}
					else {
						cout << "\t" << COMP_FAIL << endl << endl;
						cout << "\t" << result.getErrors()[0]->getErrorMessage() << endl;
					}

				}
				else {
					cout << "\t" << TREE_NOT_CREATED_SUCCESSFULLY << endl;
				}
			}
			else {
				cout << "\t" << NO_TREES_INFO << endl;
			}
		}
		else if (command == JOIN_COMMAND) {
			if (currentTreeIndex != -1) {
				if (trees[currentTreeIndex]->isSuccess()) {
					MyResult<void, MyError> result = trees[currentTreeIndex]->getValue().join(stream);
					if (result.isSuccess()) {
						cout << "\t" << JOINED_INFO << endl;
						printTree(trees[currentTreeIndex]);
						resetSaver();
					}
					else {
						cout << "\t" << JOIN_TREE_FAIL << endl << endl;
						vector<MyError*> errors = result.getErrors();
						for (size_t i = 0; i < errors.size(); i++) {
							cout << "\t" << errors[i]->getErrorMessage() << endl;
						}
						cout << endl << "\t" << TREE_REMAINS_THE_SAME << endl << endl;
						printTree(trees[currentTreeIndex]);
					}
				}
				else {
					cout << "\t" << TREE_NOT_CREATED_SUCCESSFULLY << endl;
				}
			}
			else {
				cout << "\t" << NO_TREES_INFO << endl;
			}
		}
		else if (command == LEAVES_COMMAND) {
			if (currentTreeIndex != -1) {
				if (trees[currentTreeIndex]->isSuccess()) {
					cout << "\t" << LEAVES_COUNT << trees[currentTreeIndex]->getValue().leaves() << endl;
				}
				else {
					cout << "\t" << TREE_NOT_CREATED_SUCCESSFULLY << endl;
				}
			}
			else {
				cout << "\t" << NO_TREES_INFO << endl;
			}
		}
		else if (command == TEST_COMMAND) {
			int x, y;
			if (stream >> x && stream >> y) {
				MyResult<int*, int> result = test(x, y);
				if (result.isSuccess()) {
					cout << "\t" << TESTED_SUCCESSFULLY;
					cout << *result.getValue() << endl;
				}
				else {
					cout << "\t" << TEST_FAIL << *result.getErrors()[0] << endl;
				}
			}
			else {
				cout << "\t" << INCORRECT_INPUT << endl;
			}
		}
		else {
			cout << "\t" << UNKNOWN_COMMAND << endl;
		}
	}
}

void CLI::printErrors(MyResult<Tree, MyError>* errorTree) {
	cout << "\t" << TREE_NOT_CREATED_SUCCESSFULLY << endl << endl;
	vector<MyError*> errors = errorTree->getErrors();
	for (int i = 0; i < errors.size(); i++) {
		cout << "\t" << errors[i]->getErrorMessage() << endl;
	}
}

void CLI::printTree(MyResult<Tree, MyError>* tree) {
	if (tree->isSuccess()) {
		cout << "\t" << TREE_CREATED_SUCCESSFULLY;
		cout << endl << "\t" << TREE_PRINT << tree->getValue().toString() << endl;
	}
	else {
		printErrors(tree);
	}
}

void CLI::resetSaver() {
	saver.resetSaver();
	for (size_t i = 0; i < trees.size(); i++) {
		saver.save(*trees[i]);
	}
}


MyResult<int*, int> CLI::test(int x, int y) {
	if ((x + y) % 2 == 0) {
		return MyResult<int*, int>::fail(new int(21));
	}
	return MyResult<int*, int>::ok(new int(12));
}