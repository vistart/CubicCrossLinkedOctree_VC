/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __OCTREE_NODE_H__
#include "OctreeNode.h"
#endif

#ifdef __OCTREE_NODE_H__
OctreeNode::OctreeNode()
{
    if (this->is_leaf) {
        this->nodes.~vector();
    }
    else {
        this->nodes.resize(8);
        this->nodes[0] = make_unique<OctreeNode>();
        this->nodes[1] = make_unique<OctreeNode>();
        this->nodes[2] = make_unique<OctreeNode>();
        this->nodes[3] = make_unique<OctreeNode>();
        this->nodes[4] = make_unique<OctreeNode>();
        this->nodes[5] = make_unique<OctreeNode>();
        this->nodes[6] = make_unique<OctreeNode>();
        this->nodes[7] = make_unique<OctreeNode>();
    }
}

OctreeNode::~OctreeNode()
{
    if (this->is_leaf) {

    }
    else {
        for (auto& node : this->nodes)
        {
            node->~OctreeNode();
            node.~unique_ptr();
        }
        this->nodes.~vector();
    }
}
#endif
