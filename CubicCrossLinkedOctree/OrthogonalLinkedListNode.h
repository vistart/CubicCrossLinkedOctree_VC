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
#ifndef __ORTHOGONAL_LINKED_LIST_NODE__
#define __ORTHOGONAL_LINKED_LIST_NODE__

#include "OrthogonalLinkedListBox.h"
#include <memory>

#include "OctreeNode.h"

template<typename TOctreeNode,
         typename TPoint,
         typename = typename std::enable_if<std::is_base_of<OctreeNode<TPoint>, TOctreeNode>::type, TOctreeNode>::type>
class OrthogonalLinkedListNode
{
public:
    std::shared_ptr<TOctreeNode> data;
	std::unique_ptr<OrthogonalLinkedListBox<BoxInfo>> first_in;
	std::unique_ptr<OrthogonalLinkedListBox<BoxInfo>> first_out;
};

#endif
