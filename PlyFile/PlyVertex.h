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
#include "Point.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class PlyVertex : public Point
{
public:
	struct VertexName {
		int name;
		int type;
	};
	PlyVertex() = default;
	PlyVertex(vector<VertexName> const&, string const&);
	PlyVertex(vector<VertexName> const&, fstream&, PlyFileEncoding::FileEncoding const&);
	PlyVertex(double const, double const, double const, unsigned char const, unsigned char const, unsigned char const);
	~PlyVertex() = default;
	enum PropertyNames { PROPERTY_NONE,
		                 PROPERTY_X, PROPERTY_Y, PROPERTY_Z,
		                 PROPERTY_R, PROPERTY_G, PROPERTY_B,
		                 PROPERTY_NX, PROPERTY_NY, PROPERTY_NZ,
		                 PROPERTY_ALPHA, PROPERTY_CONFIDENCE, PROPERTY_INTENSITY };
	friend ostream& operator<<(ostream& stream, PlyVertex const& vertex)
	{
		stream << "(" << setprecision(10) << vertex.__X << "," << setprecision(10) << vertex.__Y << "," << setprecision(10) << vertex.__Z << ")";
		return stream;
	}
};

#endif