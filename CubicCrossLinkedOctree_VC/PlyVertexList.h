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
#include "SingletonBase.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class PlyVertexList : public SingletonBase<PlyVertexList>
{
private:
	PlyVertexList();
	~PlyVertexList();
	friend class SingletonBase<PlyVertexList>;
public:
	auto GetVertexCount();
	vector<PlyVertex> GetVertices();
	PlyVertexList& operator<<(string);
	PlyVertexList& operator<<(fstream&);
	PlyVertexList& operator<<(PlyVertex const&);
	enum PropertyDataType { INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64 };
	struct VertexName {
		string name;
		int type;
	};
	bool read_element_vertex_names(fstream&);
	vector<VertexName> GetNames();
	PlyVertexList(PlyVertexList const&) = delete;
	PlyVertexList& operator=(PlyVertexList const&) = delete;
	static PlyVertexList& get();
	PlyVertex& operator[](int);
	void SetCountInHeader(unsigned int const);
	unsigned int GetCountInHeader();
	PlyVertex& back();
protected:
	vector<PlyVertex> vertices;
	vector<VertexName> names;
	unsigned int count_in_header = 0;
};

#endif