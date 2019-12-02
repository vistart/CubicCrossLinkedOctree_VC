/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX_LIST_H__
#include "PlyVertexList.h"
#endif

#ifdef __PLY_VERTEX_LIST_H__
vector<PlyVertexList::VertexName> PlyVertexList::GetNames()
{
	return names;
}

PlyVertexList::~PlyVertexList()
{
	vertices.erase(vertices.begin(), vertices.end());
	vertices.~vector();
}

vector<PlyVertex> PlyVertexList::GetVertices()
{
	return vertices;
}

PlyVertexList& PlyVertexList::operator<<(string str_vertex)
{
	PlyVertex vertex(str_vertex);
	this->vertices.push_back(vertex);
	return *this;
}

PlyVertexList& PlyVertexList::operator<<(fstream& file)
{
	PlyVertex vertex(file);
	this->vertices.push_back(vertex);
	return *this;
}

PlyVertexList& PlyVertexList::operator<<(PlyVertex const& vertex)
{
	this->vertices.push_back(vertex);
	return *this;
}

bool PlyVertexList::read_element_vertex_names(fstream& file)
{
	string type;
	string name;
	file >> type >> name;
	VertexName vertex_name = { name, 0 };
	if (type == string("int8")) {
		vertex_name.type = INT8;
	}
	if (type == string("uint8")) {
		vertex_name.type = UINT8;
	}
	if (type == string("int16")) {
		vertex_name.type = INT16;
	}
	if (type == string("uint16")) {
		vertex_name.type = UINT16;
	}
	if (type == string("int32")) {
		vertex_name.type = INT32;
	}
	if (type == string("uint32")) {
		vertex_name.type = UINT32;
	}
	if (type == string("float32")) {
		vertex_name.type = FLOAT32;
	}
	if (type == string("float64")) {
		vertex_name.type = FLOAT64;
	}
	this->names.push_back(vertex_name);
	return true;
}

PlyVertex& PlyVertexList::operator[](int i)
{
	return vertices[i];
}

void PlyVertexList::SetCountInHeader(unsigned int const count)
{
	this->count_in_header = count;
}

unsigned int PlyVertexList::GetCountInHeader()
{
	return this->count_in_header;
}

PlyVertex& PlyVertexList::back()
{
	return vertices.back();
}
#endif
