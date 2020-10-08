/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_EDGE_LIST_H__
#include "PlyEdgeList.h"
#endif

#ifdef __PLY_EDGE_LIST_H__
#include <iostream>
using namespace std;
PlyEdgeList& PlyEdgeList::operator<<(std::string const&)
{
	return *this;
}
PlyEdgeList& PlyEdgeList::operator<<(std::fstream&)
{
	return *this;
}
PlyEdgeList& PlyEdgeList::operator<<(std::shared_ptr<PlyEdge> const& edge)
{
	this->edges->emplace_back(edge);
	return *this;
}
PlyEdgeList& PlyEdgeList::operator<<(PlyFileEncoding const& fe)
{
	this->file_encoding = fe.GetDefinition();
	return *this;
}
bool PlyEdgeList::read_element_edge_names(std::fstream& file)
{
	return true;
}
void PlyEdgeList::demo()
{
	cout << "demo" << endl;
}
void PlyEdgeList::SetCountInHeader(unsigned int count)
{
	this->count_in_header = count;
}
unsigned int PlyEdgeList::GetCountInHeader() const
{
	return this->count_in_header;
}
std::shared_ptr<std::vector<std::shared_ptr<PlyEdge>>> PlyEdgeList::GetEdges() const
{
	return this->edges;
}
#endif
