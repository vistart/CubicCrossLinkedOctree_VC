/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __CUBIC_CROSS_LINKED_OCTREE_H__
#define __CUBIC_CROSS_LINKED_OCTREE_H__

#include "OctreeNode.h"
#include "PlyFile.h"
#include "PointList.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>

using namespace std;

template<typename T, typename TPoint, typename = typename enable_if<is_base_of<PointList<TPoint>, T>::value, T>::type>
class CubicCrossLinkedOctree
{
public:
    CubicCrossLinkedOctree() = default;
    CubicCrossLinkedOctree(shared_ptr<T> const& point_list, unsigned char depth = 12)
    {
        if (depth < 1 || depth > 31) {
            throw "The depth out of range. It should be an integer from 1 to 31.";
        }
        this->depth = depth;
        const auto boundries = find_boundry(point_list);
        const auto middle_point = OctreeNode::find_middle_point(boundries);
        double x_mid, y_mid, z_mid;
        tie(x_mid, y_mid, z_mid) = middle_point;
        const auto max_range = find_max_range(boundries);

        double leaf_width = max_range / (pow(2, depth) - 1);

        cout << "Max extended range: " << setprecision(8) << max_range + leaf_width << endl;
        cout << "X-axis extended range: " << setprecision(8) << x_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << x_mid + (max_range + leaf_width) / 2 << endl;
        cout << "Y-axis extended range: " << setprecision(8) << y_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << y_mid + (max_range + leaf_width) / 2 << endl;
        cout << "Z-axis extended range: " << setprecision(8) << z_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << z_mid + (max_range + leaf_width) / 2 << endl;

        cout << "Leaf node width: " << leaf_width << endl;
        for (auto i = 0; i < point_list->GetPoints()->size(); i++) {
            auto& point = (*point_list->GetPoints())[i];
            const auto& node_coordinate = OctreeNode::find_node_coordinate(point, middle_point, max_range, depth);
            insert_point(node_coordinate, i);
        }

        print_nodes_stats();
    }
    ~CubicCrossLinkedOctree() = default;
protected:
    OctreeNode::node_type nodes;
private:
    unsigned char depth = 12; // The depth range is limited to between 1 and 31.
    void print_nodes_stats()
    {
        cout << "Octree Stats:" << endl;
        unsigned int count = 0;
        map<unsigned int, unsigned int> count_per_node;
        for (auto &p : this->nodes)
        {
            count += p.second.GetLeaves().size();
            auto [iterator, success] = count_per_node.try_emplace(p.second.GetLeaves().size(), 1);
            if (!success) {
                iterator->second++;
            }
        }
        cout << "Nodes: " << this->nodes.size() << ", Depth: " << (int)depth << ", Average Density: " << (float)count / this->nodes.size() << endl;
        for (auto& c : count_per_node)
        {
            cout << "Count (" << c.first << "): " << c.second << endl;
        }
        cout << endl;
    }
    void insert_point(OctreeNode::NodeCoordinate const& node_coordinate, unsigned int const index)
    {
        auto [iterator, success] = nodes.try_emplace(node_coordinate, index);
        if (!success) {
            iterator->second.insert(index);
        }
    }
    tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> find_boundry(shared_ptr<T> const& point_list)
    {
        const auto comp_x = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::X); };
        const auto comp_y = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Y); };
        const auto comp_z = [](const Point& a, const Point& b) {return a.is_less_than(b, Point::Coordination::Z); };
        const auto begin = point_list->GetPoints()->begin();
        const auto end = point_list->GetPoints()->end();
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
        return make_tuple(make_tuple((*x_min).X(), (*x_max).X()), make_tuple((*y_min).Y(), (*y_max).Y()), make_tuple((*z_min).Z(), (*z_max).Z()));
    }
    double find_max_range(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const& boundries) const
    {
        auto [x_range, y_range, z_range] = boundries;
        auto [x_range_min, x_range_max] = x_range;
        auto [y_range_min, y_range_max] = y_range;
        auto [z_range_min, z_range_max] = z_range;
        return max(x_range_max - x_range_min, max(y_range_max - y_range_min, z_range_max - z_range_min));
    }
};
#endif
