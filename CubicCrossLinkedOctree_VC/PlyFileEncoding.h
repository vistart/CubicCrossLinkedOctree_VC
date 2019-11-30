#pragma once

#ifndef __PLY_FILE_ENCODING__
#define __PLY_FILE_ENCODING__

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
protected:
	FileEncoding file_encoding;
	PlyFileEncoding();
	PlyFileEncoding(PlyFileEncoding const&) = delete;
	PlyFileEncoding(PlyFileEncoding&&) = delete;
	PlyFileEncoding& operator=(PlyFileEncoding const&) = delete;
	PlyFileEncoding& operator=(PlyFileEncoding&&) = delete;
	bool operator==(PlyFileEncoding const&);
	bool operator!=(PlyFileEncoding const&);
	bool operator==(FileEncoding const&);
	bool operator!=(FileEncoding const&);
	~PlyFileEncoding();
};

#endif