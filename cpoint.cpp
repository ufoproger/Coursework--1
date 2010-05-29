#include <iostream>
#include <cmath>

#include "cpoint.h"

cPoint::cPoint () {}

bool cPoint::operator== (cPoint a)
{
	return (x == a.x && y == a.y);
}

std::ostream& operator<< (std::ostream &out, cPoint a)
{
	out << "(" << a.x << ", " << a.y << ")";
	
	return out;
}

cPoint::cPoint (double _x, double _y)
{
	x = _x;
	y = _y;
}

int cPoint::point_position (cPoint a, cPoint b)
{
	double t = (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x);
	return (fabs(t) < 1e-6) ? (0) : ((t > 0) ? (1) : (-1)); // -1 - справа, 0 - на его прямой и 1 - слева
}

double cPoint::length_to (cPoint a)
{
	return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
}

double cPoint::length_to (cPoint a, cPoint b)
{
	double t;
	
	if (((x - a.x) * (b.x - a.x) + (y - a.y) * (b.y - a.y)) * ((x - b.x) * (b.x - a.x) + (y - b.y) * (b.y - a.y)) > 0)
	{
		double w = pow(x - b.x, 2) + pow(y - b.y, 2);
		t = pow(x - a.x, 2) + pow(y - a.y, 2);
		
		if (w < t)
			t = w;
	}
	else
		t = pow((x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x), 2) / (pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		
	return sqrt(t);
}
