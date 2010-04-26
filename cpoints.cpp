#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

#include <glibmm.h>

#include "cpoints.h"
#include "cpoint.h"

void cPoints::calc ()
{
	for (size_t i = 1, size = a.size(); i < size; ++i)
		if (a[0].first.x > a[i].first.x || (a[0].first.x == a[i].first.x && a[0].first.y > a[i].first.y))
			swap(a[0], a[i]);

	for (size_t i = 1, size = a.size(); i < size - 1; ++i)
	{
		size_t leftmost, rightmost;
		
		leftmost = rightmost = i;
		
		for (size_t j = i + 1; j < size; ++j)
		{
			if (a[j].first.point_position(a[i - 1].first, a[rightmost].first) == -1)
				rightmost = j;

			if (a[j].first.point_position(a[i - 1].first, a[leftmost].first) == 1)
				leftmost = j;
		}
		
		if (a[i].first.length_to(a[leftmost].first) < a[i].first.length_to(a[rightmost].first))
			swap(a[i], a[leftmost]);
		else
			swap(a[i], a[rightmost]);
	}
}

cPoint cPoints::correct_point (cPoint point, int width, int height)
{
	point.x = std::max(std::min(point.x, width - minTab), (int)minTab);
	point.y = std::max(std::min(point.y, height - minTab), (int)minTab);
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

int cPoints::read_from_file (Glib::ustring filename)
{
	std::ifstream fin(filename.c_str());

	if (!fin)
		return 0;

	int count = 0;
	
	for (float x, y; fin >> x >> y;)
		a.push_back(std::make_pair(cPoint(0, 0), cPoint(x, y)));
	
	if (a.size() == 0)
		return 0;

	int minX, maxX, minY, maxY;
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

	float indexX = infelicity / (float)(maxX - minX + minTab);
	float indexY = infelicity / (float)(maxY - minY + minTab);

	for (size_t i = 0; i < a.size(); ++i)
		a[i].first = cPoint((float)a[i].second.x * indexX, (float)a[i].second.y * indexY);
	
	return a.size();
}

void cPoints::clear ()
{
	a.clear();
}

cPoints::cPoints ()
{
}

int cPoints::size ()
{
	return a.size();
}

CPOINTS_PUSH cPoints::push (cPoints points)
{
	bool ok = true;

	for (size_t i = 0; i < points.a.size(); ++i)
	{
		for (size_t j = 0, size = a.size(); i < size; ++i)
			if (i != j && a[i].first.length_to(points.a[i].first) < minLength)
			{
				ok = false;
				break;
			}
	
		a.push_back(points.a[i]);
	}
	
	calc();
	
	return (ok) ? (CPOINTS_PUSH_OK) : (CPOINTS_PUSH_NOT_ALL);
}

CPOINTS_PUSH cPoints::push (int x, int y, int width, int height)
{
	cPoint temp((float)x / (float)width * infelicity, (float)y / (float)height * infelicity);
	
	for (size_t i = 0, size = a.size(); i < size; ++i)
		if (a[i].first.length_to(temp) < minLength)
			return CPOINTS_PUSH_NO_SPACE;

	a.push_back(std::make_pair(temp, correct_point(cPoint(x, y), width, height)));

	calc();
	
	return CPOINTS_PUSH_OK;
}

void cPoints::correct (int newWidth, int newHeight)
{
	float indexX = (float)newWidth/infelicity;
	float indexY = (float)newHeight/infelicity;

	for (size_t i = 0; i < a.size(); ++i)
		a[i].second = correct_point(cPoint((float)a[i].first.x * indexX, (float)a[i].first.y * indexY), newWidth, newHeight);
}

cPoint cPoints::operator[] (size_t index)
{
	return a[index].second;
}
