#ifndef CPOINT_H
#define CPOINT_H

class cPoint
{
	public:
		cPoint ();
		cPoint (int, int);
		int point_position (cPoint, cPoint);
		
		int x;
		int y;
};

#endif
