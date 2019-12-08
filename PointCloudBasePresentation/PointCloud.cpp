/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __POINT_CLOUD_H__
#include "PointCloud.h"
#endif

#ifdef __POINT_CLOUD_H__
PointCloud::PointCloud()
{
    this->points = make_unique<PointList>();
}

PointCloud::~PointCloud()
{
    this->points = nullptr;
}
#endif
