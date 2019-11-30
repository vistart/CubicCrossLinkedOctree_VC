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

#ifndef __PLY_VERTEX__
#define __PLY_VERTEX__

#include <fstream>

using namespace std;

class PlyVertex
{
public:
	PlyVertex();
	PlyVertex(fstream&);
	PlyVertex(double const, double const, double const);
	PlyVertex(double const, double const, double const, char const, char const, char const);
	~PlyVertex();
	double X() const;
	PlyVertex& X(int const X);
	double Y() const;
	PlyVertex& Y(int const Y);
	double Z() const;
	PlyVertex& Z(int const Z);
	char R() const;
	PlyVertex& R(char const R);
	char G() const;
	PlyVertex& G(char const G);
	char B() const;
	PlyVertex& B(char const B);
	bool operator==(PlyVertex const&) const;
	bool operator!=(PlyVertex const&) const;
	bool operator<(PlyVertex const&) const;
	bool operator>(PlyVertex const&) const;
	friend std::ostream& operator<<(std::ostream& stream, PlyVertex const& vertex)
	{
		stream << "(" << vertex.__X << "," << vertex.__Y << "," << vertex.__Z << ")";
		return stream;
	}
	void offset(int const, int const, int const);
protected:
	double __X;
	double __Y;
	double __Z;
	char __R;
	char __G;
	char __B;
	bool has_RGB = false;
};

#endif