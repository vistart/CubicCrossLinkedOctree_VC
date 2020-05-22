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
#include <list>
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
        for (int i = 1; i <= 5; i++) {
            auto [x, y, z, d] = GetRelativeNodeCoordinate(make_tuple(16, 15, 14, 5), i);
            cout << (int)x << " " << (int)y << " " << (int)z << " " << (int)d << endl;
        } return;
        if (depth < 1 || depth > 31) {
            throw "The depth out of range. It should be an integer from 1 to 31.";
        }
        this->depth = depth;
        const auto boundries = find_boundry(point_list);
        const auto middle_point = OctreeNode::find_middle_point(boundries);
        auto [x_mid, y_mid, z_mid] = middle_point;
        const auto max_range = find_max_range(boundries);

        long long base_depth = 1;
        double leaf_width = max_range / ((base_depth << depth) - 1);
#ifdef _DEBUG
        cout << "Max extended range: " << setprecision(8) << max_range + leaf_width << endl;
        cout << "X-axis extended range: " << setprecision(8) << x_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << x_mid + (max_range + leaf_width) / 2 << endl;
        cout << "Y-axis extended range: " << setprecision(8) << y_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << y_mid + (max_range + leaf_width) / 2 << endl;
        cout << "Z-axis extended range: " << setprecision(8) << z_mid - (max_range + leaf_width) / 2 << " to " << setprecision(8) << z_mid + (max_range + leaf_width) / 2 << endl;

        cout << "Leaf node width: " << leaf_width << endl;
#endif
        for (auto i = 0; i < point_list->GetPoints()->size(); i++) {
            auto& point = (*point_list->GetPoints())[i];
            const auto& node_coordinate = OctreeNode::find_node_coordinate(point, middle_point, max_range, depth);
            insert_point(node_coordinate, i);
        }
#ifdef _DEBUG
        print_nodes_stats();
#endif
    }
    ~CubicCrossLinkedOctree() = default;
protected:
    OctreeNode::node_map nodes;
    shared_ptr<OctreeNode> root = make_shared<OctreeNode>();
    unique_ptr<OctreeNode> build_tree(OctreeNode::node_map nodes)
    {
        for (auto node : nodes)
        {
            auto coordinate = node.first;
            build_tree(node.first, depth);
        }
    }
    shared_ptr<OctreeNode> build_tree(OctreeNode::NodeCoordinate coordinate)
    {
        auto node = get_deepest_node(coordinate);
        if (node->coordinate != coordinate) {
            // There are two cases of inequality: either coordinate is deeper than node or shallower.
            // If the former, build the tree node until it could meet the same depth; otherwise,
            // return the pointer of the node with the coordinate.

        }
    }
    /**
     * 
     */
    shared_ptr<OctreeNode> get_deepest_node(OctreeNode::NodeCoordinate coordinate)
    {
        auto [x, y, z, d] = coordinate;
        if (d <= 0) { // The Depth less than or equal to zero is abnormal.
            throw exception("The depth shouldn't be less than zero.");
        }
        if (d > 1)
        {
            auto node = get_deepest_node(GetRelativeNodeCoordinate(coordinate, d - 1));
            if (node)
            {
                if (node->is_leaf) {
                    return node;
                }
                auto child = node->get_node((x << 2 + y << 1 + z) & 7);
                return child ? child : node;
            }
            return nullptr;
        }
        if (d == 1)
        {
            auto child = root->get_node((x << 2 + y << 1 + z) & 7);
            return child ? child : root;
        }
        return nullptr;
    }

    shared_ptr<OctreeNode> emplace(OctreeNode& parent, OctreeNode& child, OctreeNode::NodeCoordinate coordinate)
    {/*
        if (parent) {
            throw exception("The parent cannot be accessed.");
        }
        */
        return nullptr;
    }

    shared_ptr<OctreeNode> try_emplace(OctreeNode::NodeCoordinate parent, unsigned char index, OctreeNode& child)
    {/*
        if (!get_node(parent)) {
            build_tree(parent);
        }*/
        return nullptr;
    }

    /**
     * Get the coordinate of a specific depth difference relative to the current
     * coordinates.
     * If the specified depth is deeper than the depth of the specified coordinate,
     * zero is added at the end of the coordinate; if the specified depth is
     * shallower than the depth of the specified coordinate, the specified depth
     * is truncated; otherwise, the output is as it is.
     *
     * @param OctreeNode::NodeCoordinate coordinate.
     * @param unsigned char Depth difference relative to specified coordinate.
     * @return OctreeNode::NodeCoordinate calculated coordinate.
     */
    OctreeNode::NodeCoordinate GetRelativeNodeCoordinate(OctreeNode::NodeCoordinate coordinate, unsigned char depth)
    {
        auto [x, y, z, d] = coordinate;
        if (d < depth) {
            return make_tuple(x << (depth - d), y << (depth - d), z << (depth - d), depth - d);
        }
        if (d > depth) {
            return make_tuple(x >> (d - depth), y >> (d - depth), z >> (d - depth), d - depth);
        }
        return coordinate;
    }

    
