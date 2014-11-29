/**
* Homework 2: Using Template
* Assigned: September 13
* Due: September 23 24:00
**/

// [TODO]
// Student ID: ##########
// Name: ÐÕÃû
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <string>
#include <stdexcept>

#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
	// [TODO] Add private variables and methods here
	size_t _size;
	T* _storage;

public:
	// Do NOT modify following interfaces
	Vector();
	Vector(int size, const T& val = T());
	Vector(const Vector& x);
	~Vector();
	Vector<T>& operator=(const Vector<T>& x);
	int size() const;
	bool empty() const;
	T& operator [](int pos);
	void resize(size_t n, T val = T());
	void push_back(const T& val);
	void sort();
};

// (default constructor)
// Constructs an empty container, with no elements.
template <typename T>
Vector<T>::Vector() {
	// [TODO]
}

// (fill constructor)
// Constructs a container with n elements.
// Each element is a copy of val.
template <typename T>
Vector<T>::Vector(int size, const T& val) {
	// [TODO]
}

// (copy constructor)
// Constructs a container with a copy of each of the
// elements in x, in the same order.
template <typename T>
Vector<T>::Vector(const Vector& x) {
	// [TODO]
}

// (destructor)
// Destroys the container object.
template <typename T>
Vector<T>::~Vector() {
	// [TODO]
}

// operator=
// Assigns new contents to the container, replacing its
// current contents, and modifying its size accordingly.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x) {
	// [TODO]
}

// size
// Returns the number of elements in the vector.
// This is the number of actual objects held in the
// vector, which is not necessarily equal to its
// storage capacity.
template <typename T>
int Vector<T>::size() const {
	// [TODO]
}

// empty
// Returns whether the vector is empty
template <typename T>
bool Vector<T>::empty() const {
	// [TODO]
}

// operator[]
// Returns a reference to the element at position n
// in the vector container.
// if the requested position is out of range, the
// behavior is undefined
template <typename T>
T& Vector<T>::operator[](int pos) {
	// [TODO]
}

// resize
// Resizes the container so that it contains n elements.
// If n is smaller than the current container size, the 
// content is reduced to its first n elements, removing 
// those beyond (and destroying them).
// If n is greater than the current container size, the 
// content is expanded by inserting at the end as many 
// elements as needed to reach a size of n. If val is 
// specified, the new elements are initialized as copies 
// of val, otherwise, they are value-initialized.
template <typename T>
void Vector<T>::resize(size_t n, T val) {
	// [TODO]
}

// push_back
// Adds a new element at the end of the vector, after its
// current last element. The content of val is copied (or
// moved) to the new element.
template <typename T>
void Vector<T>::push_back(const T& val) {
	// [TODO]
}

// a general sort
// Sort the vector, output the result in std out
// with monotonically increasing order in one line
// for instance: 
//     your original vector is 3 2 4 5
//     your output after sorting is 2 3 4 5
// you shouldn't change the order of oringinal vector
template <typename T>
void Vector<T>::sort() {
	// [TODO]
}

// specialization of string
// Sort the string vector in lexicographical increasing order 
// from tail to head!
// for instance:
//      your original vector is "abc" "cba" "bcaa"
//      your output after sorting is "bcaa" "cba" "abc"
// you shouldn't change the order of oringinal vector
template <>
void Vector<string>::sort() {
	//[TODO]
}


#endif

