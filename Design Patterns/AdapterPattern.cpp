#include <iostream>
#include <vector>
using namespace std;

/* Adapter Pattern
	***Adapter pattern definition ***
	coverts the interface of a class into another interface. Adapter lets
	classes work together that couldn’t otherwise
	because of incompatible interfaces	If adapter needs to coordinate with groups of adapted interfaces / classes, 	there's a separate pattern for that, called the Facade pattern
	***Facade pattern definition***
	provides a unified interface to a set of interfaces. Facade defines a
	high-level interface that makes a system easier touse
*/

class Turkey
{
public:
	virtual void gobble(void) {}
	virtual void fly(void) {}
};

class WildTurkey : public Turkey
{
public:
	void gobble(void)
	{
		cout << "Gobble gobble" << endl;
	}
	void fly(void)
	{
		cout << "I fly short distances" << endl;
	}
};

class Duck
{
public:
	virtual void quack(void) {}
	virtual void fly(void) {}
};

class TurkeyAdapter : public Duck
{
public:
	Turkey * turkey;
	TurkeyAdapter(Turkey* turkey);
	void quack(void);
	void fly(void);
};

TurkeyAdapter::TurkeyAdapter(Turkey* turkey)
{
	this->turkey = turkey;
}

void TurkeyAdapter::quack(void)
{
	this->turkey->gobble();
}

void TurkeyAdapter::fly(void)
{
	this->turkey->fly();
}

class Animal
{
public:
	virtual void makeNoise(void) {}
	virtual void fly(void) {}
	virtual void move(void) {}
};

class Dog : public Animal
{
public:
	void makeNoise();
	void fly();
	void move(void);
};

void Dog::makeNoise()
{
	cout << "Woof woof!" << endl;
}

void Dog::fly()
{
	cout << "I don't fly!" << endl;
}

void Dog::move(void)
{
	cout << "Run...Run!" << endl;
}

class Cat : public Animal
{
public:
	void makeNoise();
	void fly();
	void move(void);
};

void Cat::makeNoise()
{
	cout << "Meow meow!" << endl;
}

void Cat::fly()
{
	cout << "I don't fly!" << endl;
}

void Cat::move(void)
{
	cout << "Patter...Patter!" << endl;
}

class AnimalDuckAdapter : public Duck
{
private:
	Animal* myanimal;
public:
	AnimalDuckAdapter(Animal* myanimal);
	void setAdapterClass(Animal* myanimal);
	void quack(void);
	void fly(void);
};

AnimalDuckAdapter::AnimalDuckAdapter(Animal* myanimal)
{
	setAdapterClass(myanimal);
}

void AnimalDuckAdapter::setAdapterClass(Animal* myanimal)
{
	this->myanimal = myanimal;
}

void AnimalDuckAdapter::quack(void)
{
	this->myanimal->makeNoise();
}

void AnimalDuckAdapter::fly(void)
{
	this->myanimal->fly();
}


class AnimalFlockFacade : public Duck
{
public:
	vector<Animal*> MyAnimalList;
	~AnimalFlockFacade()
	{
		for (int animalindex = 0; animalindex < MyAnimalList.size(); animalindex++)
		{
			delete MyAnimalList[animalindex];
		}
	}
	void fly(void)
	{
		this->AllBirdsFly();
	}
	void addAnimal(Animal* NewAnimal)
	{
		MyAnimalList.push_back(NewAnimal);
	}
	void AllBirdsFly(void)
	{
		for (int animalindex = 0; animalindex < MyAnimalList.size(); animalindex++)
			MyAnimalList[animalindex]->move();
	}
};


int main(void)
{
	// Abstract running example

	/*
	Duck* MyDuck = new AnimalDuckAdapter(new Dog);
	MyDuck->quack();
	delete MyDuck;
	*/

	// Facace running example

	AnimalFlockFacade MyFlock;
	MyFlock.addAnimal(new Dog);
	MyFlock.addAnimal(new Cat);

	MyFlock.AllBirdsFly();

	Duck* MyDuck = &MyFlock;

	MyDuck->fly();

	return 0;

}
