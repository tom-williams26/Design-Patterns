#include "Subject.h"

Subject::Subject(unsigned aid) : id(aid)
{
	role.setRoleName(aid);
	std::cout << "Subject created!" << std::endl;
}



unsigned Subject::getID() { return id; }

Role Subject::getRole() { return role; }

void Subject::display()
{
	std::cout << "\nSubject ID = " << id << " role = " << role.getRoleName() << std::endl;

}

Resource* Subject::getResource(int resourceID, unsigned accessType) {
	resourceFactory *rf = new resourceFactory();
	r = rf->accessResource(resourceID, role, accessType);
	delete rf;
	return r;
}
