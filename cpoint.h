#ifndef CPOINT_H
#define CPOINT_H
/*
struct sPoint
{
	int x;
	int y;
	
	sPoint (int _x, int _y) : x(_x), y(_y) {}
};
*/
class cPoint
{
	public:
		cPoint ();
		cPoint (int, int);
		int calc_point_pos (cPoint, cPoint);
		
		int x;
		int y;
};

typedef cPoint sPoint;

#endif
