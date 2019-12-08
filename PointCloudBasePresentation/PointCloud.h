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
#ifndef __POINT_CLOUD_H__
#define __POINT_CLOUD_H__

#include "PointList.h"

class PointCloud
{
public:
    PointCloud();
    ~PointCloud();
    shared_ptr<PointList> points;
};
#endif
