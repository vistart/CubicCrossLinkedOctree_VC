#ifndef __PLY_VERTEX_LIST__
#include "PlyVertexList.h"
#endif

#ifdef __PLY_VERTEX_LIST__
PlyVertexList::PlyVertexList()
{

}

PlyVertexList::PlyVertexList(unsigned int const count, fstream& file)
{
	for (unsigned int i = 0; i < count; i++)
	{
		auto vertex = new PlyVertex(file);
		vertices.push_back(*vertex);
	}
}

PlyVertexList::~PlyVertexList()
{
	vertices.erase(vertices.begin(), vertices.end());
}

auto PlyVertexList::GetVertexCount()
{
	return vertices.size();
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

PlyVertexList::VertexName PlyVertexList::read_element_vertex_names(fstream& file)
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
		vertex_name.type = INT32;
	}
	if (type == string("float64")) {
		vertex_name.type = FLOAT64;
	}
	return vertex_name;
}
#endif