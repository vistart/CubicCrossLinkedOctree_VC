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

#ifndef __PLY_H__
#define __PLY_H__

#include "PlyVertexList.h"
#include "PlyFaceList.h"
#include "PlyEdgeList.h"
#include "PlyCommentList.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PlyFile
{
public:
#pragma region Constructor & Destructor
	explicit PlyFile(string);
	~PlyFile();
#pragma endregion

#pragma region File Format
	string GetFileFormat();
#pragma endregion

#pragma region Comment
	PlyCommentList& GetCommentList();
#pragma endregion

#pragma region Vertex
	PlyVertexList GetVertexList();
#pragma endregion

#pragma region Face
	PlyFaceList GetFaceList();
#pragma endregion

#pragma region Edge
	PlyEdgeList GetEdgeList();
#pragma endregion

	bool GetIsValid();

protected:
	fstream file;
	bool valid = false;
	bool open(string);
	enum Tag { PLY, FORMAT, COMMENT, ELEMENT, PROPERTY, END_HEADER };
	bool read(fstream&);

#pragma region File Format
	enum FileFormatType { FILE_FORMAT_PLY };
	int file_format = FILE_FORMAT_PLY;
	bool set_file_format(string);
#pragma endregion

#pragma region File Encoding
	bool read_file_encoding(string, fstream&);
#pragma endregion

#pragma region PropertyDataType
	enum PropertyDataType { INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64};
#pragma endregion

#pragma region Comment
	bool read_comment(string, fstream&);
#pragma endregion

#pragma region Vertex
#pragma endregion

#pragma region Face
#pragma endregion

#pragma region Edge
#pragma endregion

#pragma region User-Defined Elements
#pragma endregion
};

#endif