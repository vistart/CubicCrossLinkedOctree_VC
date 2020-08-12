/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __OCTREE_NODE_H__
#include "OctreeNode.h"
#endif

#ifdef __OCTREE_NODE_H__
OctreeNode::OctreeNode()
{
    if (this->is_leaf) {
        this->leaves = make_unique<set<unsigned int>>();
        this->nodes = nullptr;
    }
    else {
        this->leaves = nullptr;
        (*this->nodes)[0] = nullptr; // First Octant
        (*this->nodes)[1] = nullptr; // Second Octant
        (*this->nodes)[2] = nullptr; // Third Octant
        (*this->nodes)[3] = nullptr; // Fourth Octant
        (*this->nodes)[4] = nullptr; // Fifth Octant
        (*this->nodes)[5] = nullptr; // Sixth Octant
        (*this->nodes)[6] = nullptr; // Seventh Octant
        (*this->nodes)[7] = nullptr; // Eighth Octant
    }
}

OctreeNode::OctreeNode(unsigned int const index)
{
    this->is_leaf = true;
    this->leaves = make_unique<set<unsigned int>>();
    this->insert(index);
    this->nodes = nullptr;
}

OctreeNode::OctreeNode(initializer_list<OctreeNode> children)
{
    this->is_leaf = false;
    this->leaves = nullptr;
    int i = 0;
    for (auto iterator = children.begin(); iterator < children.end(); iterator++, i++)
    {
        //(*this->nodes)[i] = make_shared<OctreeNode>(*iterator);
    }
}

OctreeNode::~OctreeNode()
{
    if (this->is_leaf) {
        this->leaves = nullptr;
    }
    else {
        for (auto& node : *this->nodes)
        {
            node->~OctreeNode();
            node = nullptr;
        }
        this->nodes = nullptr;
    }
}

void OctreeNode::insert(unsigned int const& index)
{
    this->leaves->insert(index);
    /*
    for (auto p : *this->leaves)
    {
        cout << p << " ";
    }
    cout << endl;
    */
}

OctreeNode::NodeCoordinate OctreeNode::find_node_coordinate(Point const& point, OctreeNode::PointCoordinate const& middle_point, double const& max_range, unsigned char const depth = 8)
{
    double leaf_width = max_range / (pow(2, depth) - 1);
    auto [x_mid, y_mid, z_mid] = middle_point;
    const auto offset_of_x = point.offset_of(x_mid - (max_range + leaf_width) / 2, Point::Coordination::X);
    const auto offset_of_y = point.offset_of(y_mid - (max_range + leaf_width) / 2, Point::Coordination::Y);
    const auto offset_of_z = point.offset_of(z_mid - (max_range + leaf_width) / 2, Point::Coordination::Z);
    const auto x_th = (unsigned int)(offset_of_x / leaf_width);
    const auto y_th = (unsigned int)(offset_of_y / leaf_width);
    const auto z_th = (unsigned int)(offset_of_z / leaf_width);
    // cout << "Offset of last point in (X,Y,Z): " << "(" << offset_of_x << "," << offset_of_y << "," << offset_of_z << ")" << " (X-th, Y-th, Z-th) in hexidecimal: " << "(" << bitset<10>(x_th) << "," << bitset<10>(y_th) << "," << bitset<10>(z_th) << ")" << endl;
    return make_tuple(x_th, y_th, z_th, depth);
}

OctreeNode::PointCoordinate OctreeNode::find_middle_point(double const& x_range_min, double const& x_range_max, double const& y_range_min, double const& y_range_max, double const& z_range_min, double const& z_range_max)
{
    return make_tuple((x_range_max + x_range_min) / 2, (y_range_max + y_range_min) / 2, (z_range_max + z_range_min) / 2);
}

OctreeNode::PointCoordinate OctreeNode::find_middle_point(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const& boundries)
{
    auto [x_range, y_range, z_range] = boundries;
    auto [x_range_min, x_range_max] = x_range;
    auto [y_range_min, y_range_max] = y_range;
    auto [z_range_min, z_range_max] = z_range;
    return OctreeNode::find_middle_point(x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max);
}
#endif
