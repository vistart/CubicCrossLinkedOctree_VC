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

class CubicCrossLinkedOctree
{
public:
    CubicCrossLinkedOctree();
    CubicCrossLinkedOctree(shared_ptr<PlyVertexList>);
    ~CubicCrossLinkedOctree();
    bool compare_coordination_X(Point a, Point b);
    bool compare_coordination_Y(Point a, Point b);
    bool compare_coordination_Z(Point a, Point b);
};
#endif
