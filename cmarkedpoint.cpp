#include <iostream>
#include <cmath>

#include "cmarkedpoint.h"
#include "defines.h"

cMarkedPoint::cMarkedPoint ()
{
	state = CMARKEDPOINT_FLAG_NO_SELECT;
}

std::ostream& operator<< (std::ostream & out, cMarkedPoint a)
{
	out << "(" << a.x << ", " << a.y << "; " << a.state << ")";
	
	return out;
}

cMarkedPoint::cMarkedPoint (double _x, double _y)
{
	state = CMARKEDPOINT_FLAG_NO_SELECT;
	x = _x;
	y = _y;
}

cMarkedPoint::cMarkedPoint (double _x, double _y, CMARKEDPOINT_FLAG _state)
{
	state = _state;
	x = _x;
	y = _y;
}

void cMarkedPoint::set_flag (CMARKEDPOINT_FLAG _state)
{
	state = _state;
}

CMARKEDPOINT_FLAG cMarkedPoint::get_flag ()
{
	return state;
}
