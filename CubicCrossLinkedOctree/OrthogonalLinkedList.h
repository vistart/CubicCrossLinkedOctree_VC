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
#ifndef __ORTHOGONAL_LINKED_LIST_H__
#define __ORTHOGONAL_LINKED_LIST_H__

#include "OrthogonalLinkedListNode.h"
#include <vector>

template <typename TLinkedListNode,
          typename TOctreeNode,
          typename TPoint,
          typename = typename std::enable_if<std::is_base_of<OrthogonalLinkedListNode<TOctreeNode, TPoint>, TLinkedListNode>::value, TLinkedListNode>::type>
class OrthogonalLinkedList
{
	unsigned int count_vertex = 0;
	unsigned int count_arc = 0;

	std::vector<TLinkedListNode> head;
};

#endif
