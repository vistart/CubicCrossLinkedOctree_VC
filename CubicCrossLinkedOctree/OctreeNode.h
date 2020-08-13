/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __OCTREE_NODE_H__
#define __OCTREE_NODE_H__

#include "Point.h"
#include "NodeCoordinate.h"
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <set>
#include <tuple>
using namespace std;
class OctreeNode
{
public:
    /**
     * Insert Point.
     *
     * @param index index of point to be inserted.
     */
    void insert(unsigned int const& index);
    /*
     * Point coordinate.
     * Each point coordinate contains X, Y and Z.
     */
    typedef tuple<double, double, double> PointCoordinate;
    OctreeNode();
    OctreeNode(unsigned int const);
    OctreeNode(initializer_list<OctreeNode>);
    ~OctreeNode();

	/**
	 * Calculate the coordinates of the node where a certain point is located.
	 *
	 * This method uses the point in space and the common maximum range of the three dimensions to determine the spatial range.
	 * Before using this method, you can use find_middle_point to calculate the midpoint of the space, and then pass it in as a parameter.
	 *
	 * Then, you need to specify the depth of the node in the octree. This parameter determines the node coordinate value.
	 *
	 * @param point The target point.
	 * @param middle_point The midpoint of the space.
	 * @param max_range Common maximum range of the three dimensions.
	 * @param depth The depth of the node in the octree. The default depth is 8.
	 *
	 * @return The coordinates of the node where the current point is located.
	 */
    static NodeCoordinate find_node_coordinate(Point const& point, PointCoordinate const& middle_point, double const& max_range, unsigned char const depth);

    /**
     * Calculate the coordinates of the midpoint in the specified space.
     *
     * @param x_range_min
     * @param x_range_max
     * @param y_range_min
     * @param y_range_max
     * @param z_range_min
     * @param z_range_max
     * @return the point coordinate of midpoint.
     */
    static PointCoordinate find_middle_point(double const& x_range_min, double const& x_range_max, double const& y_range_min, double const& y_range_max, double const& z_range_min, double const& z_range_max);

	/**
	 * Calculate the coordinates of the midpoint in the specified space.
	 *
	 * @param boundaries The boundary of the space to be calculated.
	 * @return the point coordinate of midpoint.
	 */
    static PointCoordinate find_middle_point(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const& boundaries);
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
    [[nodiscard]] shared_ptr<set<unsigned int>> get_leaves() const
    {
        return this->leaves;
    }
    NodeCoordinate get_coordinate()
    {
        if (is_leaf) {
            return coordinate;
        }
    }
    shared_ptr<OctreeNode> get_node(unsigned char index) const
    {
        return (*this->nodes)[index];
    }
protected:
    bool is_leaf = true;
    NodeCoordinate coordinate;
    shared_ptr<set<unsigned int>> leaves;
    /* Eight Octants. */
    unique_ptr<array<shared_ptr<OctreeNode>, 8>> nodes;
};
#endif
