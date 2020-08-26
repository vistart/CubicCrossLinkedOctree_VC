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
#ifndef __ORTHOGONAL_LINKED_LIST_BOX__
#define __ORTHOGONAL_LINKED_LIST_BOX__

#include <memory>

typedef struct
{
	int weight;
} BoxInfo;

template<typename T>
class OrthogonalLinkedListBox
{
	int head_vex;
	int tail_vex;
	std::unique_ptr<OrthogonalLinkedListBox> head_ptr;
	std::unique_ptr<OrthogonalLinkedListBox> tail_ptr;
	std::shared_ptr<T> info;
};

#endif
