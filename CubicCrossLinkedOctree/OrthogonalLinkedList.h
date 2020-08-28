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

/**
 * This class is used to represent a dimensional variable orthogonal linked list.
 *
 * @param TLinkedListNode: The linked list node class or derived class.
 * @param TOctreeNode: The octree node class or derived class. Note: The current class must be the same as the template parameter `TOctreeNode` of `TLinkedListNode`, otherwise it connot be compiled.
 * @param TPoint: The point class or derived class. Note: The current class must be the same as the template parameter `T` of `TOctreeNode`, otherwise it cannot be compiled.
 * @param TDimension: The number of dimensions in the template parameter when instantiating this class.
 */
template <class TLinkedListNode,
	      class TOctreeNode,
	      class TPoint,
          unsigned int TDimension,
          typename = typename std::enable_if<std::is_base_of<OrthogonalLinkedListNode<TOctreeNode, TPoint>, TLinkedListNode>::value, TLinkedListNode>::type>
class OrthogonalLinkedList
{
public:
	typedef std::vector<TLinkedListNode> dimension_head;

	OrthogonalLinkedList()
	{
		for (int i = 0; i < TDimension; i++)
		{
			heads.push_back(std::vector<TLinkedListNode>());
		}
	}

	virtual ~OrthogonalLinkedList() = default;

	std::shared_ptr<TOctreeNode> GetOctreeNode(std::initializer_list<int> position)
	{
		
	}

	[[nodiscard]] static int GetDimensions() noexcept
	{
		return TDimension;
	}

	[[nodiscard]] int GetCountOfVertex() noexcept
	{
		return this->count_vertex;
	}

	[[nodiscard]] int GetCountOfArc() noexcept
	{
		return this->count_arc;
	}
protected:
	std::vector<dimension_head> heads;

	/**
	 * The count of vertices.
	 */
	unsigned int count_vertex = 0;

	/**
	 * The count of arcs.
	 */
	unsigned int count_arc = 0;
};

#endif
