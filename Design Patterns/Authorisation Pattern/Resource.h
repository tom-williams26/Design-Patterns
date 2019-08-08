#pragma once

#ifndef _RESOURCE_
#define _RESOURCE_

#include <iostream>
#include <string>




class Resource
{
private:
	int id = 0;
	std::string secret;
	Resource(int a);
public:
	static Resource* newResource(unsigned resourceID, unsigned role, unsigned accessType);
	int getID();
	std::string getSecret();
};

#include "Permissions.h"


#endif
