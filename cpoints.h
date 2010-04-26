#ifndef CPOINTS_H
#define CPOINTS_H

#include <utility>
#include <vector>

#include <glibmm.h>

#include "defines.h"
#include "cpoint.h"

class cPoints
{
	public:
		cPoints ();
		void correct (int, int);
		void clear ();
		void calc ();
		CPOINTS_PUSH push (int, int, int, int);
		CPOINTS_PUSH push (cPoints);
		bool save_to_file (Glib::ustring);
		int read_from_file (Glib::ustring);
		int size ();
		cPoint operator[] (size_t);
		
	private:
		static const float infelicity = 400.0;
		static const float minLength = 10.0;
		static const int minTab = 7;
		std::vector < std::pair < cPoint , cPoint > > a;
		
		cPoint correct_point (cPoint, int, int);
};

#endif
