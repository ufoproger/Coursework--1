#include <cmath>

#include "cpoint.h"

int cPoint::calc_point_pos (cPoint a, cPoint b)
{
	float t = (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x);
	return (fabs(t) < 1e-6) ? (0) : ((t > 0) ? (1) : (-1)); // -1 - справа, 0 - на его прямой и 1 - слева
}

cPoint::cPoint () {}
cPoint::cPoint (int _x, int _y)
{
	x = _x;
	y = _y;
}
