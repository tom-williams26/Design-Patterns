#include "Role.h"



Role::Role()
{
	userRoleAccessMap[0] = Administrator;
	userRoleAccessMap[1] = Lecturer;
	userRoleAccessMap[2] = Lecturer;
	userRoleAccessMap[3] = Student;
	userRoleAccessMap[4] = Student;
	userRoleAccessMap[5] = Student;
}

unsigned Role::getRoleName()
{
	return roleName;
}

void Role::setRoleName(unsigned subjectID)
{
	roleName = userRoleAccessMap[subjectID];
}
