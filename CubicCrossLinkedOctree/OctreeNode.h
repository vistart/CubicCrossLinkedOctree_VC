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
#ifndef __OCTREE_NODE_H__
#define __OCTREE_NODE_H__

#include "Point.h"
#include "PointList.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <vector>
using namespace std;
class OctreeNode
{
public:
    void insert(unsigned int const&);
    typedef tuple<double, double, double> PointCoordinate;
    typedef tuple<unsigned int, unsigned int, unsigned int> NodeCoordinate;
    typedef map<NodeCoordinate, OctreeNode> node_type;
    OctreeNode();
    OctreeNode(unsigned int const);
    ~OctreeNode();
    static NodeCoordinate find_node_coordinate(Point const&, PointCoordinate const&, double const&, unsigned char const);
    static PointCoordinate find_middle_point(double const&, double const&, double const&, double const&, double const&, double const&);
    static PointCoordinate find_middle_point(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const&);
    friend ostream& operator<<(ostream& stream, OctreeNode const& node)
    {
        if (node.is_leaf) {
            if (node.leaves->size()) {

            }
            return stream;
        }
        else {
            stream << "This node is not a node.";
            return stream;
        }
    }
protected:
    bool is_leaf = true;
    unique_ptr<set<unsigned int>> leaves;
    unique_ptr<array<unique_ptr<OctreeNode>, 8>> nodes;
};
#endif
