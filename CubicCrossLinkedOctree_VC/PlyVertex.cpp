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
PlyVertex::PlyVertex(vector<VertexName> names, string vertex)
{
	double X = 0, Y = 0, Z = 0;
	unsigned short R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0;
	unsigned short ALPHA = 255;
	stringstream stream(vertex);
	for (auto name : names)
	{
		if (name.name == "x") {
			stream >> X;
		}
		else if (name.name == "y") {
			stream >> Y;
		}
		else if (name.name == "z") {
			stream >> Z;
		}
		else if (name.name == "red" || name.name == "r") {
			stream >> R;
		}
		else if (name.name == "green" || name.name == "g") {
			stream >> G;
		}
		else if (name.name == "blue" || name.name == "b") {
			stream >> B;
		}
		else if (name.name == "nx") {
			stream >> NX;
		}
		else if (name.name == "ny") {
			stream >> NY;
		}
		else if (name.name == "nz") {
			stream >> NZ;
		}
		else if (name.name == "alpha") {
			stream >> ALPHA;
		}
		else {
			string none;
			stream >> none;
		}
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA);
}

PlyVertex::PlyVertex(vector<VertexName> names, fstream& file)
{
	double X = 0, Y = 0, Z = 0;
	unsigned short R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0;
	unsigned short ALPHA = 255;
	for (auto name : names)
	{
		if (name.name == "x") {
			file >> X;
		}
		else if (name.name == "y") {
			file >> Y;
		}
		else if (name.name == "z") {
			file >> Z;
		}
		else if (name.name == "red" || name.name == "r") {
			file >> R;
		}
		else if (name.name == "green" || name.name == "g") {
			file >> G;
		}
		else if (name.name == "blue" || name.name == "b") {
			file >> B;
		}
		else if (name.name == "nx") {
			file >> NX;
		}
		else if (name.name == "ny") {
			file >> NY;
		}
		else if (name.name == "nz") {
			file >> NZ;
		}
		else if (name.name == "alpha") {
			file >> ALPHA;
		}
		else {
			string none;
			file >> none;
		}
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA);
}

PlyVertex::PlyVertex(double const X, double const Y, double const Z, unsigned short const R = 0, unsigned short const G = 0, unsigned short const B = 0)
{
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255);
}

void PlyVertex::set_all_properties(double const X, double const Y, double const Z, unsigned short const R, unsigned short const G, unsigned short const B, double const NX, double const NY, double const NZ, unsigned short const ALPHA)
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
unsigned short PlyVertex::R() const
{
	return __R;
}
PlyVertex& PlyVertex::R(unsigned short const R)
{
	__R = R;
	return *this;
}
unsigned short PlyVertex::G() const
{
	return __G;
}
PlyVertex& PlyVertex::G(unsigned short const G)
{
	__G = G;
	return *this;
}
unsigned short PlyVertex::B() const
{
	return __B;
}
PlyVertex& PlyVertex::B(unsigned short const B)
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
unsigned short PlyVertex::ALPHA() const
{
	return __ALPHA;
}
PlyVertex& PlyVertex::ALPHA(unsigned short const ALPHA)
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
	return __X < vertex.X() || __Y < vertex.Y() || __Z < vertex.Z();
}

bool PlyVertex::operator>(PlyVertex const& vertex) const
{
	return __X > vertex.X() || __Y > vertex.Y() || __Z > vertex.Z();
}

void PlyVertex::offset(double const offset_x, double const offset_y, double const offset_z)
{
	__X += offset_x;
	__Y += offset_y;
	__Z += offset_z;
}
#endif