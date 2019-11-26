#ifndef __PLY_VERTEX_LIST__
#include "PlyVertexList.h"
#endif

#ifdef __PLY_VERTEX_LIST__
PlyVertexList::PlyVertexList()
{

}

PlyVertexList::PlyVertexList(unsigned int count, fstream& file)
{
	for (int i = 0; i < count; i++)
	{
		auto vertex = new PlyVertex(file);
		vertices.push_back(*vertex);
	}
}

PlyVertexList::~PlyVertexList()
{
	for (auto& vertex : vertices) {
		vertex.~PlyVertex();
	}
}

unsigned int PlyVertexList::GetVertexCount()
{
	return vertices.size();
}

vector<PlyVertex> PlyVertexList::GetVertices()
{
	return vertices;
}
#endif