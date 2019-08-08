#include <iostream>
#include <string>

using namespace std;

class Beverage
{
protected:
	string itemname = "";
	float itemcost = 0;
	string brewdetails = "";
	string boilwaterdetails = "";
public:
	virtual string name(void);
	virtual float cost();
	virtual ~Beverage(void) {};
	virtual void prepare(void);
	virtual void brew(void);
	virtual void boilwater(void);
	virtual void pour(void);
	virtual void displayOrder(void);
};

string Beverage::name(void)
{
	return this->itemname;
}

float Beverage::cost(void)
{
	return this->itemcost;
}

void Beverage::prepare(void)
{
	boilwater();
	brew();
	pour();
}

void Beverage::brew(void)
{
	cout << brewdetails << endl;
}

void Beverage::boilwater(void)
{
	cout << boilwaterdetails << endl;
}

void Beverage::pour(void)
{
	cout << "Pour!" << endl;
}

void Beverage::displayOrder(void)
{
	cout << this->name() << " Cost ";
	cout << this->cost() << endl;
}

class Espresso : public Beverage
{
public:
	Espresso(void)
	{
		itemname = "Espresso";
		itemcost = 1.2;
		brewdetails = "Filtering espresso";
		boilwaterdetails = "Heating to 90 celsius";
	}
};

class Tea : public Beverage
{
public:
	Tea(void)
	{
		itemname = "Tea";
		itemcost = 1.2;
		brewdetails = "Steeping teabag";
		boilwaterdetails = "Heating to 100 celsius";
	}
};

class CondimentDecorator : public Beverage
{
protected:
	Beverage* beverage;
	string addcondimentdetails = "";
public:
	virtual float cost(void);
	virtual string name(void);
	virtual void addCondiment(void);
	void addToBeverage(Beverage* customerBeverage);
	~CondimentDecorator(void);
	void prepare(void);
	virtual void brew(void);
	virtual void boilwater(void);
	void pour(void);
};

float CondimentDecorator::cost(void)
{
	return this->itemcost + beverage->cost();
}

string CondimentDecorator::name(void)
{
	return beverage->name() + " + " + this->itemname;
}

void CondimentDecorator::addCondiment(void)
{
	cout << addcondimentdetails << endl;
}

void CondimentDecorator::addToBeverage(Beverage *CustomerBeverage)
{
	beverage = CustomerBeverage;
}

CondimentDecorator::~CondimentDecorator(void)
{
	delete beverage;
}

void CondimentDecorator::prepare(void)
{
	beverage->prepare();
	addCondiment(); // adding a condiment makes sense here
}

void CondimentDecorator::brew(void)
{
	beverage->brew();
}

void CondimentDecorator::boilwater(void)
{
	beverage->boilwater();
}

void CondimentDecorator::pour(void)
{
	beverage->pour();
}

class Mocha : public CondimentDecorator
{
public:
	Mocha(void)
	{
		itemname = "Mocha";
		itemcost = 0.2;
		addcondimentdetails = "Adding Mocha!";
	}
};

class Cream : public CondimentDecorator
{
public:
	Cream(void)
	{
		itemname = "Cream";
		itemcost = 0.5;
		addcondimentdetails = "Adding Cream!";
	}
};


int main(void)
{
	// Decorator Pattern Implementation

	Beverage* currentBeverage = new Tea;

	currentBeverage->displayOrder();

	CondimentDecorator* currentCondiment = new Mocha;
	currentCondiment->addToBeverage(currentBeverage);
	currentBeverage = currentCondiment;
	currentBeverage->displayOrder();
	currentCondiment = new Cream;
	currentCondiment->addToBeverage(currentBeverage);
	currentBeverage = currentCondiment;
	currentBeverage->displayOrder();
	cout << endl;
	currentBeverage->prepare();

	delete currentBeverage;

	return 0;
}
