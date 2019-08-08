#include <iostream>
#include <vector>
using namespace std;

class prepareBeverageBehaviour {
public:
	virtual void prepareDrink(void) { cout << "preparing drink" << endl; }
};

class prepareTea : public prepareBeverageBehaviour
{
public:
	void prepareDrink(void);
};

void prepareTea::prepareDrink(void)
{
	cout << "Adding Tea bag...Brewing...Adding Milk....Adding Sugar...." <<
		endl;
}

class prepareCoffee : public prepareBeverageBehaviour
{
public:
	void prepareDrink(void);
};

void prepareCoffee::prepareDrink(void)
{
	cout << "Grinding Beans...Precolating...Adding Milk... Adding Sugar...."
		<< endl;
}

class prepareFruitJuice : public prepareBeverageBehaviour
{
public:
	void prepareDrink(void);
};

void prepareFruitJuice::prepareDrink(void)
{
	cout << "Squeezing fruit and pouring juice" << endl;
}


class Beverage
{
	prepareBeverageBehaviour *pCurrentPrepareBehaviour = nullptr;

public:
	Beverage(void);
	void setprepareBehaviour(prepareBeverageBehaviour* pNewPrepareBehaviour);
	virtual void prepare(void);
	virtual void display(void) {}
};

Beverage::Beverage(void)
{
	pCurrentPrepareBehaviour = new prepareBeverageBehaviour;
}

void Beverage::prepare(void)
{
	if (pCurrentPrepareBehaviour != nullptr) pCurrentPrepareBehaviour->prepareDrink();
}

void Beverage::setprepareBehaviour(prepareBeverageBehaviour* pNewPrepareBehaviour)
{
	delete pCurrentPrepareBehaviour;
	pCurrentPrepareBehaviour = pNewPrepareBehaviour;
}



class Tea : public Beverage
{
public:
	void displya(void)
	{
		cout << "Tea" << endl;
	}
	Tea(void);

};

Tea::Tea(void)
{
	setprepareBehaviour(new prepareTea);
}

class Coffee : public Beverage
{
public :
	void display(void)
	{
		cout << "COFFEE" << endl;
	}
	Coffee(void);
};

Coffee::Coffee(void)
{
	setprepareBehaviour(new prepareCoffee);
}

class Fruitjuice : public Beverage
{
public:
	void display(void)
	{
		cout << "FRUITJUICE" << endl;
	}
	Fruitjuice(void);
};

Fruitjuice::Fruitjuice(void)
{
	setprepareBehaviour(new prepareFruitJuice);
}

class VendingMachine
{
private:
	vector<Beverage*> Drinks;
public:
	VendingMachine(void)
	{
		//construct drinks vector
		Drinks.push_back(new Tea);
		Drinks.push_back(new Coffee);
		Drinks.push_back(new Fruitjuice);
	}
	~VendingMachine(void)
	{
		// delete drinks vector
		Drinks.clear();
	}

	void displayBeverages(void)
	{
		int count = 1;

		for (int count = 1; count <= Drinks.size(); count++)
		{
			cout << count << ") ";
			Drinks[count - 1]->display();
		}
	}

	void selectBeverage(void)
	{
		int choice;
		this->displayBeverages();

		cout << "Enter choice: ";
		cin >> choice;
		if (choice > Drinks.size() || choice < 1) cout  << "Bad choice!!!" << endl;
		else Drinks[choice - 1]->prepare();
	}
};

int main(void)
{
	VendingMachine* newVendingMachine = new VendingMachine;
	newVendingMachine->displayBeverages();
	newVendingMachine->selectBeverage();
	delete newVendingMachine;


	return 0;
}
