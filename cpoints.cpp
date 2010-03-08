#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <gtkmm.h>

#include "cpoints.h"

sPoint cPoints::correct_point (sPoint point, int width, int height)
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

	for (pointsArray::iterator it = a.begin(); it != a.end(); ++it)
		fout << it->first.x << " " << it->first.y << std::endl;
		
	return true;
}

int cPoints::read_from_file (Glib::ustring filename)
{
	std::ifstream fin(filename.c_str());

	if (!fin)
		return 0;

	int count = 0;
	
	for (float x, y; fin >> x >> y;)
		a.push_back(std::make_pair(sPoint(0, 0), sPoint(x, y)));
	
	if (a.size() == 0)
		return 0;

	int minX, maxX, minY, maxY;
	minX = maxX = a[0].second.x;
	minY = maxY = a[0].second.y; 
	
	for (pointsArray::iterator it = a.begin() + 1; it != a.end(); ++it)
	{
		minX = std::min(minX, it->second.x);
		minY = std::min(minY, it->second.y);
		maxX = std::max(maxX, it->second.x);
		maxY = std::max(maxY, it->second.y);
	}
	
	minX -= minTab;
	minY -= minTab;

	if (minX < 0)
		for (pointsArray::iterator it = a.begin() + 1; it != a.end(); ++it)
			it->second.x -= minX;

	if (minY < 0)
		for (pointsArray::iterator it = a.begin() + 1; it != a.end(); ++it)
			it->second.y -= minY;
			
	minX = minY = 0;

	float indexX = infelicity / (float)(maxX - minX + minTab);
	float indexY = infelicity / (float)(maxY - minY + minTab);

	for (pointsArray::iterator it = a.begin(); it != a.end(); ++it)
		it->first = sPoint((float)it->second.x * indexX, (float)it->second.y * indexY);
	
	return a.size();
}

void cPoints::clear ()
{
	a.clear();
}

cPoints::cPoints () {}

int cPoints::size ()
{
	return a.size();
}

void cPoints::push (cPoints points)
{
	for (pointsArray::iterator it = points.a.begin(); it != points.a.end(); ++it)
		a.push_back(*it);
}

void cPoints::push (int x, int y, int width, int height)
{
	a.push_back(std::make_pair(sPoint((float)x / (float)width * infelicity, (float)y / (float)height * infelicity), correct_point(sPoint(x, y), width, height)));
}

void cPoints::correct (int newWidth, int newHeight)
{
	float indexX = (float)newWidth/infelicity;
	float indexY = (float)newHeight/infelicity;

	for (pointsArray::iterator it = a.begin(); it != a.end(); ++it)
		it->second = correct_point(sPoint((float)it->first.x * indexX, (float)it->first.y * indexY), newWidth, newHeight);
}

sPoint cPoints::operator[] (int index)
{
	return a[index].second;
}
