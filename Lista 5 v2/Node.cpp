#include "Node.h"
#include "HelperMethods.h"

using namespace std;

const string AddNode::OPERATOR_SIGN = "+";
const string SubstractNode::OPERATOR_SIGN = "-";
const string MultiplicationNode::OPERATOR_SIGN = "*";
const string DivisionNode::OPERATOR_SIGN = "/";
const string SinusNode::OPERATOR_SIGN = "sin";
const string CosinusNode::OPERATOR_SIGN = "cos";

/* NODE */

Node::~Node() {
	for (int i = 0; i < childNodes.size(); i++) {
		delete childNodes[i];
	}
}

/* UNUSED */
bool Node::join(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors) {
	if (variablesNames.size() > 0) {
		for (int i = childNodes.size() - 1; i >= 0; i--) {
			VariableNode* variableNode = dynamic_cast<VariableNode*>(childNodes[i]);
			if (variableNode) {
				if (--variablesNames[variableNode->getVariableName()].first == 0) {
					variablesNames.erase(variableNode->getVariableName());
				}
				childNodes[i] = parseNode(stream, variablesNames, errors);
				return true;
			}
			else {
				if (childNodes[i]->join(stream, variablesNames, errors)) {
					return true;
				}
			}
		}
		return false;
	}

	for (int i = childNodes.size() - 1; i >= 0; i--) {
		ValueNode* valueNode = dynamic_cast<ValueNode*>(childNodes[i]);
		if (valueNode) {
			childNodes[i] = parseNode(stream, variablesNames, errors);
			return true;
		}
		else {
			if (childNodes[i]->join(stream, variablesNames, errors)) {
				return true;
			}
		}
	}
	return false;
}


bool Node::join(Node* joinRoot, map<string, pair<int, int>>& variablesNames) {
	if (variablesNames.size() > 0) {
		for (int i = childNodes.size() - 1; i >= 0; i--) {
			VariableNode* variableNode = dynamic_cast<VariableNode*>(childNodes[i]);
			if (variableNode) {
				if (--variablesNames[variableNode->getVariableName()].first == 0) {
					variablesNames.erase(variableNode->getVariableName());
				}
				childNodes[i] = joinRoot;
				return true;
			}
			else {
				if (childNodes[i]->join(joinRoot, variablesNames)) {
					return true;
				}
			}
		}
		return false;
	}

	for (int i = childNodes.size() - 1; i >= 0; i--) {
		ValueNode* valueNode = dynamic_cast<ValueNode*>(childNodes[i]);
		if (valueNode) {
			childNodes[i] = joinRoot;
			return true;
		}
		else {
			if (childNodes[i]->join(joinRoot, variablesNames)) {
				return true;
			}
		}
	}
	return false;
}

// mod
int Node::leaves() {
	if (childNodes.size() == 0) {
		return 1;
	}
	int toReturn = 0;
	for (int i = 0; i < childNodes.size(); i++) {
		toReturn += childNodes[i]->leaves();
	}
	return toReturn;
}

/* VALUE NODE */
const double ValueNode::DEFAULT_VALUE = 1.0;

ValueNode::ValueNode(string nodeValue, vector<MyError*>& errors) {
	if (isValue(nodeValue)) {
		value = convertToDigit(nodeValue);
	}
	else {
		errors.push_back(new MyError(MyError::INCORRECT_VALUE));
		value = ValueNode::DEFAULT_VALUE;
	}
}

ValueNode::ValueNode(int newValue) : value(newValue) {

}

MyResult<double, MyError> ValueNode::calculateValue(map<string, pair<int, int>>& variablesNames) {
	return MyResult<double, MyError>::ok(value);
}

string ValueNode::toString() const {

	ostringstream stream;
	stream << static_cast<char>('0' + value) << " ";
	return stream.str();
}

Node* ValueNode::clone() const {
	return new ValueNode(value);
}

/* VARIABLE NODE */
VariableNode::VariableNode(string variableToProcess)
	: variableName(removeSpecialCharacters(variableToProcess)) {
}

MyResult<double, MyError> VariableNode::calculateValue(map<string, pair<int, int>>& variablesNames) {
	return MyResult<double, MyError>::ok(variablesNames[variableName].second);
}

string VariableNode::getVariableName() {
	return variableName;
}

string VariableNode::toString() const {
	return variableName + " ";
}

Node* VariableNode::clone() const {
	return new VariableNode(variableName);
}

/* ONE CHILD OPERATOR NODE */
void OneChildOperatorNode::init(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors) {
	Node* childNode = parseNode(stream, variablesNames, errors);
	childNodes.push_back(childNode);
}

string OneChildOperatorNode::toString() const {
	string toReturn = getOperator() + " ";
	for (int i = 0; i < childNodes.size(); i++) {
		toReturn += childNodes[i]->toString();
	}
	return toReturn;
}

/* TWO CHILDREN NODE */
void TwoChildrenOperatorNode::init(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors) {
	for (int i = 0; i < 2; i++) {
		OneChildOperatorNode::init(stream, variablesNames, errors);
	}
}

/* ADD NODE */
string AddNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> AddNode::calculateValue(map<string, pair<int, int>>& variablesNames) {
	double treeValue = 0;
	for (int i = 0; i < childNodes.size(); i++) {
		MyResult<double, MyError> nodeValue = childNodes[i]->calculateValue(variablesNames);

		if (nodeValue.isSuccess()) {
			treeValue += nodeValue.getValue();
		}
		else {
			return nodeValue;
		}
	}
	return MyResult<double, MyError>::ok(treeValue);
}

