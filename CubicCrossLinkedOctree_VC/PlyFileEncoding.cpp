#ifndef __PLY_FILE_ENCODING__
#include "PlyFileEncoding.h"
#endif

#ifdef __PLY_FILE_ENCODING__
PlyFileEncoding& PlyFileEncoding::get()
{
	static PlyFileEncoding instance;
	return instance;
}

PlyFileEncoding& PlyFileEncoding::operator<<(PlyFileEncoding::FileEncoding file_encoding)
{
	auto& instance = this->get();
	instance.file_encoding = file_encoding;
	return instance;
}

PlyFileEncoding& PlyFileEncoding::operator<<(string format)
{
	auto& instance = this->get();
	if (format == string(PLY_FILE_ENCODING_ASCII))
	{
		instance.file_encoding.type = FILE_ENCODING_ASCII;
	}
	return instance;
}

PlyFileEncoding& PlyFileEncoding::operator<<(float version)
{
	auto& instance = this->get();
	instance.file_encoding.version = version;
	return instance;
}

PlyFileEncoding::PlyFileEncoding()
{
	this->file_encoding = { FILE_ENCODING_ASCII, 1.0 };
}

PlyFileEncoding::~PlyFileEncoding()
{

}
#endif