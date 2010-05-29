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
		
//		cPoints& operator= (cPoints &);
		CPOINTS_PUSH push (double, double, double, double);
		CPOINTS_PUSH push (cPoints);
		cMarkedPoint& operator[] (size_t);
		size_t search_click_point (double, double);
		bool mark_point (double, double, CMARKEDPOINT_FLAG);
		bool save_to_file (Glib::ustring);
		void delete_marked_points (CMARKEDPOINT_FLAG);
		void mark_all_points (CMARKEDPOINT_FLAG);
		void correct (double, double);
		void clear ();
		void calc ();
		int read_from_file (Glib::ustring);
		size_t size ();

		friend std::ostream& operator<< (std::ostream &, cPoints);
	
	private:
		static const double infelicity = 400.0;
		static const double minLength = 20.0;
		static const int minTab = 7;

		typedef std::vector < std::pair < cPoint , cMarkedPoint > > tpPointsArray;
		
		tpPointsArray a;

		cMarkedPoint correct_point (cMarkedPoint, double, double);
		bool make_sequence (tpPointsArray, tpPointsArray);
		bool test_min_length_to_segment (cPoint);
		bool test_min_length_to_point (cPoint);
		bool test_crossing_lines ();
};

#endif
