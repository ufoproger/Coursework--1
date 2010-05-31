#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

#include <glibmm.h>

#include "cpoints.h"
#include "cpoint.h"

size_t cPoints::search_click_point (double x, double y)
{
	cPoint temp(x, y);

	for (size_t i = 0, size = a.size(); i < size; ++i)
		if (a[i].second.length_to(temp) < 7.0)
			return (i + 1);

	return 0;
}

void cPoints::mark_all_points (CMARKEDPOINT_FLAG state)
{
	for (size_t i = 0, size = a.size(); i < size; ++i)
		a[i].second.set_flag(state);
}

void cPoints::delete_marked_points (CMARKEDPOINT_FLAG state)
{
	for (bool ok = true; ok;)
	{
		ok = false;
		
		for (size_t i = 0, size = a.size(); i < size; ++i)
			if (a[i].second.get_flag() == state)
			{
				a.erase(a.begin() + i);
				ok = true;
				break;
			}
	}
}

std::ostream& operator<< (std::ostream & out, cPoints a)
{
	for (size_t i = 0, size = a.size(); i < size; ++i)
		out << a.a[i].second << " ";
		
	out << std::endl;
 
	return out;
}

template < typename T >
bool in_range (T x, T l, T r)
{
	return (l <= x && x <= r);	
}

bool crossing (cPoint point11, cPoint point12, cPoint point21, cPoint point22)
{
    double denominator = (point12.y - point11.y) * (point21.x - point22.x) - (point21.y - point22.y) * (point12.x - point11.x);
    double numeratorA = (point12.y - point11.y) * (point21.x - point11.x) - (point21.y - point11.y) * (point12.x - point11.x);
    double numeratorB = (point21.y - point11.y) * (point21.x - point22.x) - (point21.y - point22.y) * (point21.x - point11.x);

    if(!denominator)
    	return (!numeratorA && !numeratorB);

	return (in_range(numeratorA/denominator, 0.0, 1.0) && in_range(numeratorB/denominator, 0.0, 1.0));
}

bool cPoints::test_crossing_lines ()
{
	for (size_t i = 1, size = a.size(); i + 2 < size; ++i)
		for (size_t j = i + 2; j < size; ++j)
			if (crossing(a[i - 1].first, a[i].first, a[j - 1].first, a[j].first))
				return false;
				
	return true;
}

bool cPoints::test_min_length_to_segment (cPoint point)
{
	for (size_t i = 1, size = a.size(); i < size; ++i)
		if (point.length_to(a[i - 1].first, a[i].first) < minLength)
			return false;
	
	return true;
}

bool cPoints::test_min_length_to_point (cPoint point)
{
	for (size_t i = 0, size = a.size(); i < size; ++i)
		if (point.length_to(a[i].first) < minLength)
			return false;
			
	return true;
}

#ifdef USE_CALC_R
bool cPoints::make_sequence (tpPointsArray source, tpPointsArray result)
{
	if (source.empty())
	{
		a = result;

		if (!test_crossing_lines())
			return false;

		for (size_t i = 0, size = a.size(); i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
				if (i != j && a[i].first.length_to(a[j].first) < minLength)
					return false;
					
			for (size_t j = 1; j < size; ++j)
				if (i != j && i != j - 1 && a[i].first.length_to(a[j].first, a[j - 1].first) < minLength)
					return false;							
		}

		return true;		
	}

	for (size_t k = 0, size = source.size(); k < size; ++k)
	{
		tpPointsArray temp = source;

		result.push_back(temp[k]);	
		temp.erase(temp.begin() + k);

		a = result;

		if (!test_crossing_lines())
			continue;

		bool ok = true;

		for (size_t i = 0, size = a.size(); i < size; ++i)
		{
			for (size_t j = 0; j < size && ok; ++j)
				if (i != j && a[i].first.length_to(a[j].first) < minLength)
					ok = false;
		
			for (size_t j = 1; j < size && ok; ++j)
				if (i != j && i != j - 1 && a[i].first.length_to(a[j].first, a[j - 1].first) < minLength)
					ok = false;
		}
		
		if (!ok)
			continue;
			
		bool f = make_sequence(temp, result);
		
		result.pop_back();

		if (f)
			return true;
	}
	
	return false;
}

void cPoints::calc ()
{
	tpPointsArray temp = a;
	
	bool f = make_sequence(a, tpPointsArray());
	
	if (!f)
		a = temp;
}

#else

