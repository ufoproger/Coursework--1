#ifndef CPOINTS_H
#define CPOINTS_H

#include <utility>
#include <vector>

#include <glibmm.h>

#include "cpoint.h"

class cPoints
{
	public:
		cPoints ();
		void correct (int, int);
		void clear ();
		void set_calc_rule (bool, bool);
		void calc ();
		void push (int, int, int, int);
		void push (cPoints);
		bool save_to_file (Glib::ustring);
		int read_from_file (Glib::ustring);
		int size ();
		cPoint operator[] (int);
		
	private:
		static const float infelicity = 400.0;
		static const int minTab = 7;
		int rightTurn;
		int sided;
		typedef std::vector < std::pair < cPoint , cPoint > > pointsArray;
		pointsArray a;
		
		cPoint correct_point (cPoint, int, int);
};

#endif
