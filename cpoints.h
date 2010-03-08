#ifndef CPOINTS_H
#define CPOINTS_H

#include <utility>
#include <vector>
#include <gtkmm.h>

struct sPoint
{
	int x;
	int y;
	
	sPoint (int _x, int _y) : x(_x), y(_y) {}
};

class cPoints
{
	public:
		cPoints ();
		void correct (int, int);
		void clear ();
		void push (int, int, int, int);
		void push (cPoints);
		bool save_to_file (Glib::ustring);
		int read_from_file (Glib::ustring);
		int size ();
		sPoint operator[] (int);
		
	private:
		static const float infelicity = 400.0;
		static const int minTab = 7;
		typedef std::vector < std::pair < sPoint , sPoint > > pointsArray;
		pointsArray a;
		
		sPoint correct_point (sPoint, int, int);
};

#endif
