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
    /**
     * Insert Point.
     *
     * @param unsigned int const& index of point to be inserted.
     */
    void insert(unsigned int const&);
    /* X, Y, X */
    typedef tuple<double, double, double> PointCoordinate;
    /* X, Y, Z, depth */
    typedef tuple<unsigned int, unsigned int, unsigned int, unsigned char> NodeCoordinate;
    typedef map<NodeCoordinate, OctreeNode> node_map;
    OctreeNode();
    OctreeNode(unsigned int const);
    OctreeNode(initializer_list<OctreeNode>);
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
    OctreeNode* operator[](unsigned int const index) const
    {
        return &(*(*this->nodes)[index]);
    }
    set<unsigned int> get_leaves() const
    {
        return *this->leaves;
    }
    NodeCoordinate get_coordinate()
    {
        if (is_leaf) {
            return coordinate;
        }
    }
    shared_ptr<OctreeNode> get_node(unsigned char index)
    {
        return (*this->nodes)[index];
    }
protected:
    bool is_leaf = true;
    NodeCoordinate coordinate;
    unique_ptr<set<unsigned int>> leaves;
    /* Eight Octants. */
    unique_ptr<array<shared_ptr<OctreeNode>, 8>> nodes;
};
#endif
