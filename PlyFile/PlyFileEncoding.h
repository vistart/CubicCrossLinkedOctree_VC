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

#include "PlyPropertyType.h"
#include <string>
#include <fstream>
using namespace std;

/*
 This class is used to describe the file encoding of ply file.
 */
class PlyFileEncoding
{
public:
	/*
	 Check and set endian of current situation.
	 Set the default encoding type as ASCII, and it's version is 1.0.
	 */
	PlyFileEncoding();
	~PlyFileEncoding() = default;
	enum FileEncodingType { FILE_ENCODING_ASCII, FILE_ENCODING_BINARY_BIG_ENDIAN, FILE_ENCODING_BINARY_LITTLE_ENDIAN };
	struct FileEncoding
	{
		int type = FILE_ENCODING_ASCII;
		float version = 1.0;
	};

	/*
	 Set the file encoding from the file stream.

	 @param fstream&:
	 @return PlyFileEncoding&:
	 */
	PlyFileEncoding& operator<<(fstream&);

	/*
	 Set the file encoding according to the giving FileEncoding value.

	 @param FileEncoding const&:
	 @return PlyFileEncoding&: self.
	 */
	PlyFileEncoding& operator<<(FileEncoding const&);

	/*
	 Regard the string value as the encoding type.

	 @param string const&: encoding type.
	 @return PlyFileEncoding&: self.
	 */
	PlyFileEncoding& operator<<(string const&);

	/*
	 Regard the float value as the version of the encoding type.

	 @param float const&: encoding version.
	 @return PlyFileEncoding&: self.
	 */
	PlyFileEncoding& operator<<(float const&);
	FileEncoding GetDefinition() const&;

	/*
	 Get the encoding title.
	 
	 @return string: "ascii", "binary_big_endian" or " binary_little_endian".
	 */
	string Encoding() const;

	/*
	 Set the encoding type.

	 @param string const&: encoding type.
	 @return PlyFileEncoding&: self.
	 */
	PlyFileEncoding& Encoding(string const&);
	
	/*
	 Get the version.

	 @return float: version.
	 */
	float Version() const;

	/*
	 Set the version of file encoding.

	 @param float const&: version.
	 @return PlyFileEncoding&: self.
	 */
	PlyFileEncoding& Version(float const&);

	/*
	 Check whether the current file encoding is equal to the specified one.
	 
	 @param PlyFileEncoding const&: object to compare.
	 @return bool: true if equal.
	 */
	bool operator==(PlyFileEncoding const&) const;

	/*
	 Check whether the current file encoding is not equal to the specified one.

	 @param PlyFileEncoding const&: object to compare.
	 @return bool: true if not equal.
	 */
	bool operator!=(PlyFileEncoding const&) const;

	/*
	 Check whether the current file encoding is equal to the specified one.

	 @param FileEncoding const&: object to compare.
	 @return bool: true if equal.
	 */
	bool operator==(FileEncoding const&) const;

	/*
	 Check whether the current file encoding is not equal to the specified one.

	 @param FileEncoding const&: object to compare.
	 @return bool: true if not equal.
	 */
	bool operator!=(FileEncoding const&) const;

	/*
	 The attribute containing the endian of current situation.
	 The default value is related to the current architecture and is determined 
	 at compile time. This value should be specified during instantiation, and 
	 it is strongly not recommended to modify it thereafter.
	 */
	PlyPropertyType::Endian endian;
protected:
	FileEncoding file_encoding;
};

#endif