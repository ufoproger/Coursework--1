#ifndef CPOINT_H
#define CPOINT_H

#include <iostream>

class cPoint
{
	public:
		int x;
		int y;

		cPoint ();
		cPoint (int, int);

		float length_to (cPoint);
		float length_to (cPoint, cPoint);
		int point_position (cPoint, cPoint);
		bool operator== (cPoint);

		friend std::ostream& operator<< (std::ostream&, cPoint);
};

#endif
