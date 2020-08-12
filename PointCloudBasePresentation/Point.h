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
#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <iomanip>
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

using namespace std;

/*
 This class is used to describe a point (or a vertex in discrete mathematics).
 The currently supported attributes are:
 - 3D Coordinates (X, Y, Z) (Required, double for each)
 - Color (R, G, B) (Optional, unsigned char for each)
 - Normal Vector (NX, NY, NZ) (Optional, double for each)
 - Transparency (ALPHA) (Optional, unsigned char)
 - Confidence (CONFIDENCE) (Optional, positive double-precision number or zero)
 - Intensity (INTENSITY) (Optional, positive double-precision number or zero)

 If you think that this class definition cannot meet your needs, you can inherit
 the current class and implement it yourself according to your needs.

 TODO:
 - Enable to allocate memory for coordinates, colors, normal vector, transparency,
   confidence, and intensity as needed, that is, if not needed, it is not allocated.
*/
class Point
{
public:
    Point() = default;
    ~Point() = default;
    double X() const noexcept
    {
        return __X;
    }
    virtual Point& X(double const X) noexcept {
        __X = X;
        return *this;
    }
    double Y() const noexcept
    {
        return __Y;
    }
    virtual Point& Y(double const Y) noexcept {
        __Y = Y;
        return *this;
    }
    double Z() const noexcept
    {
        return __Z;
    }
    virtual Point& Z(double const Z) noexcept {
        __Z = Z;
        return *this;
    }
    unsigned char R() const
    {
        return __R;
    }
    virtual Point& R(unsigned char const R) {
        __R = R;
        return *this;
    }
    unsigned char G() const
    {
        return __G;
    }
    virtual Point& G(unsigned char const G) {
        __G = G;
        return *this;
    }
    unsigned char B() const
    {
        return __B;
    }
    virtual Point& B(unsigned char const B) {
        __B = B;
        return *this;
    }
    double NX() const
    {
        return __NX;
    }
    virtual Point& NX(double const NX) {
        __NX = NX;
        return *this;
    }
    double NY() const
    {
        return __NY;
    }
    virtual Point& NY(double const NY) {
        __NY = NY;
        return *this;
    }
    double NZ() const
    {
        return __NZ;
    }
    virtual Point& NZ(double const NZ) {
        __NZ = NZ;
        return *this;
    }
    unsigned char ALPHA() const
    {
        return __ALPHA;
    }
    virtual Point& ALPHA(unsigned char const ALPHA) {
        __ALPHA = ALPHA;
        return *this;
    }
    double CONFIDENCE() const
    {
        return __CONFIDENCE;
    }
    virtual Point& CONFIDENCE(double const CONFIDENCE) {
        __CONFIDENCE = CONFIDENCE;
        return *this;
    }
    double INTENSITY() const
    {
        return __INTENSITY;
    }
    virtual Point& INTENSITY(double const INTENSITY) {
        __INTENSITY = INTENSITY;
        return *this;
    }
    virtual bool operator==(Point const& vertex) const
    {
        bool result = (__X == vertex.X() && __Y == vertex.Y() && __Z == vertex.Z());
        if (has_RGB)
        {
            result = (result && __R == vertex.R() && __G == vertex.G() && __B == vertex.B());
        }
        if (has_normal)
        {
            result = (result && __NX == vertex.NX() && __NY == vertex.NY() && __NZ == vertex.NZ());
        }
        if (has_alpha)
        {
            result = (result && __ALPHA == vertex.ALPHA());
        }
        if (has_confidence)
        {
            result = (result && __CONFIDENCE == vertex.CONFIDENCE());
        }
        if (has_intensity)
        {
            result = (result && __INTENSITY == vertex.INTENSITY());
        }
        return result;
    }
    virtual bool operator!=(Point const& vertex) const
    {
        return !(*this == vertex);
    }
    virtual bool operator<(Point const& vertex) const
    {
        return __X < vertex.X() || __Y < vertex.Y() || __Z < vertex.Z();
    }
    virtual bool operator>(Point const& vertex) const
    {
        return __X > vertex.X() || __Y > vertex.Y() || __Z > vertex.Z();
    }
    enum class Coordination { X, Y, Z };
    virtual bool is_less_than(Point const& obj, Coordination const& coord) const
    {
        switch (coord) {
        case Coordination::X:
            return this->__X < obj.X();

        case Coordination::Y:
            return this->__Y < obj.Y();

        case Coordination::Z:
            return this->__Z < obj.Z();
        }
#ifdef _MSC_VER
        throw exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
        throw runtime_error(coord_no_out_of_range_message);
#endif
    }
    virtual bool is_equal_to(Point const& obj, Coordination const& coord) const
    {
        switch (coord) {
        case Coordination::X:
            return this->__X == obj.X();

        case Coordination::Y:
            return this->__Y == obj.Y();

        case Coordination::Z:
            return this->__Z == obj.Z();
        }
#ifdef _MSC_VER
        throw exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
        throw runtime_error(coord_no_out_of_range_message);
#endif
    }
    virtual bool is_greater_than(Point const& obj, Coordination const& coord) const
    {
        switch (coord) {
        case Coordination::X:
            return this->__X > obj.X();

        case Coordination::Y:
            return this->__Y > obj.Y();

        case Coordination::Z:
            return this->__Z > obj.Z();
        }
#ifdef _MSC_VER
        throw exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
        throw runtime_error(coord_no_out_of_range_message);
#endif
    }
    virtual bool is_equal_or_less_than(Point const& obj, Coordination const& coord) const
    {
        return this->is_less_than(obj, coord) || this->is_equal_to(obj, coord);
    }
    virtual bool is_equal_or_greater_than(Point const& obj, Coordination const& coord) const
    {
        return this->is_greater_than(obj, coord) || this->is_equal_to(obj, coord);
    }
    bool has_RGB = false;
    bool has_normal = false;
    bool has_alpha = false;
    bool has_confidence = false;
    bool has_intensity = false;
    void offset(double const, double const, double const);
    double offset_of(double const, Coordination const&) const;
    friend ostream& operator<<(ostream& stream, Point const& point)
    {
        stream << "(" << setprecision(10) << point.__X << "," << setprecision(10) << point.__Y << "," << setprecision(10) << point.__Z << ")";
        return stream;
    }
protected:
    double __X = 0;
    double __Y = 0;
    double __Z = 0;
    unsigned char __R = 0;
    unsigned char __G = 0;
    unsigned char __B = 0;
    double __NX = 0;
    double __NY = 0;
    double __NZ = 0;
    unsigned char __ALPHA = 255;
    double __CONFIDENCE = 1;
    double __INTENSITY = 0.5;
    void set_all_properties(double const X, double const Y, double const Z,
        unsigned char const R, unsigned char const G, unsigned char const B,
        double const NX, double const NY, double const NZ,
        unsigned char const ALPHA, double const CONFIDENCE, double const INTENSITY)
    {
        this->__X = X;
        this->__Y = Y;
        this->__Z = Z;
        this->__R = R;
        this->__G = G;
        this->__B = B;
        this->__NX = NX;
        this->__NY = NY;
        this->__NZ = NZ;
        this->__ALPHA = ALPHA;
        this->__CONFIDENCE = CONFIDENCE;
        this->__INTENSITY = INTENSITY;
    }
private:
    const char* coord_no_out_of_range_message = "The coordination system code is out of range.";
};

#endif
