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

#ifndef __POINT_LIST_H__
#define __POINT_LIST_H__
#include "Point.h"
#include <memory>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T, typename = typename enable_if<is_base_of<Point, T>::value, T>::type>
class PointList
{
public:
    PointList() {
        this->points = make_shared<vector<T>>();
    }
    ~PointList() {
        this->points = nullptr;
    }
    virtual shared_ptr<vector<T>> GetPoints() {
        return this->points;
    }
private:
    shared_ptr<vector<T>> points;
};
#endif
