#include <iostream>
#include <cmath>

#include "defines.h"
#include "cmarkedpoint.h"

cMarkedPoint::cMarkedPoint ()
{
	state = CMARKEDPOINT_FLAG_NO_SELECT;
}
/*
bool cMarkedPoint::operator== (cMarkedPoint a)
{
	return (x == a.x && y == a.y);
}
*/
ostream& operator<< (ostream & out, cMarkedPoint a)
{
	out << "(" << a.x << ", " << a.y << "; " << a.state << ")";
	
	return out;
}

cMarkedPoint::cMarkedPoint (int _x, int _y)
{
	state = CMARKEDPOINT_FLAG_NO_SELECT;
	x = _x;
	y = _y;
}

cMarkedPoint::cMarkedPoint (int _x, int _y, CMARKEDPOINT_FLAG _state)
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

/*
int cMarkedPoint::point_position (cPoint a, cMaPoint b)
{
	float t = (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x);
	return (fabs(t) < 1e-6) ? (0) : ((t > 0) ? (1) : (-1)); // -1 - справа, 0 - на его прямой и 1 - слева
}

float cMarkedPoint::length_to (cMarkedPoint a)
{
	return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
}

float cMarkedPoint::length_to (cMarkedPoint a, cMarkedPoint b)
{
	float t;
	
	if ((((x - a.x) * (b.x - a.x) + (y - a.y) * (b.y - a.y)) * ((x - b.x) * (b.x - a.x) + (y - b.y) * (b.y - a.y)) > 0))
	{
		float w = pow(x - b.x, 2) + pow(y - b.y, 2);
		t = pow(x - a.x, 2) + pow(y - a.y, 2);
		
		if (w < t)
			t = w;
	}
	else
		t = pow((x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x), 2) / (pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		
	return sqrt(t);
}
*/
