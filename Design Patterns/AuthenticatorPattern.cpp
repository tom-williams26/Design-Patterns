#include <iostream>
#include <string>
#include <map>
using namespace std;

#pragma region proofofID_Class
class ProofofID
{
private:
	string proofID;
public:
	ProofofID() {};
	ProofofID(string aproofID);
	string getproofID();
	void setproofID(string aproofID);
};

string ProofofID::getproofID()
{
	return proofID;
};

void ProofofID::setproofID(string aproofID)
{
	proofID = aproofID;
};

ProofofID::ProofofID(string aproofID) : proofID(aproofID) { };
#pragma endregion

#pragma region Subject_Class
class Subject
{
private:
	string id;
	string password;
	string proofID;
public:
	Subject(string a, string pass);
	Subject();
	string getID();
	string getPassword();
	void setproofofID(string proof);
	string getproofofID();
};

Subject::Subject(string aId, string apass) : id(aId), password(apass) {}

Subject::Subject()
{
	cout << "\nEnter UserID :";
	cin >> id;
	cout << "\nEnter password :";
	cin >> password;
}

string Subject::getID() { return id; };
string Subject::getPassword() { return password; };

void Subject::setproofofID(string proof)
{
	proofID = proof;
}

string Subject::getproofofID()
{
	return proofID;
}
#pragma endregion

#pragma region AuthenticationInfo_Calss
//AuthenticationInfo class
class AuthenticationInfo
{
private:
	map<string, string> Users;

public:
	AuthenticationInfo(); // consutrctor sets attributes
	bool validateUser(string name, string password);
};

AuthenticationInfo::AuthenticationInfo()
{
	Users.insert(pair<string, string>("Jamie", "123"));
};

bool AuthenticationInfo::validateUser(string name, string password)
{
	bool validUser = false;
	map<string, string>::iterator it;

	it = Users.find(name);

	if (it != Users.end()) {
		if (!(it->second.compare(password)))
		{
			validUser = true;
		}
	}
	return validUser;
}
#pragma endregion

#pragma region Authenticator
// Authenticator class
class Authenticator
{
public:
	Authenticator();
	ProofofID* authenticateUser(Subject &s);
private:
	string encryptDecrypt(string toEncrypt);
};

Authenticator::Authenticator() {};

ProofofID* Authenticator::authenticateUser(Subject &s)
{
	AuthenticationInfo ainfo;
	ProofofID *proofofID = nullptr;
	string Id = s.getID();
	string pass = s.getPassword();
	string token = " ";

	if (ainfo.validateUser(Id, pass))
	{
		cout << "\nWelcome";
		cout << "\nAuthenticated!\n";
		token = encryptDecrypt(Id + pass);
		proofofID = new ProofofID(token);
		s.setproofofID(token);
	}
	else cout << "Invalid user ID or password. Please try again.";

	return proofofID;
}

string Authenticator::encryptDecrypt(string toEncrypt)
{
	char key = 'A'; //Any char will work
	string output = toEncrypt;
	for (unsigned i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;
	return output;
}

#pragma endregion


int main(void)
{
	unsigned userExited = 0;

	while (!userExited)
	{
		Subject s;
		Authenticator a;
		ProofofID *proofofID = a.authenticateUser(s);
		if(proofofID != nullptr)
		{
			cout << "Subject proof of id :" << s.getproofofID() << endl;
			cout << "system proof of id :" << proofofID->getproofID() << endl;
		}

		cout << "\nExit Yes = 1, No - 0 : ";
		cin >> userExited;
	}

	system("pause");


	return 0;
}
