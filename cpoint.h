#ifndef CPOINT_H
#define CPOINT_H

#include <iostream>

class cPoint
{
	public:
		double x;
		double y;

		cPoint ();
		cPoint (double, double);

		double length_to (cPoint);
		double length_to (cPoint, cPoint);
		int point_position (cPoint, cPoint);
		bool operator== (cPoint);

		friend std::ostream& operator<< (std::ostream&, cPoint);
};

#endif
