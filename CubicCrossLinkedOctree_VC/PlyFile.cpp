/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_H__
#include "PlyFile.h"
#endif

#ifdef __PLY_H__
#include<iostream>
#include<sstream>
#include<algorithm>

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

bool PlyFile::read(fstream& file)
{
	file.seekg(0, ios::beg);
	bool is_header = true;
	unsigned int element_count = 0;
	
	string buffer;

	while (file >> buffer)
	{
		if (is_header) {
			transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
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
				cout << "Element: " << element_name << element_count << endl;

				if (element_name == string("vertex")) {
					
				}

				if (element_name == string("face")) {

				}

				if (element_name == string("edge")) {

				}

				while (file >> buffer) {
					transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
					if (buffer.c_str() == string("property")) {
						string property_type;
						string property_name;
						file >> property_type >> property_name;
						cout << "Property: " << property_type << property_name << endl;
					}
					else
					{
						for (auto i = buffer.size(); i > 0; i--) file.putback(buffer[i - 1]);
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
		else
		{

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