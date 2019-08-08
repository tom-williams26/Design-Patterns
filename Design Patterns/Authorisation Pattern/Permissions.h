#pragma once

#ifndef _PERMISSIONS_
#define _PERMISSIONS_

#include <map>
#include <vector>

#include "Resource.h"

enum AccessType {
	NA = 0x00,  //00000
	CO = 0x01,  //00001
	E = 0x02,   //00010
	W = 0x04,   //00100
	R = 0x08,   //01000
	FA = 0x10   //10000
};

enum Roles { Administrator, Lecturer, Student };

class Permission {
private:
	typedef std::vector<unsigned> resources;
	std::map<int, resources> userResourceAccessMap;
public:
	Permission();
	bool checkPermission(unsigned resourceID, unsigned role, unsigned accessType);

};

#endif
