#ifndef CMARKEDPOINT_H
#define CMARKEDPOINT_H

#include "defines.h"
#include "cpoint.h"

class cMarkedPoint: public cPoint
{
	public:
		cMarkedPoint ();
		cMarkedPoint (double, double);
		cMarkedPoint (double, double, CMARKEDPOINT_FLAG);

		CMARKEDPOINT_FLAG get_flag ();
		void set_flag (CMARKEDPOINT_FLAG);

	private:
		CMARKEDPOINT_FLAG state;
};

#endif
