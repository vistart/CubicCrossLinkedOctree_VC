#ifndef __PLY_H__
#include "PlyFile.h"
#endif

#ifdef __PLY_H__
#include<iostream>
#include<algorithm>

#pragma region Constructor & Destructor
/*
 * Summary: Instantiate the current object from the ply file.
 * Parameters:
 *     std::string file_path: the file path to store the ply data.
 */
PlyFile::PlyFile(string file_path)
{
	open(file_path);
	read(this->file);
}

PlyFile::~PlyFile()
{
	if (this->file.is_open()) {
		this->file.close();
	}
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

bool PlyFile::read(fstream& file)
{
	file.seekg(0, ios::beg);
	bool is_header = true;
	unsigned int element_count = 0;
	
	string buffer;

	int pos = file.tellg();
	while (file >> buffer)
	{
		cout << "The Position of File Pointer: " << pos << endl;
		pos = file.tellg();
		if (is_header) {
			transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
			if (buffer.c_str() == string("ply")) {
				cout << "PLY" << endl;
				this->set_file_format("ply");
				continue;
			}

			if (buffer.c_str() == string("format")) {
				string encoding;
				float version;
				file >> encoding >> version;
				cout << "FORMAT: " << encoding << " VERSION:" << version << endl;
				continue;
			}

			if (buffer.c_str() == string("comment")) {
				string comment;
				getline(file, comment);
				cout << "comment: " << comment << endl;
				continue;
			}

			if (buffer.c_str() == string("element")) {
				string element_name;
				file >> element_name >> element_count;
				cout << "Element: " << element_name << element_count << endl;

				while (file >> buffer) {
					transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
					if (buffer.c_str() == string("property")) {
						string property_type;
						string property_name;
						file >> property_type >> property_name;
						cout << "Property: " << property_type << property_name << endl;
						pos = file.tellg();
					}
					else {
						file.seekg(pos, ios::beg);
						cout << file.tellg() << endl;
						break;
					}
				}
				continue;
			}

			if (buffer.c_str() == string("end_header")) {
				cout << "END of HEADER" << endl;
				is_header = false;
				continue;
			}
		}
	}
	return true;
}

#pragma region File Format
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
#pragma endregion

#endif