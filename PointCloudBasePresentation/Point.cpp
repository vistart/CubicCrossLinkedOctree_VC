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
using namespace std;
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif


Point* Point::operator+(Point const& target)
{
    __X += target.X();
    __Y += target.Y();
    __Z += target.Z();
    return this;
}

Point* Point::operator+(XYZ const& target)
{
    offset(target.X, target.Y, target.Z);
    return this;
}

void Point::offset(double offset_x, double offset_y, double offset_z)
{
    __X += offset_x;
    __Y += offset_y;
    __Z += offset_z;
}

void Point::offset(Point const& target)
{
    offset(target.X(), target.Y(), target.Z());
}

void Point::offset(XYZ const& target)
{
    offset(target.X, target.Y, target.Z);
}

double Point::offset_of(double offset, Coordination const& coordination) const
{
    switch (coordination)
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

std::tuple<double, double, double> Point::offset_of(std::tuple<double, double, double> const& offset) const
{
    auto& [x, y, z] = offset;
    return make_tuple<double, double, double>(__X - x, __Y - y, __Z - z);
}

std::tuple<double, double, double> Point::offset_of(double const& x, double const& y, double const& z) const
{
    return make_tuple<double, double, double>(__X - x, __Y - y, __Z - z);
}

#endif
