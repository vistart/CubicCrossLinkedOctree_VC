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

#ifndef __PLY_FILE_ENCODING_H__
#define __PLY_FILE_ENCODING_H__

#define PLY_TAG_FILE_ENCODING "format"
#define PLY_FILE_ENCODING_ASCII "ascii"
#define PLY_FILE_BINARY_BIG_ENDIAN "binary_big_endian"
#define PLY_FILE_BINARY_LITTLE_ENDIAN "binary_little_endian"

#include <string>
#include <fstream>
using namespace std;
class PlyFileEncoding
{
public:
	PlyFileEncoding();
	~PlyFileEncoding() = default;
	enum FileEncodingType { FILE_ENCODING_ASCII, FILE_ENCODING_BINARY_BIG_ENDIAN, FILE_ENCODING_BINARY_LITTLE_ENDIAN };
	struct FileEncoding
	{
		int type = FILE_ENCODING_ASCII;
		float version = 1.0;
	};
	PlyFileEncoding& operator<<(fstream&);
	PlyFileEncoding& operator<<(FileEncoding const&);
	PlyFileEncoding& operator<<(string const&);
	PlyFileEncoding& operator<<(float const&);
	FileEncoding GetDefinition() const&;
	string Encoding() const;
	PlyFileEncoding& Encoding(string const&);
	float Version() const;
	PlyFileEncoding& Version(float const&);
	bool operator==(PlyFileEncoding const&) const;
	bool operator!=(PlyFileEncoding const&) const;
	bool operator==(FileEncoding const&) const;
	bool operator!=(FileEncoding const&) const;
protected:
	FileEncoding file_encoding;
};

#endif