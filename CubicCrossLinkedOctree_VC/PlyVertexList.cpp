#ifndef __PLY_VERTEX_LIST__
#include "PlyVertexList.h"
#endif

#ifdef __PLY_VERTEX_LIST__
PlyVertexList::PlyVertexList()
{

}

PlyVertexList::PlyVertexList(unsigned int count, fstream& file)
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
#endif