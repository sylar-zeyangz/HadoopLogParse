#ifndef ___TimeOperator_H___
#define ___TimeOperator_H___

#include "SystemTime.h"
#include <iostream> 
#include "C_Debug.h"

namespace TimeOperator
{
	SYSTEM_TIME ToSystemTime( std::string _s );
	int TimeSubtraction(SYSTEM_TIME _a, SYSTEM_TIME _b);
}

#endif //___TimeOperator_H___

