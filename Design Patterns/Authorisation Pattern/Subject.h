#pragma once

#ifndef _SUBJECT_

#include "Resource.h"
#include "Header.h"
#include "Role.h"

class Subject
{
private:
	unsigned id = 0;
	Resource* r;
	Role role;
public:
	Subject(unsigned aid);
	void display();
	unsigned getID();
	Role getRole();
	Resource* getResource(int resourceID, unsigned accessType);
};


#endif // !_SUBJECT_
