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
#ifndef __CUBIC_CROSS_LINKED_OCTREE_H__
#define __CUBIC_CROSS_LINKED_OCTREE_H__

#include "OctreeNode.h"
#include "NodeCoordinate.h"
#include "PointList.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>

/**
 * 
 */
template<typename TPointList, typename TPoint, typename = typename std::enable_if<std::is_base_of<PointList<TPoint>, TPointList>::value, TPointList>::type>
class CubicCrossLinkedOctree
{
public:
    CubicCrossLinkedOctree() = default;
    /**
     * Construct the octree.
     *
     * @param point_list Points from which construct an octree.
     * @param depth Depth of the octree.
     */
    CubicCrossLinkedOctree(std::shared_ptr<TPointList> const& point_list, unsigned char depth = 12)
    {
#ifdef _DEBUG
    	/* The following loop will be discarded. */
        for (int i = 1; i <= 5; i++) {
            auto [x, y, z, d] = GetRelativeNodeCoordinate(NodeCoordinate(16, 15, 14, 5), i);
            std::cout << "X:" << x << " | Y:" << y << " | Z:" << z << " | Depth:" << static_cast<unsigned short>(d) << std::endl;
        }
#endif
        if (depth < 1 || depth > 127) {
            throw "The depth out of range. It should be an integer from 1 to 127.";
        }
        
    	// Specify the parameter `depth`. This parameter is recognized as the depth of octree.
        this->depth = depth;

    	// Find the the boundaries throughout the three dimensions.
    	
        std::cout << "The boundaries of three dimensions are following:" << std::endl;
    	
        boundaries = find_boundary(point_list);
        std::cout << std::endl;
        
    	// Find the middle point of each dimension.
    	
        const auto middle_point = OctreeNode<TPoint>::find_middle_point(boundaries);
        auto [x_mid, y_mid, z_mid] = middle_point;
        max_range = find_max_range(boundaries);

        leaf_width = max_range / ((base_depth << depth) - 1);
#pragma region Output Range
#ifdef _DEBUG
        std::cout << "Leaf node width: " << leaf_width << std::endl;
        std::cout << "Max extended range (= Max range + Leaf node width): " << std::setprecision(8) << max_range + leaf_width << std::endl;
        std::cout << "X-axis extended range: " << std::setprecision(8) << x_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << x_mid + (max_range + leaf_width) / 2 << std::endl;
        std::cout << "Y-axis extended range: " << std::setprecision(8) << y_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << y_mid + (max_range + leaf_width) / 2 << std::endl;
        std::cout << "Z-axis extended range: " << std::setprecision(8) << z_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << z_mid + (max_range + leaf_width) / 2 << std::endl;
#endif
#pragma endregion
        
#pragma region Insert Point into Octree
    	
        auto points = point_list->GetPoints();
        for (auto i = 0; i < points->size(); i++) {
            auto& point = (*points)[i];
            const auto& node_coordinate = OctreeNode<TPoint>::find_node_coordinate(point, middle_point, max_range, depth);
            auto result = insert_point(node_coordinate, point);
        }
#pragma endregion
#ifdef _DEBUG
    	
        print_nodes_stats();
        
#endif
    }
    ~CubicCrossLinkedOctree() = default;
    /*
     * The mapping between node coordinates and octree nodes.
     */
    typedef std::unordered_map<NodeCoordinate, std::shared_ptr<OctreeNode<TPoint>>, NodeCoordinate::Hash> node_map;
protected:
    node_map nodes;

