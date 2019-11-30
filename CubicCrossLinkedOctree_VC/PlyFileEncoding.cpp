#ifndef __PLY_FILE_ENCODING__
#include "PlyFileEncoding.h"
#endif

#ifdef __PLY_FILE_ENCODING__
PlyFileEncoding& PlyFileEncoding::get()
{
	static PlyFileEncoding instance;
	return instance;
}

PlyFileEncoding& PlyFileEncoding::operator<<(fstream& file)
{
	string encoding;
	float version;
	file >> encoding >> version;
	*this << encoding << version;
	return *this;
}

PlyFileEncoding& PlyFileEncoding::operator<<(PlyFileEncoding::FileEncoding file_encoding)
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

PlyFileEncoding::PlyFileEncoding()
{
	this->file_encoding = { FILE_ENCODING_ASCII, 1.0 };
}

PlyFileEncoding::~PlyFileEncoding()
{

}
#endif