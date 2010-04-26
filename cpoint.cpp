#include <cmath>

#include "cpoint.h"

cPoint::cPoint () {}

cPoint::cPoint (int _x, int _y)
{
	x = _x;
	y = _y;
}

int cPoint::point_position (cPoint a, cPoint b)
{
	float t = (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x);
	return (fabs(t) < 1e-6) ? (0) : ((t > 0) ? (1) : (-1)); // -1 - справа, 0 - на его прямой и 1 - слева
}

float cPoint::length_to (cPoint a)
{
	return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
}