    /**
     * Get the coordinate of a specific depth difference relative to the current
     * coordinates.
     * If the specified depth is deeper than the depth of the specified coordinate,
     * zero is added at the end of the coordinate; if the specified depth is
     * shallower than the depth of the specified coordinate, the specified depth
     * is truncated; otherwise, the output is as it is, but the depth is 0.
     *
     * For example:
     * The detail of a node coordinate is (X:16, Y:15, Z:14, D:5).
     * 
     * if parameter `depth` is 3, the output is (2, 1, 1, 3);
     * if parameter `depth` is 5, the output is as it is, but the depth is 0.
     * if parameter `depth` is 7, the output is (64, 60, 56, 2);
     *
     * @param coordinate
     * @param depth Depth difference relative to specified coordinate.
     * @return calculated coordinate.
     */
    static NodeCoordinate GetRelativeNodeCoordinate(NodeCoordinate const& coordinate, unsigned char depth)
    {
        auto [x, y, z, d] = coordinate;
        if (d < depth) {
            return NodeCoordinate(x << (depth - d), y << (depth - d), z << (depth - d), depth - d);
        }
        if (d > depth) {
            return NodeCoordinate(x >> (d - depth), y >> (d - depth), z >> (d - depth), d - depth);
        }
        return NodeCoordinate(x, y, z, 0);
    }

    
private:
    unsigned char depth = 12; // The depth range is limited to between 1 and 127.
    std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> boundaries;
    double max_range = 1;
    long long const base_depth = 1;
    double leaf_width = 1;

    void print_nodes_stats()
    {
        std::cout << "Octree Stats:" << std::endl;
        size_t count = 0;
        std::map<size_t, unsigned int> count_per_node;
        for (auto &p : this->nodes)
        {
            auto size = p.second->GetPoints().size();
            count += size;
            auto [iterator, success] = count_per_node.try_emplace(p.second->GetPoints().size(), 1);
            if (!success) {
               ++iterator->second;
            }
        }
        std::cout << "Nodes: " << this->nodes.size() << ", Depth: " << (int)depth << ", Average Density: " << (float)count / this->nodes.size() << std::endl;

        std::cout << "Number of nodes containing # point(s):" << std::endl;
        for (auto& c : count_per_node)
        {
            std::cout << "Count (" << c.first << "): " << c.second << std::endl;
        }
        std::cout << std::endl;
    }

	/**
	 * Insert Node into Octree.
	 *
	 * If the current node exists in the octree, it returns false, otherwise is inserted.
	 * 
	 * @param node_coordinate the coordinates of node.
	 * @param node the node to inserted.
	 * @return true only if `node_map` doesn't contain the passed-in `node`.
	 */
	bool insert_node(NodeCoordinate const& node_coordinate, std::shared_ptr<OctreeNode<TPoint>> const& node)
    {
        /**
         * If the coordinates of the current node already exist, it is considered that the current node cannot insert a new node.
         */
        if (node_exists(node_coordinate))
            return false;
        auto result = this->nodes.insert({ node_coordinate, node });
        return result.second;
    }

	bool node_exists(NodeCoordinate const& node_coordinate)
    {
        return this->nodes.find(node_coordinate) != this->nodes.end();
    }

	/**
	 * Insert a Point into Octree.
	 *
	 * @param node_coordinate the coordinates of node to which the point belongs.
	 * @param point the point to be inserted.
	 *
	 * @return true if inserted. 
	 */
	bool insert_point(NodeCoordinate const& node_coordinate, std::shared_ptr<TPoint> const& point)
    {
    	if (!node_exists(node_coordinate) && !insert_node(node_coordinate, std::make_shared<OctreeNode<TPoint>>()))
            return false;
        const auto& result = nodes[node_coordinate];
        *result << point;
        return true;
    	if (node_exists(node_coordinate))
    	{
            const auto& result = nodes[node_coordinate];
            *result << point;
            return true;
    	}
        const auto& ptr = std::make_shared<OctreeNode<TPoint>>(point);
        return insert_node(node_coordinate, ptr);
    }

