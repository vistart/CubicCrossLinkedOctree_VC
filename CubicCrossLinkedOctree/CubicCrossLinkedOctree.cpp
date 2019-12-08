/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __CUBIC_CROSS_LINKED_OCTREE_H__
#include "CubicCrossLinkedOctree.h"
#endif

#ifdef __CUBIC_CROSS_LINKED_OCTREE_H__
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;
CubicCrossLinkedOctree::CubicCrossLinkedOctree()
{

}

CubicCrossLinkedOctree::CubicCrossLinkedOctree(shared_ptr<PlyVertexList> point_list)
{
    auto comp_x = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::X); };
    auto comp_y = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Y); };
    auto comp_z = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Z); };
    auto begin = point_list->points.begin();
    auto end = point_list->points.end();
    auto x_min = min_element(begin, end, comp_x);
    auto x_max = max_element(begin, end, comp_x);
    auto y_min = min_element(begin, end, comp_y);
    auto y_max = max_element(begin, end, comp_y);
    auto z_min = min_element(begin, end, comp_z);
    auto z_max = max_element(begin, end, comp_z);
    cout << "X-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, x_min) << "]" << setprecision(8) << (*x_min).X() << endl;
    cout << "X-axis highest boundry: " << setprecision(0) << "[" << distance(begin, x_max) << "]" << setprecision(8) << (*x_max).X() << endl;
    cout << "Y-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, y_min) << "]" << setprecision(8) << (*y_min).Y() << endl;
    cout << "Y-axis highest boundry: " << setprecision(0) << "[" << distance(begin, y_max) << "]" << setprecision(8) << (*y_max).Y() << endl;
    cout << "Z-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, z_min) << "]" << setprecision(8) << (*z_min).Z() << endl;
    cout << "Z-axis highest boundry: " << setprecision(0) << "[" << distance(begin, z_max) << "]" << setprecision(8) << (*z_max).Z() << endl;
}

CubicCrossLinkedOctree::~CubicCrossLinkedOctree()
{

}

bool CubicCrossLinkedOctree::compare_coordination_X(Point a, Point b)
{
    return a.is_less_than(b, Point::Coordination::X);
}
bool CubicCrossLinkedOctree::compare_coordination_Y(Point a, Point b)
{
    return a.is_less_than(b, Point::Coordination::Y);
}
bool CubicCrossLinkedOctree::compare_coordination_Z(Point a, Point b)
{
    return a.is_less_than(b, Point::Coordination::Z);
}
#endif
