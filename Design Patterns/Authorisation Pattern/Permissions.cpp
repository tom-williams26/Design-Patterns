#include "Permissions.h"


using namespace std;

/*
 FA - FULL ACCESS
 E - EXECUTE
 R - READ
 W - WRITE
 NA - NO ACCESS
*/

Permission::Permission()
{
	//resourcceID							  0   1   2   3   4   5
	userResourceAccessMap[Administrator] = { FA, FA, FA, FA, FA, FA };
	userResourceAccessMap[Lecturer] = { E | W, E | W | R, E | W | R, E, E, E };
	userResourceAccessMap[Student] = { E|W, E|W|R,E | W | R, E,E,E };

}

bool Permission::checkPermission(unsigned resourceID, unsigned role, unsigned accessType)
{
	if (userResourceAccessMap[role].at(resourceID) & accessType)  return true;
	else return false;
}