Node* AddNode::clone() const {
	AddNode* node = new AddNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

/* SUBSTRACT NODE */
string SubstractNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> SubstractNode::calculateValue(map<string, pair<int, int>>& variablesNames) {

	MyResult<double, MyError> firstValue = childNodes[0]->calculateValue(variablesNames);

	if (!firstValue.isSuccess()) {
		return firstValue;
	}
	double treeValue = firstValue.getValue();

	for (int i = 1; i < childNodes.size(); i++) {
		MyResult<double, MyError> nodeValue = childNodes[i]->calculateValue(variablesNames);

		if (nodeValue.isSuccess()) {
			treeValue -= nodeValue.getValue();
		}
		else {
			return nodeValue;
		}
	}
	return MyResult<double, MyError>::ok(treeValue);
}

Node* SubstractNode::clone() const {
	SubstractNode* node = new SubstractNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

/* MULTIPLICATION NODE */
string MultiplicationNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> MultiplicationNode::calculateValue(map<string, pair<int, int>>& variablesNames) {

	MyResult<double, MyError> firstValue = childNodes[0]->calculateValue(variablesNames);
	if (!firstValue.isSuccess()) {
		return firstValue;
	}

	double treeValue = firstValue.getValue();

	for (int i = 1; i < childNodes.size(); i++) {
		MyResult<double, MyError> nodeValue = childNodes[i]->calculateValue(variablesNames);

		if (nodeValue.isSuccess()) {
			treeValue *= nodeValue.getValue();
		}
		else {
			return nodeValue;
		}
	}
	return MyResult<double, MyError>::ok(treeValue);;
}

Node* MultiplicationNode::clone() const {
	MultiplicationNode* node = new MultiplicationNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

/* DIVISION NODE */
string DivisionNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> DivisionNode::calculateValue(map<string, pair<int, int>>& variablesNames) {

	MyResult<double, MyError> firstValue = childNodes[0]->calculateValue(variablesNames);
	if (!firstValue.isSuccess()) {
		return firstValue;
	}

	double treeValue = firstValue.getValue();

	for (int i = 1; i < childNodes.size(); i++) {

		MyResult<double, MyError> nodeValue = childNodes[i]->calculateValue(variablesNames);

		if (nodeValue.isSuccess()) {
			if (nodeValue.getValue() == 0) {
				return MyResult<double, MyError>::fail(new MyError(MyError::DIVISION_BY_0));
			}
			treeValue /= nodeValue.getValue();
		}
		else {
			return nodeValue;
		}
	}
	return MyResult<double, MyError>::ok(treeValue);
}

Node* DivisionNode::clone() const {
	DivisionNode* node = new DivisionNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

/* SINUS NODE */
string SinusNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> SinusNode::calculateValue(map<string, pair<int, int>>& variablesNames) {
	MyResult<double, MyError> nodeValue = childNodes[0]->calculateValue(variablesNames);
	if (nodeValue.isSuccess()) {
		return MyResult<double, MyError>::ok(sin(nodeValue.getValue()));
	}
	return nodeValue;
}

Node* SinusNode::clone() const {
	SinusNode* node = new SinusNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

/* COSINUS NODE */
string CosinusNode::getOperator() const {
	return OPERATOR_SIGN;
}

MyResult<double, MyError> CosinusNode::calculateValue(map<string, pair<int, int>>& variablesNames) {
	MyResult<double, MyError> nodeValue = childNodes[0]->calculateValue(variablesNames);
	if (nodeValue.isSuccess()) {
		return MyResult<double, MyError>::ok(cos(nodeValue.getValue()));
	}
	return nodeValue;
}

Node* CosinusNode::clone() const {
	CosinusNode* node = new CosinusNode();
	for (int i = 0; i < childNodes.size(); i++) {
		node->childNodes.push_back(childNodes[i]->clone());
	}
	return node;
}

Node* parseNode(istringstream& inputStream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors) {

	string next;
	string errorMessage;
	if (inputStream >> next) {
		if (next == AddNode::OPERATOR_SIGN) {
			AddNode* node = new AddNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		else if (next == SubstractNode::OPERATOR_SIGN) {
			SubstractNode* node = new SubstractNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		else if (next == MultiplicationNode::OPERATOR_SIGN) {
			MultiplicationNode* node = new MultiplicationNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		else if (next == DivisionNode::OPERATOR_SIGN) {
			DivisionNode* node = new DivisionNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		next = removeSpecialCharacters(next);
		if (next == SinusNode::OPERATOR_SIGN) {
			SinusNode* node = new SinusNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		else if (next == CosinusNode::OPERATOR_SIGN) {
			CosinusNode* node = new CosinusNode();
			node->init(inputStream, variablesNames, errors);
			return node;
		}
		else if (isVariable(next)) {
			if (variablesNames.find(next) == variablesNames.end()) {
				variablesNames[next] = make_pair(1, 0);
			}
			else {
				variablesNames[next].first++;
			}
			return new VariableNode(next);
		}
		else if (isValue(next)) {
			return new ValueNode(next, errors);
		}

		errorMessage = MyError::INCORRECT_INPUT + " (" + next + "!";
	}
	else {
		errorMessage = MyError::LACKING_VALUES;
	}

	errors.push_back(new MyError(errorMessage));
	return NULL;

}