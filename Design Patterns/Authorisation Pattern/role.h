
#pragma once

#ifndef Role

#include <map>

#include "Permissions.h"

class Role
{
private:
unsigned roleName;
std::map<unsigned, unsigned> userRoleAccessMap;
public:
Role();
unsigned getRoleName();
void setRoleName(unsigned subjectID);
};

#endif // !Role
