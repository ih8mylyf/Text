#include <iostream>

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

int main(){
Cat c;
cout << c.speak() << endl;
}
