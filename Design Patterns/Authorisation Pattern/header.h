#pragma once

#ifndef _RESOURCE_FACTORY_
#define _RESOURCE_FACTORY_

#include "Role.h"

class resourceFactory {
public:
	Resource* accessResource(int resourceID,Role &role, unsigned accessType)
	{
		return Resource::newResource(resourceID, role.getRoleName(), accessType);
	}
};

#endif
