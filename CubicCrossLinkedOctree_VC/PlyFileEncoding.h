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

#include "SingletonBase.h"
#include <string>
#include <fstream>
using namespace std;
class PlyFileEncoding : public SingletonBase<PlyFileEncoding>
{
	PlyFileEncoding();
	~PlyFileEncoding();
	friend class SingletonBase<PlyFileEncoding>;
public:
	enum FileEncodingType { FILE_ENCODING_ASCII, FILE_ENCODING_BINARY_BIG_ENDIAN, FILE_ENCODING_BINARY_LITTLE_ENDIAN };
	struct FileEncoding
	{
		int type = FILE_ENCODING_ASCII;
		float version = 1.0;
	};
	static PlyFileEncoding& get();
	PlyFileEncoding& operator<<(fstream&);
	PlyFileEncoding& operator<<(FileEncoding);
	PlyFileEncoding& operator<<(string);
	PlyFileEncoding& operator<<(float);
	string Encoding();
	PlyFileEncoding& Encoding(string const);
	float Version();
	PlyFileEncoding& Version(float const);
	bool operator==(PlyFileEncoding const&);
	bool operator!=(PlyFileEncoding const&);
	bool operator==(FileEncoding const&);
	bool operator!=(FileEncoding const&);
protected:
	FileEncoding file_encoding;
};

#endif