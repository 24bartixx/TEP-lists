#ifndef MY_SMART_POINTER_H
#define MY_SMART_POINTER_H


template <typename T>
class MySmartPointer {
public:
	MySmartPointer(T* newPointer);
	MySmartPointer(const MySmartPointer& other);

	~MySmartPointer();

	T* operator->() { return pointer; }
	T& operator*() { return *pointer; }

	MySmartPointer& operator=(const MySmartPointer& other);

private: 

	class MyCounter {
	public:
		MyCounter() : count(0) {}
		int increment() { return ++count; }
		int decrement() { return --count; }
		int getCount() { return count; }
	private:
		int count;
	};

	T* pointer;
	MyCounter* counter;

	void clear();
};

template <typename T>
MySmartPointer<T>::MySmartPointer(T* newPointer) {
	pointer = newPointer;
	counter = new MyCounter();
	counter->increment();
}

template <typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer& other) {
	pointer = other.pointer;
	counter = other.counter;
	counter->increment();
}

template <typename T>
MySmartPointer<T>::~MySmartPointer() {
	clear();
}

template <typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(const MySmartPointer<T>& other) {
	clear();
	pointer = other.pointer;
	counter = other.counter;
	counter->increment();
	return this;
}

template <typename T>
void MySmartPointer<T>::clear() {
	if (counter->decrement() == 0) {
		delete pointer;
		delete counter;
	}
}

#endif
