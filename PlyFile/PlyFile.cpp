/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
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
	this->filename = file_path;
	this->FileEncoding = make_shared<PlyFileEncoding>();
	this->CommentList = make_shared<PlyCommentList>();
	this->point_list = make_shared<PlyVertexList>();
	this->EdgeList = make_shared<PlyEdgeList>();
	this->FaceList = make_shared<PlyFaceList>();
	open(this->filename);
	if (read(this->file))
		this->valid = true;
}

PlyFile::~PlyFile()
{
	if (this->file.is_open()) {
		this->file.close();
	}
	this->FaceList = nullptr;
	this->EdgeList = nullptr;
	this->point_list = nullptr;
	this->CommentList = nullptr;
	this->FileEncoding = nullptr;
	this->filename = "";
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
bool PlyFile::read_file_encoding(string tag, fstream& file)
{
	if (tag != string("format"))
		return false;
	auto& encoding = this->FileEncoding;
	*encoding << file;
	return true;
}
#pragma endregion

#pragma region Comment

bool PlyFile::read_comment(string tag, fstream& file)
{
	if (tag != string(PLY_TAG_COMMENT))
		return false;

	string comment;
	getline(file, comment);
	*this->CommentList << comment;
	return true;
}
#pragma endregion

bool PlyFile::open(string file_path)
{
	if (this->file.is_open()) {
		this->file.close();
	}
	//std::cout << file_path << std::endl;
	this->file.open(file_path, ios::in | ios::binary);
	return this->file.good();
}

#pragma region Vertex
bool PlyFile::read_element_vertex_names(fstream& file)
{
	this->point_list->read_element_vertex_names(file);
	PlyVertex::VertexName const back = this->point_list->names.back();
#ifdef _DEBUG
	cout << "Property: " << back.name << " | " << back.type << endl;
#endif
	return true;
}

bool PlyFile::read_element_vertex_encoding(PlyFileEncoding const& file_encoding)
{
	auto& vertex_list = *this->point_list;
	vertex_list << file_encoding;
	return true;
}

bool PlyFile::read_element_vertex(fstream& file)
{
	auto& vertex_list = *this->point_list;
	vertex_list << file;
	return true;
}

shared_ptr<PlyVertexList> PlyFile::GetPointList()
{
	return this->point_list;
}
#pragma endregion

#pragma region Face
bool PlyFile::read_element_face_names(fstream& file)
{
	string face;
	getline(file, face);
#ifdef _DEBUG
	cout << "Element: " << face << endl;
#endif
	return true;
}
#pragma endregion

#pragma region Edge
bool PlyFile::read_element_edge_names(fstream& file)
{
	string edge;
	getline(file, edge);
#ifdef _DEBUG
	cout << "Element: " << edge << endl;
#endif
	return true;
}
#pragma endregion

#pragma region User-Defined Elements
bool PlyFile::read_element_user_defined_names(fstream& file)
{
	return true;
}
#pragma endregion

bool PlyFile::read_header(fstream& file)
{
	unsigned int element_count = 0;
	string buffer;
	enum ELEMENTS { NONE, VERTEX, FACE, EDGE, USER_DEFINED };
	int current_elements = NONE;

	// Regardless of the status of the current file, it searches from the beginning.
	file.seekg(0, ios::beg);

    // Reading the header of a ply file.
	while (file >> buffer)
	{
		// Regardless of the case of the current word, it is converted to lower case for comparison.
		transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

		// If `buffer` equals to "property", the content after it is regarded as the property name.
		if (buffer.c_str() == string("property")) {
			// There are three default property names: vertex, face and edge.
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
			// All others are user-defined.
			if (current_elements == USER_DEFINED) {
				read_element_user_defined_names(file);
				continue;
			}
		}

		current_elements = NONE;

		// If `buffer` equals to "ply", it indicates that the current file format is ply.
		if (buffer.c_str() == string("ply")) {
			cout << "PLY" << endl;
			this->set_file_format("ply");
			continue;
		}


		// If `buffer` equals to "format", it indicates that the following content is format and encoding.
		if (read_file_encoding(buffer.c_str(), file)) {
#ifdef _DEBUG
			cout << "FORMAT: " << (*this->FileEncoding).Encoding() << " VERSION:" << (*this->FileEncoding).Version() << endl;
#endif
			continue;
		}

		// If `buffer` equals to "comment", it indicates that the following content is comment.
		if (read_comment(buffer.c_str(), file)) {
#ifdef _DEBUG
			for (auto comment : (*this->CommentList).getComments())
			{
				cout << "Comment: " << comment << endl;
			}
#endif
			continue;
		}

		// If `buffer` equals to "element", it indicates that the following content is element names.
		if (buffer.c_str() == string("element")) {
			string element_name;
			file >> element_name >> element_count;

			if (element_name == "vertex") {
				current_elements = VERTEX;
				auto point_list = this->GetPointList();
				point_list->SetCountInHeader(element_count);
#ifdef _DEBUG
				cout << "Element: " << element_name << point_list->GetCountInHeader() << endl;
#endif
				continue;
			}

			if (element_name == "face") {
				current_elements = FACE;
				continue;
			}

			if (element_name == "edge") {
				current_elements = EDGE;
				continue;
			}
			continue;
		}

		if (buffer.c_str() == string("end_header")) {
#ifdef _DEBUG
			cout << "END of HEADER" << endl;
#endif
			break;
		}
	}
	return true;
}

bool PlyFile::read_body(fstream& file)
{
	file.get(); // throw out the last character ('\n').
	read_element_vertex_encoding(*this->FileEncoding);
	unsigned int const vertex_count_in_header = this->GetPointList()->GetCountInHeader();
	for (unsigned int i = 0; i < vertex_count_in_header; i++)
	{
#ifdef _DEBUG
		cout << "file pointer: " << file.tellg() << endl;
#endif
		read_element_vertex(file);
	}
	return true;
}


bool PlyFile::read(fstream& file)
{
	if (!this->read_header(file)) {
		return false;
	}
	if (!this->read_body(file)) {
		return false;
	}
	return true;
}

#endif