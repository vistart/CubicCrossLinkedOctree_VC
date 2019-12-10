/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __POINT_H__
#include "Point.h"
#endif

#ifdef __POINT_H__
#include <exception>
double Point::X() const noexcept
{
	return __X;
}
Point& Point::X(double const X) noexcept
{
	__X = X;
	return *this;
}
double Point::Y() const noexcept
{
	return __Y;
}
Point& Point::Y(double const Y) noexcept
{
	__Y = Y;
	return *this;
}
double Point::Z() const noexcept
{
	return __Z;
}
Point& Point::Z(double const Z) noexcept
{
	__Z = Z;
	return *this;
}
unsigned char Point::R() const
{
	return __R;
}
Point& Point::R(unsigned char const R)
{
	__R = R;
	return *this;
}
unsigned char Point::G() const
{
	return __G;
}
Point& Point::G(unsigned char const G)
{
	__G = G;
	return *this;
}
unsigned char Point::B() const
{
	return __B;
}
Point& Point::B(unsigned char const B)
{
	__B = B;
	return *this;
}
double Point::NX() const
{
	return __NX;
}
Point& Point::NX(double const NX)
{
	__NX = NX;
	return *this;
}
double Point::NY() const
{
	return __NY;
}
Point& Point::NY(double const NY)
{
	__NY = NY;
	return *this;
}
double Point::NZ() const
{
	return __NZ;
}
Point& Point::NZ(double const NZ)
{
	__NZ = NZ;
	return *this;
}
unsigned char Point::ALPHA() const
{
	return __ALPHA;
}
Point& Point::ALPHA(unsigned char const ALPHA)
{
	__ALPHA = ALPHA;
	return *this;
}
double Point::CONFIDENCE() const
{
	return __CONFIDENCE;
}
Point& Point::CONFIDENCE(double const CONFIDENCE)
{
	__CONFIDENCE = CONFIDENCE;
	return *this;
}
double Point::INTENSITY() const
{
	return __INTENSITY;
}
Point& Point::INTENSITY(double const INTENSITY)
{
	__INTENSITY = INTENSITY;
	return *this;
}

bool Point::operator==(Point const& vertex) const
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

bool Point::operator!=(Point const& vertex) const
{
	return !(*this == vertex);
}

bool Point::operator<(Point const& vertex) const
{
	return __X < vertex.X() || __Y < vertex.Y() || __Z < vertex.Z();
}

bool Point::operator>(Point const& vertex) const
{
	return __X > vertex.X() || __Y > vertex.Y() || __Z > vertex.Z();
}

bool Point::is_less_than(Point const& obj, Coordination const& coord) const
{
	switch (coord) {
	case Coordination::X:
		return this->__X < obj.X();

	case Coordination::Y:
		return this->__Y < obj.Y();

	case Coordination::Z:
		return this->__Z < obj.Z();
	}
	throw exception(coord_no_out_of_range_message);
}

bool Point::is_equal_to(Point const& obj, Coordination const& coord) const
{
	switch (coord) {
	case Coordination::X:
		return this->__X == obj.X();

	case Coordination::Y:
		return this->__Y == obj.Y();

	case Coordination::Z:
		return this->__Z == obj.Z();
	}
	throw exception(coord_no_out_of_range_message);
}

bool Point::is_greater_than(Point const& obj, Coordination const& coord) const
{
	switch (coord) {
	case Coordination::X:
		return this->__X > obj.X();

	case Coordination::Y:
		return this->__Y > obj.Y();

	case Coordination::Z:
		return this->__Z > obj.Z();
	}
	throw exception(coord_no_out_of_range_message);
}

bool Point::is_equal_or_less_than(Point const& obj, Coordination const& coord) const
{
	return this->is_less_than(obj, coord) || this->is_equal_to(obj, coord);
}

bool Point::is_equal_or_greater_than(Point const& obj, Coordination const& coord) const
{
	return this->is_greater_than(obj, coord) || this->is_equal_to(obj, coord);
}

void Point::set_all_properties(double const X, double const Y, double const Z,
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

void Point::offset(double const offset_x, double const offset_y, double const offset_z)
{
	__X += offset_x;
	__Y += offset_y;
	__Z += offset_z;
}

double Point::offset_of(double const offset , Coordination const& coord) const
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
	throw exception(coord_no_out_of_range_message);
}

#endif
