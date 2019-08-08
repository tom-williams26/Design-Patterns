#include <iostream>
#include <map>
#include <string>
using namespace std;

enum commandType {on, off, increaseSpeed};
enum receiverType {r_fan, r_light};
enum trust { COMPLETE, LITTLE};

const unsigned COMMANDS_NO = 4;


class TrustLevel
{
public:
	trust level;
};

class Subject
{
private:
	int ipAddr;
	TrustLevel trustLevel;
public:
	Subject(int newIpAddr, TrustLevel trust)
	{
		ipAddr = newIpAddr;
		trustLevel = trust;
	}
	TrustLevel getTrustLevel()
	{
		return trustLevel;
	}
	TrustLevel getTrustLevel() const { return trustLevel; }
	int getIpAddr() const { return ipAddr; }
};


class Receiver
{
public:
	virtual void on() = 0;
	virtual void off() = 0;
};

class Light : public Receiver
{
	int intensity;
public:
	void on()
	{
		intensity = 50;
		cout << "The light is on, intensity =" << intensity << "\n";
	}
	void off()
	{
		cout << "The light is off\n";
	}
};


class Fan : public Receiver
{
	int speed;
public:
	void on()
	{
		speed = 80;
		cout << "Fan is on, speed =" << speed << "\n";
	}
	void off()
	{
		cout << "Fan is off\n";
	}
	void increaseSpeed()
	{

		cout << "Speed increase \n";
	}

};


class CommandChecker
{
private:
	map<string, trust> commands;
	bool checkCredentials(TrustLevel l, string calledMethodName)
	{
		map<string, trust>::iterator it = commands.find(calledMethodName);
		if (it != commands.end()) {
			trust t = it->second;
			if (l.level >= t) {
				return true;
			}
			else {
				return false;
			}
		}
		else return false;
	}
public:
	CommandChecker()
	{
		commands["OnCommand"] = { COMPLETE };
		commands["OffCommand"] = { LITTLE };
	}
	virtual bool accessAllowed(const Subject client, string calledMethodName)
	{
		if (!(checkCredentials(client.getTrustLevel(), calledMethodName)))
		{
			string reason = string("") + "The client trust level ("
				+ to_string(client.getTrustLevel().level) + ") is not " +
				"sufficent to execute method " + calledMethodName;
			cout << reason << endl;
			return false;
		}
		else return true;
	}
};

class Command
{

public:
	string name = " ";
	virtual void execute() = 0;
};

class OnCommand : public Command
{
private:
	Receiver *mReceiver;
public:
	OnCommand(Receiver *receiver) : mReceiver(receiver) {}

	void execute()
	{
		mReceiver->on();
	}
};

class OffCommand : public Command
{
private:
	Receiver *mReceiver;
public:
	OffCommand(Receiver *receiver) : mReceiver(receiver) {}
	void execute()
	{
		mReceiver->off();
	}
};

class FanSpeedIncrease : public Command
{
private:
	Receiver * mReceiver;
public:
	FanSpeedIncrease(Receiver *receiver) :
		mReceiver(receiver) {}
	void execute()
	{
		(dynamic_cast<Fan*>(mReceiver))->increaseSpeed();
	}
};

class RemoteControl
{
private:
	Command * mCmd[COMMANDS_NO];
	CommandChecker cmdChecker;
public:
	void setCommand(int slot, Command *cmd)
	{
		mCmd[slot] = cmd;
	}

	void buttonPressed(int slot, const Subject client)
	{
		if(cmdChecker.accessAllowed(client, mCmd[slot]->name))
		{
		cout << "command " << slot << " executed ";
		mCmd[slot]->execute();
		}
	}

};



int main(void)
{
	TrustLevel t;
	t.level = COMPLETE; // COMPLETE, LITTLE
	Subject client(1, t);

	Receiver *receivers[] = { new Light, new Fan };
	Command *commands[COMMANDS_NO] =
	{
		new OnCommand(receivers[r_fan]),
		new OffCommand(receivers[r_fan]),
		new OnCommand(receivers[r_light]),
		new OffCommand(receivers[r_light])
	};

	RemoteControl *control = new RemoteControl;

	for (int i = 0; i < COMMANDS_NO; i++)
		control->setCommand(i, commands[i]);

	for (int i = 0; i < COMMANDS_NO; i++)
		control->buttonPressed(i, client);



	cout << '\n';
	system("pause");


	return 0;
}
