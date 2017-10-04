#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;


class Animal {
public:
    virtual string speak() const = 0;
};

class Cat : public Animal {
public: 
        virtual string speak() const;
};

class Dog : public Animal {
public: 
        virtual string speak() const;
};

string Cat::speak() const {
  return "meow";
}

string Dog::speak() const {
  return "bark";
}


template<class T>
class Array {
public:
        Array(int size);
        ~Array();
        T & operator[](int i) const;
        int size() const;
        void fill(T k);
        int * begin();
        int * end();

private:
        int len;
        T * data;
};
template<class T>
Array<T>::Array(int size){
	len = size;
	data = new T[len];
}

template<class T>
Array<T>::~Array(){
	delete data;
}

template<class T>
T & Array<T>::operator[](int i) const {
	return data[i];
}
	
template<class T>
int Array<T>::size() const {
	return len;
}
	
template<class T>
void Array<T>::fill(T k){
		for(int x=0;x<len;x++)
		{
			data[x] = k;
		}
	}

template<class T>
int * Array<T>::begin(){
	return data;
}

template<class T>
int * Array<T>::end(){
	return &data[len];
}


int main(int argc, char * args[]) {
	Array<Animal *> a(3);
	Dog d;
	Cat c;
  a[0] = &d;
  a[1] = &c;
  a[2] = &d;
  assert(a[0] == &d);
  assert(a[1] == &c);
  assert(a[2] == &d);
  assert(a.size() == 3);
  cout << a[0]->speak() << endl;
  cout << a[1]->speak() << endl;
  cout << a[2]->speak() << endl;
}
