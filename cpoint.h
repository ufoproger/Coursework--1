#ifndef CPOINT_H
#define CPOINT_H

class cPoint
{
	public:
		cPoint ();
		cPoint (int, int);
		float length_to (cPoint);
		int point_position (cPoint, cPoint);
		
		int x;
		int y;
};

#endif
