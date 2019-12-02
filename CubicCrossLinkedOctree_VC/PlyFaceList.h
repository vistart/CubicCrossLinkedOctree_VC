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

#ifndef __PLY_FACE_LIST_H__
#define __PLY_FACE_LIST_H__
#include "SingletonBase.h"
class PlyFaceList : public SingletonBase<PlyFaceList>
{
	PlyFaceList() = default;
	~PlyFaceList() = default;
	friend class SingletonBase<PlyFaceList>;
public:
};

#endif