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
#include <vector>
using namespace std;

class PlyVertexList
{
public:
	PlyVertexList();
	PlyVertexList(unsigned int, fstream&);
	unsigned int GetVertexCount();
	vector<PlyVertex> GetVertices();
	~PlyVertexList();
protected:
	vector<PlyVertex> vertices;
};

#endif