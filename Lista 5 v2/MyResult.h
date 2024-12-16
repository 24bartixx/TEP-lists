#ifndef MY_RESULT_H
#define MY_RESULT_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename E>
class MyResult
{
public:
	MyResult(const T& newValue) : value(new T(newValue)), errors() {}
	MyResult(E* newError) : value(NULL), errors(1, newError) {}
	MyResult(vector<E*>& newErrors) : value(NULL), errors(newErrors) {}
	MyResult(const MyResult<T, E>& otherMyResult);

	~MyResult();

	static MyResult<T, E> ok(const T& value) { return MyResult<T, E>(value); }
	static MyResult<T, E> fail(E* error) { return MyResult<T, E>(error); }
	static MyResult<T, E> fail(vector<E*>& errors) { return MyResult<T, E>(errors); }

	MyResult<T, E>& operator=(const MyResult<T, E>& otherMyResult);

	bool isSuccess() const { return errors.empty(); }

	T& getValue() const { return *value; }
	vector<E*>& getErrors() { return errors; }

private:
	T* value;
	vector<E*> errors;
};

/* CONSTRUCTOR */

template <typename T, typename E>
MyResult<T, E>::MyResult(const MyResult<T, E>& otherMyResult) {

	value = NULL;

	*this = otherMyResult;

}

/* DESTRUCTOR */

template <typename T, typename E>
MyResult<T, E>::~MyResult() {
	if (value) {
		delete value;
	}
	for (int i = 0; i < errors.size(); i++) {
		delete errors[i];
	}
	errors.clear();
}

/* OPERATOR */
template <typename T, typename E>
MyResult<T, E>& MyResult<T, E>::operator=(const MyResult<T, E>& otherMyResult) {
	if (this != &otherMyResult) {
		if (value) {
			delete value;
		}

		for (int i = 0; i < errors.size(); i++) {
			delete errors[i];
		}
		errors.clear();

		value = otherMyResult.value ? new T(*otherMyResult.value) : NULL;

		for (int i = 0; i < otherMyResult.errors.size(); i++) {
			if (otherMyResult.errors[i]) {
				errors.push_back(new E(*otherMyResult.errors[i]));
			}
			else {
				errors.push_back(NULL);
			}
		}

	}
	return *this;
}

template <typename E>
class MyResult<void, E>
{
public:
	MyResult() : errors() {}
	MyResult(E* newError) : errors(1, newError) {}
	MyResult(vector<E*>& newErrors) : errors(newErrors) {}
	MyResult(const MyResult<void, E>& otherMyResult);

	~MyResult();

	static MyResult<void, E> ok() { return MyResult<void, E>(); }
	static MyResult<void, E> fail(E* newError) { return MyResult<void, E>(newError); }
	static MyResult<void, E> fail(vector<E*>& newErrors) { return MyResult<void, E>(newErrors); }

	MyResult<void, E>& operator=(const MyResult<void, E>& other);

	bool isSuccess() const { return errors.empty(); }
	vector<E*>& getErrors() { return errors; }

private:
	vector<E*> errors;
};

/* CONSTRUCTOR */

template <typename E>
MyResult<void, E>::MyResult(const MyResult<void, E>& otherMyResult) {
	for (int i = 0; i < otherMyResult.errors.size(); i++) {
		if (otherMyResult.errors[i]) {
			errors.push_back(new E(*otherMyResult.errors[i]));
		}
		else {
			errors.push_back(NULL);
		}
	}
}

/* DESTRUCTOR */

template <typename E>
MyResult<void, E>::~MyResult() {
	for (int i = 0; i < errors.size(); i++) {
		delete errors[i];
	}
	errors.clear();
}

/* OPERATOR */

template <typename E>
MyResult<void, E>& MyResult<void, E>::operator=(const MyResult<void, E>& otherMyResult) {
	if (this != &otherMyResult) {

		for (int i = 0; i < errors.size(); i++) {
			delete errors[i];
		}
		errors.clear();

		for (int i = 0; i < otherMyResult.errors.size(); i++) {
			if (otherMyResult.errors[i]) {
				errors.push_back(new E(*otherMyResult.errors[i]));
			}
			else {
				errors.push_back(NULL);
			}
		}

	}
	return *this;
}


/* MODIFICATION */

template <typename TE>
class MyResult<TE*, TE>
{
public:
	MyResult() {}
	MyResult(TE* newValue, TE* newError);
	MyResult(vector<TE*>& newErrors) : errors(newErrors) {}
	MyResult(const MyResult<TE*, TE>& other);

	~MyResult();

	static MyResult<TE*, TE> ok(TE* value) { return MyResult<TE*, TE>(value, NULL); }
	static MyResult<TE*, TE> fail(TE* newError) { return MyResult<TE*, TE>(NULL, newError); }
	static MyResult<TE*, TE> fail(vector<TE*>& newErrors) { return MyResult<TE*, TE>(newErrors); }

	MyResult<TE*, TE>& operator=(const MyResult<TE*, TE>& other);

	bool isSuccess() const { return value; }

	TE* getValue() { return value; }
	vector<TE*>& getErrors() { return errors; }

private:
	TE* value;
	vector<TE*> errors;
};


template <typename TE>
MyResult<TE*, TE>::MyResult(TE* newValue, TE* newError) : value(newValue) {
	if (newError) {
		errors.push_back(newError);
	}
}

template <typename TE>
MyResult<TE*, TE>::MyResult(const MyResult<TE*, TE>& other) : value(other.value ? new TE(*other.value) : NULL) {
	for (int i = 0; i < other.errors.size(); i++) {
		other.errors[i]
			? errors.push_back(new TE(*other.errors[i]))
			: errors.push_back(NULL);
	}
}

template <typename TE>
MyResult<TE*, TE>::~MyResult() {
	if (value) {
		delete value;
	}
	for (int i = 0; i < errors.size(); i++) {
		delete errors[i];
	}
	errors.clear();
}

template <typename TE>
MyResult<TE*, TE>& MyResult<TE*, TE>::operator=(const MyResult<TE*, TE>& other) {
	if (this != &other) {

		if (value) {
			delete value;
		}

		for (int i = 0; i < errors.size(); i++) {
			delete errors[i];
		}
		errors.clear();

		value = other.isSuccess() ? new TE(*other.getValue()) : NULL;

		for (size_t i = 0; i < other.errors.size(); i++) {
			other.errors[i]
				? errors.push_back(new TE(*other.errors[i]))
				: errors.push_back(NULL);
		}

	}
	return *this;
}

#endif 