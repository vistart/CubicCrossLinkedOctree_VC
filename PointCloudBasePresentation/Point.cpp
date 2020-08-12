/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __POINT_H__
#include "Point.h"
#endif

#ifdef __POINT_H__
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

void Point::offset(double const offset_x, double const offset_y, double const offset_z)
{
    __X += offset_x;
    __Y += offset_y;
    __Z += offset_z;
}

double Point::offset_of(double const offset, Coordination const& coord) const
{
    switch (coord)
    {
    case Coordination::X:
        return __X - offset;
    case Coordination::Y:
        return __Y - offset;
    case Coordination::Z:
        return __Z - offset;
    }
#ifdef _MSC_VER
    throw exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
    throw runtime_error(coord_no_out_of_range_message);
#endif
}

#endif