private:
    unsigned char depth = 12; // The depth range is limited to between 1 and 31.
    void print_nodes_stats()
    {
        cout << "Octree Stats:" << endl;
        size_t count = 0;
        map<size_t, unsigned int> count_per_node;
        for (auto &p : this->nodes)
        {
            count += p.second.get_leaves().size();
            auto [iterator, success] = count_per_node.try_emplace(p.second.get_leaves().size(), 1);
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

	/**
	 * Find the boundry of the point cloud.
	 *
	 * @param shared_ptr<T> const& The list that contains all the points.
	 * @return tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> The min & max coordinate of three dimensions.
	 */
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
#ifdef _DEBUG
        cout << fixed;
        cout << "X-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, x_min) << "]" << setprecision(8) << (*x_min).X() << endl;
        cout << "X-axis highest boundry: " << setprecision(0) << "[" << distance(begin, x_max) << "]" << setprecision(8) << (*x_max).X() << endl;
        cout << "Y-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, y_min) << "]" << setprecision(8) << (*y_min).Y() << endl;
        cout << "Y-axis highest boundry: " << setprecision(0) << "[" << distance(begin, y_max) << "]" << setprecision(8) << (*y_max).Y() << endl;
        cout << "Z-axis lowest boundry:  " << setprecision(0) << "[" << distance(begin, z_min) << "]" << setprecision(8) << (*z_min).Z() << endl;
        cout << "Z-axis highest boundry: " << setprecision(0) << "[" << distance(begin, z_max) << "]" << setprecision(8) << (*z_max).Z() << endl;
#endif
        const auto x_range = (*x_max).X() - (*x_min).X();
        const auto y_range = (*y_max).Y() - (*y_min).Y();
        const auto z_range = (*z_max).Z() - (*z_min).Z();
        const auto x_mid = ((*x_max).X() + (*x_min).X()) / 2;
        const auto y_mid = ((*y_max).Y() + (*y_min).Y()) / 2;
        const auto z_mid = ((*z_max).Z() + (*z_min).Z()) / 2;
#ifdef _DEBUG
        cout << "X-axis range: " << setprecision(8) << x_range << " middle point: " << setprecision(8) << x_mid << endl;
        cout << "Y-axis range: " << setprecision(8) << y_range << " middle point: " << setprecision(8) << y_mid << endl;
        cout << "Z-axis range: " << setprecision(8) << z_range << " middle point: " << setprecision(8) << z_mid << endl;
#endif
        const auto max_range = max(x_range, max(y_range, z_range));
#ifdef _DEBUG
        cout << "Max range: " << setprecision(8) << max_range << endl;
#endif
        const auto x_range_min = x_mid - max_range / 2;
        const auto x_range_max = x_mid + max_range / 2;
        const auto y_range_min = y_mid - max_range / 2;
        const auto y_range_max = y_mid + max_range / 2;
        const auto z_range_min = z_mid - max_range / 2;
        const auto z_range_max = z_mid + max_range / 2;
        return make_tuple(make_tuple((*x_min).X(), (*x_max).X()), make_tuple((*y_min).Y(), (*y_max).Y()), make_tuple((*z_min).Z(), (*z_max).Z()));
    }

	/**
	 * Find the value of the largest spanned dimension
	 */
    double find_max_range(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const& boundries) const
    {
        const auto [x_range, y_range, z_range] = boundries;
        const auto [x_range_min, x_range_max] = x_range;
        const auto [y_range_min, y_range_max] = y_range;
        const auto [z_range_min, z_range_max] = z_range;
        return max(x_range_max - x_range_min, max(y_range_max - y_range_min, z_range_max - z_range_min));
    }
    list<shared_ptr<OctreeNode::NodeCoordinate>> list_x;
};
#endif
