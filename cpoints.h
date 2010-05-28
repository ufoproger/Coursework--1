#ifndef CPOINTS_H
#define CPOINTS_H

#include <utility>
#include <vector>

#include <glibmm.h>

#include "cmarkedpoint.h"
#include "defines.h"
#include "cpoint.h"

class cPoints
{
	public:
		cPoints ();
		CPOINTS_PUSH push (int, int, int, int);
		CPOINTS_PUSH push (cPoints);
		size_t search_click_point (int, int);
		bool mark_point (int, int, CMARKEDPOINT_FLAG);
		bool save_to_file (Glib::ustring);
		void delete_marked_points (CMARKEDPOINT_FLAG);
		void mark_all_points (CMARKEDPOINT_FLAG);
		void correct (int, int);
		void calc_r ();
		void clear ();
		void calc ();
		int read_from_file (Glib::ustring);
		int size ();
		cMarkedPoint& operator[] (size_t);
		friend ostream& operator<< (ostream &, cPoints);
	
	private:
		static const float infelicity = 400.0;
		static const float minLength = 20.0;
		static const bool is_calc_r = true;
		static const int minTab = 7;

		typedef std::vector < std::pair < cPoint , cMarkedPoint > > tpPointsArray;
		
		tpPointsArray a;
		std::vector < bool > color;

		cMarkedPoint correct_point (cMarkedPoint, int, int);
		bool make_sequence (tpPointsArray, tpPointsArray);
		bool test_min_length_to_segment (cPoint);
		bool test_min_length_to_point (cPoint);
		bool test_crossing_lines ();
};

#endif
