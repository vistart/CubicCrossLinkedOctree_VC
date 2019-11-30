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

#ifndef __PLY_VERTEX_LIST__
#define __PLY_VERTEX_LIST__

#include "PlyVertex.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class PlyVertexList
{
public:
	PlyVertexList();
	PlyVertexList(unsigned int const, fstream&);
	auto GetVertexCount();
	vector<PlyVertex> GetVertices();
	~PlyVertexList();
	PlyVertexList& operator<<(string);
	PlyVertexList& operator<<(fstream&);
	PlyVertexList& operator<<(PlyVertex const&);
	enum PropertyDataType { INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64 };
	struct VertexName {
		string name;
		int type;
	};
protected:
	vector<PlyVertex> vertices;
	vector<VertexName> names;
	VertexName read_element_vertex_names(fstream&);
};

#endif