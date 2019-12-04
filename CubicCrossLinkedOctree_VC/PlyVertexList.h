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

#ifndef __PLY_VERTEX_LIST_H__
#define __PLY_VERTEX_LIST_H__

#include "PlyVertex.h"
#include "PlyFileEncoding.h"
#include "PlyPropertyType.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class PlyVertexList
{
public:
	PlyVertexList() = default;
	~PlyVertexList();
	vector<PlyVertex> GetVertices() const&;
	PlyVertexList& operator<<(string const&);
	PlyVertexList& operator<<(fstream&);
	PlyVertexList& operator<<(PlyVertex const&);
	PlyVertexList& operator<<(PlyFileEncoding const&);
	bool read_element_vertex_names(fstream&);
	vector<PlyVertex::VertexName> GetNames() const&;
	PlyVertex& operator[](int const);
	void SetCountInHeader(unsigned int const);
	unsigned int GetCountInHeader() const;
	PlyVertex& back();
protected:
	vector<PlyVertex> vertices;
	vector<PlyVertex::VertexName> names;
	unsigned int count_in_header = 0;
	PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
};

#endif