void cPoints::calc ()
{
	for (size_t i = 1, size = a.size(); i < size; ++i)
		if (a[0].first.x > a[i].first.x || (a[0].first.x == a[i].first.x && a[0].first.y > a[i].first.y))
			swap(a[0], a[i]);

	for (size_t i = 1, size = a.size(); i < size - 1; ++i)
	{
		size_t rightmost = i;

		for (size_t j = i + 1; j < size; ++j)
		{
			if (a[j].first.point_position(a[i - 1].first, a[rightmost].first) == -1)
				rightmost = j;
		}
			swap(a[i], a[rightmost]);
	}
	
	std::vector < cPoint > b;

	for (bool f = true; f; )
	{
		f = false;
		
		for (size_t i = 0, size = a.size(); i < size; ++i)
		{
			for (size_t j = 0; j < size - 1; ++j)
			{
				if (i == j || i == j + 1)
					continue;
					
				if (a[i].first.length_to(a[j].first, a[j + 1].first) < 20.0 && find(b.begin(), b.end(), a[j].first) == b.end() && find(b.begin(), b.end(), a[j + 1].first) == b.end() && find(b.begin(), b.end(), a[i].first) == b.end())
				{
					b.push_back(a[i].first);

					tpPointsArray temp = a;
				
					if (i < j)
					{
						a.insert(a.begin() + j + 1, a[i]);
						a.erase(a.begin() + i);
					}
					else
					{
						a.insert(a.begin() + j + 1, a[i]);
						a.erase(a.begin() + i + 1);
					}
					
					if (!(f = test_crossing_lines()))
						a = temp;

					break;
				}
			}
		}
	}
}

#endif

cMarkedPoint cPoints::correct_point (cMarkedPoint point, double width, double height)
{
	point.x = std::max(std::min(point.x, width - minTab), (double)minTab);
	point.y = std::max(std::min(point.y, height - minTab), (double)minTab);

	return point;
}

bool cPoints::save_to_file (Glib::ustring filename)
{
	if (filename.find_last_of(".txt") != filename.length() - 1)
		filename += ".txt";
	
	std::ofstream fout(filename.c_str());
	if (!fout)
		return false;

	for (size_t i = 0; i < a.size(); ++i)
		fout << a[i].first.x << " " << a[i].first.y << std::endl;
		
	return true;
}

bool cPoints::mark_point (double x, double y, CMARKEDPOINT_FLAG state)
{
	size_t i;
	
	if (i = search_click_point(x, y))
		a[i - 1].second.set_flag(state);

	return i;
}

int cPoints::read_from_file (Glib::ustring filename)
{
	std::ifstream fin(filename.c_str());

	if (!fin)
		return 0;

	int count = 0;
	
	for (double x, y; fin >> x >> y;)
		a.push_back(std::make_pair(cPoint(0, 0), cMarkedPoint(x, y)));
	
	if (a.size() == 0)
		return 0;

	double minX, maxX, minY, maxY;
	
	minX = maxX = a[0].second.x;
	minY = maxY = a[0].second.y; 
	
	for (size_t i = 1; i < a.size(); ++i)
	{
		minX = std::min(minX, a[i].second.x);
		minY = std::min(minY, a[i].second.y);
		maxX = std::max(maxX, a[i].second.x);
		maxY = std::max(maxY, a[i].second.y);
	}
	
	minX -= minTab;
	minY -= minTab;

	if (minX < 0)
		for (size_t i = 1; i < a.size(); ++i)
			a[i].second.x -= minX;

	if (minY < 0)
		for (size_t i = 1; i < a.size(); ++i)
			a[i].second.y -= minY;
			
	minX = minY = 0;

	double indexX = infelicity / (double)(maxX - minX + minTab);
	double indexY = infelicity / (double)(maxY - minY + minTab);

	for (size_t i = 0; i < a.size(); ++i)
		a[i].first = cPoint((double)a[i].second.x * indexX, (double)a[i].second.y * indexY);
	
	return a.size();
}

void cPoints::clear ()
{
	a.clear();
}

cPoints::cPoints () {}

size_t cPoints::size ()
{
	return a.size();
}

CPOINTS_PUSH cPoints::push (cPoints points)
{
	bool ok = true;

	for (size_t i = 0; i < points.a.size(); ++i)
	{
		if (test_min_length_to_point(points.a[i].first))
			a.push_back(points.a[i]);
		else
			ok = false;
	}
	
	calc();
	
	return (ok) ? (CPOINTS_PUSH_OK) : (CPOINTS_PUSH_NOT_ALL);
}

CPOINTS_PUSH cPoints::push (double x, double y, double width, double height)
{
	cPoint temp(x / width * infelicity, y / height * infelicity);
	
	for (size_t i = 0, size = a.size(); i < size; ++i)
		if (a[i].first.length_to(temp) < minLength)
			return CPOINTS_PUSH_NO_SPACE;

	a.push_back(std::make_pair(temp, correct_point(cMarkedPoint(x, y), width, height)));

	calc();
	
	return CPOINTS_PUSH_OK;
}

CPOINTS_PUSH cPoints::push (double x, double y)
{
	cPoint temp(x, y);
	
	for (size_t i = 0, size = a.size(); i < size; ++i)
		if (a[i].first.length_to(temp) < 1e-6)
			return CPOINTS_PUSH_NO_SPACE;

	a.push_back(std::make_pair(temp, cMarkedPoint(x, y)));

	calc();
	
	return CPOINTS_PUSH_OK;
}

void cPoints::correct (double newWidth, double newHeight)
{
	double indexX = newWidth/infelicity;
	double indexY = newHeight/infelicity;

	for (size_t i = 0; i < a.size(); ++i)
		a[i].second = correct_point(cMarkedPoint(a[i].first.x * indexX, a[i].first.y * indexY, a[i].second.get_flag()), newWidth, newHeight);
}

cMarkedPoint& cPoints::operator[] (size_t index)
{
	return a[index].second;
}
