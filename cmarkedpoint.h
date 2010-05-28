#ifndef CMARKEDPOINT_H
#define CMARKEDPOINT_H

#include <iostream>
#include "defines.h"
#include "cpoint.h"

using namespace std;

class cMarkedPoint: public cPoint
{
	public:
		cMarkedPoint ();
		cMarkedPoint (int, int);
		cMarkedPoint (int, int, CMARKEDPOINT_FLAG);
		void set_flag (CMARKEDPOINT_FLAG);
		CMARKEDPOINT_FLAG get_flag ();
		friend ostream& operator<< (ostream &, cMarkedPoint);

	private:
		CMARKEDPOINT_FLAG state;		
/*	public:
		cPoint ();
		cPoint (int, int);
		float length_to (cPoint);
		float length_to (cPoint, cPoint);
		int point_position (cPoint, cPoint);
		bool operator== (cPoint);
		friend ostream& operator<< (ostream&, cPoint);

		int x;
		int y;
*/
};

#endif
