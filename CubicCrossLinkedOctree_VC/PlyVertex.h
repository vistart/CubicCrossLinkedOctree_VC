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

#include "PlyFileEncoding.h"
#include "PlyPropertyType.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <type_traits>

using namespace std;

class PlyVertex
{
public:
	struct VertexName {
		int name;
		int type;
	};
	PlyVertex() = default;
	PlyVertex(vector<VertexName> const&, string const&);
	PlyVertex(vector<VertexName> const&, fstream&, PlyFileEncoding::FileEncoding const&);
	PlyVertex(double const, double const, double const, unsigned short const, unsigned short const, unsigned short const);
	~PlyVertex() = default;
	enum PropertyNames { PROPERTY_NONE,
		                 PROPERTY_X, PROPERTY_Y, PROPERTY_Z,
		                 PROPERTY_R, PROPERTY_G, PROPERTY_B,
		                 PROPERTY_NX, PROPERTY_NY, PROPERTY_NZ,
		                 PROPERTY_ALPHA, PROPERTY_CONFIDENCE, PROPERTY_INTENSITY };
	double X() const;
	PlyVertex& X(double const);
	double Y() const;
	PlyVertex& Y(double const);
	double Z() const;
	PlyVertex& Z(double const);
	unsigned short R() const;
	PlyVertex& R(unsigned short const);
	unsigned short G() const;
	PlyVertex& G(unsigned short const);
	unsigned short B() const;
	PlyVertex& B(unsigned short const);
	double NX() const;
	PlyVertex& NX(double const);
	double NY() const;
	PlyVertex& NY(double const);
	double NZ() const;
	PlyVertex& NZ(double const);
	unsigned short ALPHA() const;
	PlyVertex& ALPHA(unsigned short const);
	double CONFIDENCE() const;
	PlyVertex& CONFIDENCE(double const);
	double INTENSITY() const;
	PlyVertex& INTENSITY(double const);
	bool operator==(PlyVertex const&) const;
	bool operator!=(PlyVertex const&) const;
	bool operator<(PlyVertex const&) const;
	bool operator>(PlyVertex const&) const;
	friend ostream& operator<<(ostream& stream, PlyVertex const& vertex)
	{
		stream << "(" << setprecision(10) << vertex.__X << "," << setprecision(10) << vertex.__Y << "," << setprecision(10) << vertex.__Z << ")";
		return stream;
	}
	void offset(double const, double const, double const);
	bool has_RGB = false;
	bool has_normal = false;
	bool has_alpha = false;
	bool has_confidence = false;
	bool has_intensity = false;
protected:
	double __X = 0;
	double __Y = 0;
	double __Z = 0;
	unsigned short __R = 0;
	unsigned short __G = 0;
	unsigned short __B = 0;
	double __NX = 0;
	double __NY = 0;
	double __NZ = 0;
	unsigned short __ALPHA = 255;
	double __CONFIDENCE = 1;
	double __INTENSITY = 0.5;
	void set_all_properties(double const, double const, double const,
		                    unsigned short const, unsigned short const, unsigned short const,
		                    double const, double const, double const,
		                    unsigned short const, double const, double const);
};

#endif