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

#ifndef __PLY_VERTEX_H__
#define __PLY_VERTEX_H__

#include <fstream>
#include <sstream>

using namespace std;

class PlyVertex
{
public:
	PlyVertex();
	PlyVertex(string);
	PlyVertex(fstream&);
	PlyVertex(double const, double const, double const, unsigned char const, unsigned char const, unsigned char const);
	~PlyVertex() = default;
	double X() const;
	PlyVertex& X(double const X);
	double Y() const;
	PlyVertex& Y(double const Y);
	double Z() const;
	PlyVertex& Z(double const Z);
	unsigned char R() const;
	PlyVertex& R(unsigned char const R);
	unsigned char G() const;
	PlyVertex& G(unsigned char const G);
	unsigned char B() const;
	PlyVertex& B(unsigned char const B);
	double NX() const;
	PlyVertex& NX(double const NX);
	double NY() const;
	PlyVertex& NY(double const NY);
	double NZ() const;
	PlyVertex& NZ(double const NZ);
	unsigned char ALPHA() const;
	PlyVertex& ALPHA(unsigned char const ALPHA);
	bool operator==(PlyVertex const&) const;
	bool operator!=(PlyVertex const&) const;
	bool operator<(PlyVertex const&) const;
	bool operator>(PlyVertex const&) const;
	friend ostream& operator<<(ostream& stream, PlyVertex const& vertex)
	{
		stream << "(" << vertex.__X << "," << vertex.__Y << "," << vertex.__Z << ")";
		return stream;
	}
	void offset(double const, double const, double const);
	bool has_RGB = false;
	bool has_normal = false;
	bool has_alpha = false;
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
	void set_all_properties(double const, double const, double const, unsigned char const, unsigned char const, unsigned char const, double const, double const, double const, unsigned char const);
};

#endif