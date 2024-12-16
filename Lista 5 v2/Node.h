#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility> // pair
#include <cctype>
#include <typeinfo>
#include <cmath>

#include "MyError.h"
#include "MyResult.h"

using namespace std;

class Node {
public:

	~Node();

	virtual MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames) = 0;
	bool join(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors);
	bool join(Node* joinRoot, map<string, pair<int, int>>& variablesNames);
	int leaves();

	virtual string toString() const = 0;
	virtual Node* clone() const = 0;

protected:
	vector<Node*> childNodes;
};

class ValueNode : public Node {
public:

	ValueNode(string nodeValue, vector<MyError*>& errors);
	ValueNode(int newValue);

	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	string toString() const;
	Node* clone() const;

private:
	int value;
	static const double DEFAULT_VALUE;
};

class VariableNode : public Node {
public:
	VariableNode(string variableToProcess);

	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);
	string getVariableName();

	string toString() const;
	Node* clone() const;

private:
	string variableName;
};

class OneChildOperatorNode : public Node {
public:
	virtual string getOperator() const = 0;
	void init(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors);
	string toString() const;
};

class TwoChildrenOperatorNode : public OneChildOperatorNode {
public:
	void init(istringstream& stream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors);
};

class AddNode : public TwoChildrenOperatorNode {
public:
	static const string OPERATOR_SIGN;

	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	Node* clone() const;

};

class SubstractNode : public TwoChildrenOperatorNode {
public:
	static const string OPERATOR_SIGN;

	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	Node* clone() const;

};

class MultiplicationNode : public TwoChildrenOperatorNode {
public:
	static const string OPERATOR_SIGN;

	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	Node* clone() const;

};

class DivisionNode : public TwoChildrenOperatorNode {
public:
	static const string OPERATOR_SIGN;

	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	Node* clone() const;

};

class SinusNode : public OneChildOperatorNode {
public:
	static const string OPERATOR_SIGN;

	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);

	Node* clone() const;

};

class CosinusNode : public OneChildOperatorNode {
public:
	static const string OPERATOR_SIGN;
	string getOperator() const;
	MyResult<double, MyError> calculateValue(map<string, pair<int, int>>& variablesNames);
	Node* clone() const;
};

Node* parseNode(istringstream& inputStream, map<string, pair<int, int>>& variablesNames, vector<MyError*>& errors);

#endif