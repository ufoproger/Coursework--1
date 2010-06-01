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
		
		CPOINTS_PUSH push (double, double, double, double);
		CPOINTS_PUSH push (double, double);
		CPOINTS_PUSH push (cPoints);
		cMarkedPoint& operator[] (size_t);
		size_t search_click_point (double, double);
		size_t size ();
		bool mark_point (double, double, CMARKEDPOINT_FLAG);
		bool save_to_file (Glib::ustring);
		void delete_marked_points (CMARKEDPOINT_FLAG);
		void mark_all_points (CMARKEDPOINT_FLAG);
		void correct (double, double);
		void calc_b ();
		void calc_a ();
		void clear ();
		void calc ();
		size_t read_from_file (Glib::ustring);

		friend std::ostream& operator<< (std::ostream &, cPoints);
	
	private:
		static const double infelicity = 400.0;
		static const double minLength = 20.0;
		static const double minTab = 7.0;
		bool isCalcA;

		typedef std::vector < std::pair < cPoint , cMarkedPoint > > tpPointsArray;
		
		tpPointsArray a;

		cMarkedPoint correct_point (cMarkedPoint, double, double);
		int make_sequence (tpPointsArray, tpPointsArray, int&);
		bool test_min_length_to_segment (cPoint);
		bool test_min_length_to_point (cPoint);
		bool test_crossing_lines ();
};

#endif
