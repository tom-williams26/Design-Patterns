#include <iostream>

using namespace std;

class FlyBehaviour
{
public:
	virtual void fly(void) { cout << "I fly!" << endl; };
};

class QuackBehaviour
{
public:
	virtual void quack(void) { cout << "I quack!" << endl; };
};

class FlyWithWings : public FlyBehaviour
{
	void fly(void) { cout << "Flap flap!" << endl; };
};

class NormalQuack : public QuackBehaviour
{
	void quack(void) { cout << "Quack quack!" << endl; };
};

class FlyNoWay : public FlyBehaviour
{
	void fly(void) { cout << "I do not fly!" << endl; };
};

class Squeak : public QuackBehaviour
{
	void fly(void) { cout << "Squeak squeak!" << endl; };
};


class Duck
{
private:
	FlyBehaviour *pCurrentFlyBehaviour = nullptr;
	QuackBehaviour *pCurrentQuackBehaviour = nullptr;
public:
	Duck(void);
	~Duck(void);
	virtual void quack(void);
	void swim(void);
	virtual void display(void);
	virtual void fly(void);
	void setFlyBehaviour(FlyBehaviour* pNewFlyBehaviour);
	void setQuackBehaviour(QuackBehaviour* pNewQuackBehaviour);
};

Duck::~Duck(void)
{

}

Duck::Duck(void)
{
	pCurrentFlyBehaviour = new FlyWithWings;
	pCurrentQuackBehaviour = new NormalQuack;
}

void Duck::quack(void)
{
	if (pCurrentQuackBehaviour != nullptr) pCurrentQuackBehaviour->quack();
}

void Duck::swim(void)
{
	cout << "swim swim" << endl;
}

void Duck::fly(void)
{
	if (pCurrentFlyBehaviour != nullptr) pCurrentFlyBehaviour->fly();
}

void Duck::setFlyBehaviour(FlyBehaviour *pMyFlyBehaviour)
{
	delete pCurrentFlyBehaviour;
	pCurrentFlyBehaviour = pMyFlyBehaviour;
}

void Duck::setQuackBehaviour(QuackBehaviour *pNewQuackBehaviour)
{
	delete pCurrentQuackBehaviour;
	pCurrentQuackBehaviour = pNewQuackBehaviour;
}

class MallardDuck : public Duck
{
public:
	MallardDuck(void);
	void display(void);
};


MallardDuck::MallardDuck(void)
{
	setQuackBehaviour(new NormalQuack);
	setFlyBehaviour(new FlyWithWings);
}

class RedheadDuck : public Duck
{
public:
	RedheadDuck(void);
	void display(void);
};

RedheadDuck::RedheadDuck(void)
{
	setQuackBehaviour(new NormalQuack);
	setFlyBehaviour(new FlyWithWings);
}

void Duck::display(void)
{
	cout << "I am a Duck!" << endl;
}

void MallardDuck::display(void)
{
	cout << "I am a Mallard Duck!" << endl;
}

void RedheadDuck::display(void)
{
	cout << "I am a Redhead Duck!" << endl;
}


int main(void)
{
	MallardDuck MyMallardDuck;

	MyMallardDuck.display();
	MyMallardDuck.fly();
	MyMallardDuck.setFlyBehaviour(new FlyNoWay);
	MyMallardDuck.fly();



	return 0;
}
