/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX_H__
#include "PlyVertex.h"
#endif

#ifdef __PLY_VERTEX_H__
PlyVertex::PlyVertex(string vertex)
{
	stringstream stream(vertex);
	double X, Y, Z;
	char R = 0, G = 0, B = 0;
	stream >> X >> Y >> Z;
	if (has_RGB) {
		stream >> R >> G >> B;
	}
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255);
}

PlyVertex::PlyVertex(fstream& file)
{
	string line;
	while (line == "")
		getline(file, line);
	stringstream stream(line);
	double X, Y, Z;
	char R = 0, G = 0, B = 0;
	stream >> X >> Y >> Z;
	if (has_RGB) {
		stream >> R >> G >> B;
	}
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255);
}

PlyVertex::PlyVertex(double const X, double const Y, double const Z, unsigned char const R = 0, unsigned char const G = 0, unsigned char const B = 0)
{
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255);
}

void PlyVertex::set_all_properties(double const X, double const Y, double const Z, unsigned char const R, unsigned char const G, unsigned char const B, double const NX, double const NY, double const NZ, unsigned char const ALPHA)
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
}

double PlyVertex::X() const
{
	return __X;
}
PlyVertex& PlyVertex::X(double const X)
{
	__X = X;
	return *this;
}
double PlyVertex::Y() const
{
	return __Y;
}
PlyVertex& PlyVertex::Y(double const Y)
{
	__Y = Y;
	return *this;
}
double PlyVertex::Z() const
{
	return __Z;
}
PlyVertex& PlyVertex::Z(double const Z)
{
	__Z = Z;
	return *this;
}
unsigned char PlyVertex::R() const
{
	return __R;
}
PlyVertex& PlyVertex::R(unsigned char const R)
{
	__R = R;
	return *this;
}
unsigned char PlyVertex::G() const
{
	return __G;
}
PlyVertex& PlyVertex::G(unsigned char const G)
{
	__G = G;
	return *this;
}
unsigned char PlyVertex::B() const
{
	return __B;
}
PlyVertex& PlyVertex::B(unsigned char const B)
{
	__B = B;
	return *this;
}
double PlyVertex::NX() const
{
	return __NX;
}
PlyVertex& PlyVertex::NX(double const NX)
{
	__NX = NX;
	return *this;
}
double PlyVertex::NY() const
{
	return __NY;
}
PlyVertex& PlyVertex::NY(double const NY)
{
	__NY = NY;
	return *this;
}
double PlyVertex::NZ() const
{
	return __NZ;
}
PlyVertex& PlyVertex::NZ(double const NZ)
{
	__NZ = NZ;
	return *this;
}
unsigned char PlyVertex::ALPHA() const
{
	return __ALPHA;
}
PlyVertex& PlyVertex::ALPHA(unsigned char const ALPHA)
{
	__ALPHA = ALPHA;
	return *this;
}

bool PlyVertex::operator==(PlyVertex const& vertex) const
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
	return result;
}

bool PlyVertex::operator!=(PlyVertex const& vertex) const
{
	return !(*this == vertex);
}

bool PlyVertex::operator<(PlyVertex const& vertex) const
{
	return __X < vertex.__X || __Y < vertex.__Y || __Z < vertex.__Z;
}

bool PlyVertex::operator>(PlyVertex const& vertex) const
{
	return __X > vertex.__X || __Y > vertex.__Y || __Z > vertex.__Z;
}

void PlyVertex::offset(double const offset_x, double const offset_y, double const offset_z)
{
	__X += offset_x;
	__Y += offset_y;
	__Z += offset_z;
}
#endif