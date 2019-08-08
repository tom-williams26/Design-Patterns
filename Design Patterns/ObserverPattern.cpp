#include <iostream>
#include <vector>
using namespace std;

class Subject;

class Observer
{
protected:
	Subject* pMySubject = nullptr;
public:
	virtual void setSubject(Subject*);
	virtual void removeSubject(void);
	virtual void update(void);
};

class Subject
{
protected:
	vector<Observer*> MyObservers;
	virtual bool observerExists(Observer* pObserver); // added to provide security verification
public:
	~Subject(void);
	virtual void registerObserver(Observer* pNewObserver);
	virtual void removeObserver(Observer* pObserverToRemove);
	virtual void notifyObservers(void);
};

void Observer::setSubject(Subject* pCurrentSubject)
{
	this->pMySubject = pCurrentSubject;
}

void Observer::removeSubject(void)
{
	pMySubject->removeObserver(this);
	pMySubject = nullptr;
}

void Observer::update(void)
{

}

Subject::~Subject(void)
{
	MyObservers.clear();
}

void Subject::registerObserver(Observer* pNewObserver)
{
	pNewObserver->setSubject(this);
	MyObservers.push_back(pNewObserver);
}

void Subject::removeObserver(Observer* pObserverToRemove)
{
	for (int observercount = 0; observercount < MyObservers.size(); observercount++)
	{
		if (MyObservers[observercount] == pObserverToRemove)
		{
			MyObservers.erase(MyObservers.begin() + observercount);
			return;
		}
	}
}

bool Subject::observerExists(Observer* pObserver)
{
	if (pObserver == nullptr) return false;

	for (int observercount = 0; observercount < MyObservers.size(); observercount++)
	{
		if (MyObservers[observercount] == pObserver)
		{
			return true;
		}
	}
	return false;
}

void Subject::notifyObservers(void)
{
	for (int observercount = 0; observercount < MyObservers.size(); observercount++)
	{
		MyObservers[observercount]->update();
	}
}


class WeatherStation : public Subject
{
private:
	float humidity = 0, temperature = 0, pressure = 0;
public:
	void setWeatherValues(float newHumidity, float newTemperature, float newPressure);
	float getHumidity(void);
	float getTemperature(void);
	float getPressure(void);

};

void WeatherStation::setWeatherValues(float newHumidity, float newTemperature, float newPressure)
{
	humidity = newHumidity;
	temperature = newTemperature;
	pressure = newPressure;
}

float WeatherStation::getHumidity(void)
{
	return humidity;
}

float WeatherStation::getTemperature(void)
{
	return temperature;
}

float WeatherStation::getPressure(void)
{
	return pressure;
}

class WeatherClient : public Observer
{
	void update(void);
};

void WeatherClient::update(void)
{
	WeatherStation* WeatherData = (WeatherStation*)pMySubject;

	cout << "Humidity = " << WeatherData->getHumidity() << " : Temperature = " <<
		WeatherData->getTemperature() << " : Pressure = " <<
		WeatherData->getPressure();
}

int main(void)
{

	// Observer Pattern implementation
	WeatherStation* NewWeatherStation = new WeatherStation;
	WeatherClient* NewWeatherClient = new WeatherClient;

	NewWeatherStation->registerObserver(NewWeatherClient);
	NewWeatherStation->notifyObservers();
	NewWeatherStation->setWeatherValues(20, 20, 20);
	NewWeatherStation->notifyObservers();

	NewWeatherClient->removeSubject();

	NewWeatherStation->notifyObservers();

	delete NewWeatherClient;
	delete NewWeatherStation;

	return 0;

}
