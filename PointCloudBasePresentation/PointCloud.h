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
#ifndef __POINT_CLOUD_H__
#define __POINT_CLOUD_H__

#include "PointList.h"

/*
 * This class is used to describe the Point Cloud.
 * There are a point list property for all points and a shared pointer to it.
 * The class that describes a point list can be the PointList class or its inherited class,
 * otherwise, the compilation fails.
 *
 * If you think that this class definition cannot meet your needs, you can inherit
 * the current class and implement it yourself according to your needs.
 *
 * If you need to implement inherited classes, be sure to follow the following specifications:
 * 1. Define the point list property that holds all points and make shared pointer point to it.
 * 2. Initialize the shared pointer of above point list property in Constructor.
 * 3. Make the point list to nullptr in Destructor.
*/
template <typename T, typename TPoint, typename = typename std::enable_if<std::is_base_of<PointList<TPoint>, T>::value>::type>
class PointCloud
{
public:
    PointCloud() {
        this->point_list = std::make_shared<T>();
    }
    virtual ~PointCloud() {
        this->point_list = nullptr;
    }
    virtual std::shared_ptr<T> GetPointList() {
        return this->point_list;
    }
private:
    std::shared_ptr<T> point_list;
};
#endif
