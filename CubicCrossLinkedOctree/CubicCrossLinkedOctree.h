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

#include "PointList.h"
#include "PlyFile.h"
#include "OctreeNode.h"
#include <algorithm>
#include <tuple>
#include <unordered_map>

class CubicCrossLinkedOctree
{
public:
    CubicCrossLinkedOctree();
    CubicCrossLinkedOctree(PlyVertexList const&);
    ~CubicCrossLinkedOctree();
protected:
private:
    tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> find_boundry(PlyVertexList const&);
    double find_max_range(tuple<tuple<double, double>, tuple<double, double>, tuple<double, double>> const&) const;
};
#endif
