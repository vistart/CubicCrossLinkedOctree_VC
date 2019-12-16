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
#include "PointList.h"
#include "PlyFileEncoding.h"
#include "PlyPropertyType.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class PlyVertexList : public PointList<PlyVertex>
{
public:
	PlyVertexList();
	~PlyVertexList();
	PlyVertexList& operator<<(string const&);
	PlyVertexList& operator<<(fstream&);
	PlyVertexList& operator<<(PlyVertex const&);
	PlyVertexList& operator<<(PlyFileEncoding const&);
	bool read_element_vertex_names(fstream&);
	void SetCountInHeader(unsigned int const);
	unsigned int GetCountInHeader() const;
	vector<PlyVertex::VertexName> names;
	shared_ptr<vector<PlyVertex>> GetPoints() override;
protected:
	unsigned int count_in_header = 0;
	PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
	shared_ptr<vector<PlyVertex>> points;
};

#endif