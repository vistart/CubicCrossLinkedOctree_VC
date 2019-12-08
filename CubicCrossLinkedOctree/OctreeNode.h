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

#include <memory>
#include <vector>
using namespace std;
class OctreeNode
{
public:
    OctreeNode();
    ~OctreeNode();
protected:
    bool is_leaf = true;
    vector<unique_ptr<OctreeNode>> nodes;
};
#endif