	/**
	 * Find the boundary of the point cloud.
	 *
	 * @param point_list The list that contains all the points.
	 * @return The min & max coordinate of three dimensions.
	 */
    static std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> find_boundary(std::shared_ptr<TPointList> const& point_list)
    {
        /**
         * The return value of `GetPoints()` method is a shared pointer pointed to a point.
         * That is, if you want to use the built-in methods that return pointers such as
         * `min_element`/`max_element`, you should add a dereference symbol `*`
         * when accessing a specific point.
         *
         * The following lines are examples.
         */
        const auto comp_x = [](std::shared_ptr<Point> a, std::shared_ptr<Point> b) {return a->is_less_than(*b, Point::Coordination::X); };
        const auto comp_y = [](std::shared_ptr<Point> a, std::shared_ptr<Point> b) {return a->is_less_than(*b, Point::Coordination::Y); };
        const auto comp_z = [](std::shared_ptr<Point> a, std::shared_ptr<Point> b) {return a->is_less_than(*b, Point::Coordination::Z); };
        const auto begin = point_list->GetPoints()->begin();
        const auto end = point_list->GetPoints()->end();
        const auto x_min = min_element(begin, end, comp_x);
        const auto x_max = max_element(begin, end, comp_x);
        const auto y_min = min_element(begin, end, comp_y);
        const auto y_max = max_element(begin, end, comp_y);
        const auto z_min = min_element(begin, end, comp_z);
        const auto z_max = max_element(begin, end, comp_z);
#ifdef _DEBUG
        std::cout << std::fixed;
        std::cout << "X-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, x_min) << "]" << std::setw(11) << (**x_min).X() << " to "
             << std::setw(0) << "[" << std::setw(8) << std::distance(begin, x_max) << "]" << std::setw(11) << (**x_max).X() << std::endl;
        std::cout << "Y-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, y_min) << "]" << std::setw(11) << (**y_min).Y() << " to "
             << std::setw(0) << "[" << std::setw(8) << std::distance(begin, y_max) << "]" << std::setw(11) << (**y_max).Y() << std::endl;
        std::cout << "Z-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, z_min) << "]" << std::setw(11) << (**z_min).Z() << " to "
             << std::setw(0) << "[" << std::setw(8) << std::distance(begin, z_max) << "]" << std::setw(11) << (**z_max).Z() << std::endl;
#endif
        const auto x_range = (**x_max).X() - (**x_min).X();
        const auto y_range = (**y_max).Y() - (**y_min).Y();
        const auto z_range = (**z_max).Z() - (**z_min).Z();
        const auto x_mid = ((**x_max).X() + (**x_min).X()) / 2;
        const auto y_mid = ((**y_max).Y() + (**y_min).Y()) / 2;
        const auto z_mid = ((**z_max).Z() + (**z_min).Z()) / 2;
#ifdef _DEBUG
        std::cout << "X-axis range: " << std::setprecision(8) << x_range << " middle point: " << std::setprecision(8) << x_mid << std::endl;
        std::cout << "Y-axis range: " << std::setprecision(8) << y_range << " middle point: " << std::setprecision(8) << y_mid << std::endl;
        std::cout << "Z-axis range: " << std::setprecision(8) << z_range << " middle point: " << std::setprecision(8) << z_mid << std::endl;
#endif
        const auto max_range = std::max(x_range, std::max(y_range, z_range));
#ifdef _DEBUG
        std::cout << "Max range: " << std::setprecision(8) << max_range << std::endl;
#endif
        const auto x_range_min = x_mid - max_range / 2;
        const auto x_range_max = x_mid + max_range / 2;
        const auto y_range_min = y_mid - max_range / 2;
        const auto y_range_max = y_mid + max_range / 2;
        const auto z_range_min = z_mid - max_range / 2;
        const auto z_range_max = z_mid + max_range / 2;
        return std::make_tuple(std::make_tuple((**x_min).X(), (**x_max).X()), std::make_tuple((**y_min).Y(), (**y_max).Y()), std::make_tuple((**z_min).Z(), (**z_max).Z()));
    }

	/**
	 * Find the value of the largest spanned dimension.
     *
     * @param boundaries which contains three candidate dimensions.
     * @return double The upper and lower limits of the largest dimension of the range.
	 */
    [[nodiscard]] double find_max_range(std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> const& boundaries) const
    {
        const auto& [x_range, y_range, z_range] = boundaries;
        const auto [x_range_min, x_range_max] = x_range;
        const auto [y_range_min, y_range_max] = y_range;
        const auto [z_range_min, z_range_max] = z_range;
        return std::max(x_range_max - x_range_min, std::max(y_range_max - y_range_min, z_range_max - z_range_min));
    }

	
};
#endif
