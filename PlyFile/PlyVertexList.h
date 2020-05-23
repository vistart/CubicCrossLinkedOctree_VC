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

/*
 This class is used to describe the list containing all the vertices.
 */
class PlyVertexList : public PointList<PlyVertex, PlyVertexList>
{
public:
	/*
	 Initialize the vertex list.
	 */
	PlyVertexList();

	/*
	 Destroy the vertex list.
	 */
	~PlyVertexList();

	/*
	 Add a vertex to this list.
	 
	 @param string const&: the string describing the vertex.
	 @return PlyVertexList&: self.
	 */
	PlyVertexList& operator<<(string const&);

	/*
	 Add a vertex to this list.

	 @param fstream&: the file stream containing the vertex.
	 @return PlyVertexList&: self.
	 */
	PlyVertexList& operator<<(fstream&);

	/*
	 Add a vertex to this list.

	 @param PlyVertex const&: the vertex to be added.
	 @return PlyVertexList&: self.
	 */
	PlyVertexList& operator<<(PlyVertex const&);

	/*
	 Specify the current file encoding.

	 Note: The property encoding of the PLY file is unified, so you need to specify the file 
	 encoding once before reading the property value, and it is strongly not recommended to change thereafter.
	 If you need to specify this parameter twice, you need to know the consequences of doing so.

	 @param PlyFileEncoding const&: the target file encoding.
	 @return PlyVertexList&: self.
	 */
	PlyVertexList& operator<<(PlyFileEncoding const&);

	/*
	 Read property names and corresponding types.

	 @param fstream&: the target file.
	 @return bool: true if no exceptions occured.
	 */
	bool read_element_vertex_names(fstream&);

	/*
	 Set the count of vertex according to the value stored in ply file header.
	 Note: It is strongly recommended to set it only once before reading the
	 vertex properties.
	 
	 @param unsigned int const: the target count.
	 */
	void SetCountInHeader(unsigned int const);

	/*
	 Get the count of vertex.

	 @return unsigned int const: the target count.
	 */
	unsigned int GetCountInHeader() const;

	/*
	 Names of all properties.
	 Note: Please arrange their order in the vector according to the order of the property names
	 listed in the file header. The property names of the PLY file are unified, so you need to 
	 specify the property names once before reading the property value, and it is strongly not 
	 recommended to change thereafter.
	 */
	vector<PlyVertex::VertexName> names;

	/*
	 Return the pointer pointing to all vertices stored in this instance.

	 @return shared_ptr<vector<PlyVertex>>: the shared pointer to all vertices. 
	 */
	shared_ptr<vector<PlyVertex>> GetPoints() override;
protected:
	unsigned int count_in_header = 0;
	PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
	shared_ptr<vector<PlyVertex>> points;
};

#endif