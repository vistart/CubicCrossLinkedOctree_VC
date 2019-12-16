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

template <typename T, typename TPoint, typename = typename enable_if<is_base_of<PointList<TPoint>, T>::value>::type>
class PointCloud
{
public:
    PointCloud() {
        this->point_list = make_shared<T>();
    }
    ~PointCloud() {
        this->point_list = nullptr;
    }
    virtual shared_ptr<T> GetPointList() {
        return this->point_list;
    }
private:
    shared_ptr<T> point_list;
};
#endif
