/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX__
#include "PlyVertex.h"
#endif

#ifdef __PLY_VERTEX__
PlyVertex::PlyVertex()
{

}

PlyVertex::PlyVertex(string vertex)
{
	stringstream stream(vertex);
	double X, Y, Z;
	char R = 0, G = 0, B = 0;
	stream >> X >> Y >> Z;
	if (has_RGB) {
		stream >> R >> G >> B;
	}
	this->__X = X;
	this->__Y = Y;
	this->__Z = Z;
	this->__R = R;
	this->__G = G;
	this->__B = B;
}

PlyVertex::PlyVertex(fstream& file)
{
	double X, Y, Z;
	char R = 0, G = 0, B = 0;
	file >> X >> Y >> Z;
	if (has_RGB) {
		file >> R >> G >> B;
	}
	this->__X = X;
	this->__Y = Y;
	this->__Z = Z;
	this->__R = R;
	this->__G = G;
	this->__B = B;
}

PlyVertex::PlyVertex(double const X, double const Y, double const Z, char const R = 0, char const G = 0, char const B = 0)
{
	this->__X = X;
	this->__Y = Y;
	this->__Z = Z;
	this->__R = R;
	this->__G = G;
	this->__B = B;
}

PlyVertex::~PlyVertex()
{

}

double PlyVertex::X() const
{
	return __X;
}
PlyVertex& PlyVertex::X(int const X)
{
	__X = X;
	return *this;
}
double PlyVertex::Y() const
{
	return __Y;
}
PlyVertex& PlyVertex::Y(int const Y)
{
	__Y = Y;
	return *this;
}
double PlyVertex::Z() const
{
	return __Z;
}
PlyVertex& PlyVertex::Z(int const Z)
{
	__Z = Z;
	return *this;
}
char PlyVertex::R() const
{
	return __R;
}
PlyVertex& PlyVertex::R(char const R)
{
	__R = R;
	return *this;
}
char PlyVertex::G() const
{
	return __G;
}
PlyVertex& PlyVertex::G(char const G)
{
	__G = G;
	return *this;
}
char PlyVertex::B() const
{
	return __B;
}
PlyVertex& PlyVertex::B(char const B)
{
	__B = B;
	return *this;
}

bool PlyVertex::operator==(PlyVertex const& vertex) const
{
	bool result = (__X == vertex.__X && __Y == vertex.__Y && __Z == vertex.__Z);
	if (has_RGB)
	{
		result = (result && __R == vertex.__R && __G == vertex.__G && __B == vertex.__B);
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