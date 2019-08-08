#include <iostream>
#include <map>
#include <string>



using namespace std;


#include "Resource.h"
#include "Subject.h"
#include "Header.h"
#include "Role.h"
int main(void)
{
	int subjectID = 1;
	int resourceID = 3; // E|W|R
	unsigned accessType = E;

	Subject *s = new Subject(subjectID);
	s->display();
	Resource *r = s->getResource(resourceID, accessType);

	if(r != nullptr) cout << "\nscret = " << r->getSecret() << endl;
	cout << endl;

	system("pause");

	return 0;
}
