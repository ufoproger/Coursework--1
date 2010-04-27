#ifndef CPOINT_H
#define CPOINT_H

#include <iostream>

using namespace std;

class cPoint
{
	public:
		cPoint ();
		cPoint (int, int);
		float length_to (cPoint);
		float length_to (cPoint, cPoint);
		int point_position (cPoint, cPoint);
		bool operator== (cPoint);
		friend ostream& operator<< (ostream&, cPoint);

		int x;
		int y;
};

#endif
