/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FILE_ENCODING_H__
#include "PlyFileEncoding.h"
#endif

#ifdef __PLY_FILE_ENCODING_H__

string PlyFileEncoding::Encoding()
{
	if (this->file_encoding.type == FILE_ENCODING_ASCII)
		return PLY_FILE_ENCODING_ASCII;
	if (this->file_encoding.type == FILE_ENCODING_BINARY_BIG_ENDIAN)
		return PLY_FILE_BINARY_BIG_ENDIAN;
	if (this->file_encoding.type == FILE_ENCODING_BINARY_LITTLE_ENDIAN)
		return PLY_FILE_BINARY_LITTLE_ENDIAN;
	return "";
}

PlyFileEncoding& PlyFileEncoding::Encoding(string encoding)
{
	*this << encoding;
	return *this;
}

float PlyFileEncoding::Version()
{
	return this->file_encoding.version;
}

PlyFileEncoding& PlyFileEncoding::Version(float version)
{
	*this << version;
	return *this;
}

PlyFileEncoding& PlyFileEncoding::operator<<(fstream& file)
{
	string encoding;
	float version;
	file >> encoding >> version;
	*this << encoding << version;
	return *this;
}

PlyFileEncoding& PlyFileEncoding::operator<<(FileEncoding file_encoding)
{
	this->file_encoding = file_encoding;
	return *this;
}

PlyFileEncoding& PlyFileEncoding::operator<<(string format)
{
	if (format == string(PLY_FILE_ENCODING_ASCII))
	{
		this->file_encoding.type = FILE_ENCODING_ASCII;
	}
	return *this;
}

PlyFileEncoding& PlyFileEncoding::operator<<(float version)
{
	this->file_encoding.version = version;
	return *this;
}

bool PlyFileEncoding::operator==(PlyFileEncoding const& object)
{
	return this->file_encoding.type == object.file_encoding.type && this->file_encoding.version == object.file_encoding.version;
}

bool PlyFileEncoding::operator!=(PlyFileEncoding const& object)
{
	return !(*this == object);
}

bool PlyFileEncoding::operator==(PlyFileEncoding::FileEncoding const& object)
{
	return this->file_encoding.type == object.type && this->file_encoding.version == object.version;
}

bool PlyFileEncoding::operator!=(PlyFileEncoding::FileEncoding const& object)
{
	return !(*this == object);
}

PlyFileEncoding::PlyFileEncoding()
{
	this->file_encoding = { FILE_ENCODING_ASCII, 1.0 };
}
#endif