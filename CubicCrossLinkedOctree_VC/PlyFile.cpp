/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FILE_H__
#include "PlyFile.h"
#endif

#ifdef __PLY_FILE_H__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

#pragma region Constructor & Destructor
/*
 * Summary: Instantiate the current object from the ply file.
 * Parameters:
 *     std::string file_path: the file path to store the ply data.
 */
PlyFile::PlyFile(string file_path)
{
	open(file_path);
	if (read(this->file))
		this->valid = true;
}

PlyFile::~PlyFile()
{
	if (this->file.is_open()) {
		this->file.close();
	}
}

bool PlyFile::GetIsValid()
{
	return this->valid;
}
#pragma endregion

#pragma region File Format
string PlyFile::GetFileFormat()
{
	if (this->file_format == FILE_FORMAT_PLY)
	{
		return "ply";
	}
	return "unknown type!";
}

bool PlyFile::set_file_format(string file_format)
{
	if (file_format == "ply") {
		this->file_format = FILE_FORMAT_PLY;
		return true;
	}
	return false;
}
#pragma endregion

#pragma region File Encoding
PlyFileEncoding& PlyFile::GetFileEncoding()
{
	return PlyFileEncoding::get();
}

bool PlyFile::read_file_encoding(string tag, fstream& file)
{
	if (tag != string("format"))
		return false;
	auto& encoding = this->GetFileEncoding();
	encoding << file;
	return true;
}
#pragma endregion

#pragma region Comment

PlyCommentList& PlyFile::GetCommentList()
{
	return PlyCommentList::get();
}

bool PlyFile::read_comment(string tag, fstream& file)
{
	if (tag != string(PLY_TAG_COMMENT))
		return false;

	string comment;
	getline(file, comment);
	this->GetCommentList() << comment;
	return true;
}
#pragma endregion

bool PlyFile::open(string file_path)
{
	if (this->file.is_open()) {
		this->file.close();
	}
	//std::cout << file_path << std::endl;
	this->file.open(file_path);
	return this->file.good();
}

#pragma region Vertex
PlyVertexList& PlyFile::GetVertexList()
{
	return PlyVertexList::get();
}

bool PlyFile::read_element_vertex_names(fstream& file)
{
	GetVertexList().read_element_vertex_names(file);
	PlyVertex::VertexName const back = GetVertexList().GetNames().back();
	cout << "Property: " << back.name << " | " << back.type << endl;
	return true;
}

bool PlyFile::read_element_vertex(fstream& file)
{
	auto& vertex_list = GetVertexList();
	vertex_list << file;
	return true;
}
#pragma endregion

#pragma region Face
bool PlyFile::read_element_face_names(fstream& file)
{
	string face;
	getline(file, face);
	cout << "Element: " << face << endl;
	return true;
}
#pragma endregion

#pragma region Edge
bool PlyFile::read_element_edge_names(fstream& file)
{
	string edge;
	getline(file, edge);
	cout << "Element: " << edge << endl;
	return true;
}
#pragma endregion

#pragma region User-Defined Elements
bool PlyFile::read_element_user_defined_names(fstream& file)
{
	return true;
}
#pragma endregion

bool PlyFile::read(fstream& file)
{
	file.seekg(0, ios::beg);
	unsigned int element_count = 0;
	
	string buffer;

	enum ELEMENTS { NONE, VERTEX, FACE, EDGE, USER_DEFINED };
	int current_elements = NONE;
	while (file >> buffer)
	{
		transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
		if (buffer.c_str() == string("property")) {
			if (current_elements == VERTEX) {
				read_element_vertex_names(file);
				continue;
			}
			if (current_elements == FACE) {
				read_element_face_names(file);
				continue;
			}
			if (current_elements == EDGE) {
				read_element_edge_names(file);
				continue;
			}
			if (current_elements == USER_DEFINED) {
				read_element_user_defined_names(file);
				continue;
			}
		}

		current_elements = NONE;

		if (buffer.c_str() == string("ply")) {
			cout << "PLY" << endl;
			this->set_file_format("ply");
			continue;
		}

		if (read_file_encoding(buffer.c_str(), file)) {
			cout << "FORMAT: " << this->GetFileEncoding().Encoding() << " VERSION:" << this->GetFileEncoding().Version() << endl;
			continue;
		}

		if (read_comment(buffer.c_str(), file)) {
			for (auto comment : this->GetCommentList().getComments())
			{
				cout << "Comment: " << comment << endl;
			}
			continue;
		}

		if (buffer.c_str() == string("element")) {
			string element_name;
			file >> element_name >> element_count;

			if (element_name == string("vertex")) {
				current_elements = VERTEX;
				GetVertexList().SetCountInHeader(element_count);
				cout << "Element: " << element_name << GetVertexList().GetCountInHeader() << endl;
				continue;
			}

			if (element_name == string("face")) {
				current_elements = FACE;
				continue;
			}

			if (element_name == string("edge")) {
				current_elements = EDGE;
				continue;
			}
			continue;
		}

		if (buffer.c_str() == string("end_header")) {
			cout << "END of HEADER" << endl;
			break;
		}
	}
	unsigned int const count_in_header = GetVertexList().GetCountInHeader();
	for (unsigned int i = 0; i < count_in_header; i++)
	{
		read_element_vertex(file);
	}
	auto& vertex_list = GetVertexList();
	auto& vertex = vertex_list.back();
	cout << setiosflags(ios::fixed) << vertex << endl;
	return true;
}

#endif