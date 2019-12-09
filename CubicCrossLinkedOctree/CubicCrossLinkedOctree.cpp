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
#include <bitset>
#include <algorithm>
#include <iostream>
using namespace std;
CubicCrossLinkedOctree::CubicCrossLinkedOctree()
{

}

CubicCrossLinkedOctree::CubicCrossLinkedOctree(shared_ptr<PlyVertexList> point_list)
{
    const auto comp_x = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::X); };
    const auto comp_y = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Y); };
    const auto comp_z = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Z); };
    const auto begin = point_list->points.begin();
    const auto end = point_list->points.end();
    const auto x_min = min_element(begin, end, comp_x);
    const auto x_max = max_element(begin, end, comp_x);
    const auto y_min = min_element(begin, end, comp_y);
    const auto y_max = max_element(begin, end, comp_y);
    const auto z_min = min_element(begin, end, comp_z);
    const auto z_max = max_element(begin, end, comp_z);
    cout << fixed;
    cout << "X-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, x_min) << "]" << setprecision(8) << (*x_min).X() << endl;
    cout << "X-axis highest boundry: " << setprecision(0) << "[" << distance(begin, x_max) << "]" << setprecision(8) << (*x_max).X() << endl;
    cout << "Y-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, y_min) << "]" << setprecision(8) << (*y_min).Y() << endl;
    cout << "Y-axis highest boundry: " << setprecision(0) << "[" << distance(begin, y_max) << "]" << setprecision(8) << (*y_max).Y() << endl;
    cout << "Z-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, z_min) << "]" << setprecision(8) << (*z_min).Z() << endl;
    cout << "Z-axis highest boundry: " << setprecision(0) << "[" << distance(begin, z_max) << "]" << setprecision(8) << (*z_max).Z() << endl;
    const auto x_range = (*x_max).X() - (*x_min).X();
    const auto y_range = (*y_max).Y() - (*y_min).Y();
    const auto z_range = (*z_max).Z() - (*z_min).Z();
    const auto x_mid = ((*x_max).X() + (*x_min).X()) / 2;
    const auto y_mid = ((*y_max).Y() + (*y_min).Y()) / 2;
    const auto z_mid = ((*z_max).Z() + (*z_min).Z()) / 2;
    cout << "X-axis range: " << setprecision(8) << x_range << " middle point: " << setprecision(8) << x_mid << endl;
    cout << "Y-axis range: " << setprecision(8) << y_range << " middle point: " << setprecision(8) << y_mid << endl;
    cout << "Z-axis range: " << setprecision(8) << z_range << " middle point: " << setprecision(8) << z_mid << endl;
	
    const auto max_range = max(x_range, max(y_range, z_range));
    cout << "Max range: " << setprecision(8) << max_range << endl;
    const auto x_range_min = x_mid - max_range / 2;
    const auto x_range_max = x_mid + max_range / 2;
    const auto y_range_min = y_mid - max_range / 2;
    const auto y_range_max = y_mid + max_range / 2;
    const auto z_range_min = z_mid - max_range / 2;
    const auto z_range_max = z_mid + max_range / 2;

    cout << "X-axis extended range: " << setprecision(8) << x_range_min << " to " << setprecision(8) << x_range_max << endl;
    cout << "Y-axis extended range: " << setprecision(8) << y_range_min << " to " << setprecision(8) << y_range_max << endl;
    cout << "Z-axis extended range: " << setprecision(8) << z_range_min << " to " << setprecision(8) << z_range_max << endl;

    const unsigned char depth = 8; // The depth range is limited to between 1 and 31.
    double leaf_width = max_range / pow(2, depth);

    cout << "Leaf node width: " << leaf_width << endl;
    auto& last = point_list->points.back();
    const auto offset_of_x = last.offset_of(x_range_min, Point::Coordination::X);
    const auto offset_of_y = last.offset_of(y_range_min, Point::Coordination::Y);
    const auto offset_of_z = last.offset_of(z_range_min, Point::Coordination::Z);
    const auto x_th = (int)(offset_of_x / leaf_width);
    const auto y_th = (int)(offset_of_y / leaf_width);
    const auto z_th = (int)(offset_of_z / leaf_width);
    cout << "Offset of last point in X: " << offset_of_x << " X-th: " << x_th << " binary: " << bitset<depth>(x_th) << endl;
    cout << "Offset of last point in Y: " << offset_of_y << " Y-th: " << y_th << " binary: " << bitset<depth>(y_th) << endl;
    cout << "Offset of last point in Z: " << offset_of_z << " Z-th: " << z_th << " binary: " << bitset<depth>(z_th) << endl;

	
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
