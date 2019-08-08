#include "Resource.h"

using namespace std;


Resource::Resource(int a) : id(a)
{
	secret = "bla bla bla";
}

Resource* Resource::newResource(unsigned resourceID,unsigned role, unsigned accessType) {
	Permission p = Permission();
	if (p.checkPermission(resourceID, role,accessType))
	{
		cout << "access granted\n";
		return new Resource(resourceID);
	}
	else {
		cout << "no access\n";
		return nullptr;
	}
}

int Resource::getID() { return id; }

string Resource::getSecret() { return secret; };
