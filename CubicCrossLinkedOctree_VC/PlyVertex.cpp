/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX_H__
#include "PlyVertex.h"
#endif

#ifdef __PLY_VERTEX_H__

#define read_be PlyPropertyType::read_binary_be_property
#define read_le PlyPropertyType::read_binary_le_property

PlyVertex::PlyVertex(vector<VertexName> const& names, string const& vertex)
{
	double X = 0, Y = 0, Z = 0;
	unsigned char R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0, CONFIDENCE = 1, INTENSITY = 0.5;
	unsigned char ALPHA = 255;
	stringstream stream(vertex);
	for (auto& name : names)
	{
		switch (name.name) {
		case PROPERTY_X:
			stream >> X;
			break;
		case PROPERTY_Y:
			stream >> Y;
			break;
		case PROPERTY_Z:
			stream >> Z;
			break;
		case PROPERTY_R:
			stream >> R;
			break;
		case PROPERTY_G:
			stream >> G;
			break;
		case PROPERTY_B:
			stream >> B;
			break;
		case PROPERTY_NX:
			stream >> NX;
			break;
		case PROPERTY_NY:
			stream >> NY;
			break;
		case PROPERTY_NZ:
			stream >> NZ;
			break;
		case PROPERTY_ALPHA:
			stream >> ALPHA;
			break;
		case PROPERTY_CONFIDENCE:
			stream >> CONFIDENCE;
			break;
		case PROPERTY_INTENSITY:
			stream >> INTENSITY;
			break;
		default:
			string none;
			stream >> none;
		}
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA, CONFIDENCE, INTENSITY);
}

PlyVertex::PlyVertex(vector<VertexName> const& names, fstream& file, PlyFileEncoding::FileEncoding const& file_encoding)
{
	double X = 0, Y = 0, Z = 0;
	unsigned char R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0, CONFIDENCE = 1, INTENSITY = 0.5;
	unsigned char ALPHA = 255;
	switch (file_encoding.type) {
	case PlyFileEncoding::FILE_ENCODING_ASCII:
		for (auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				file >> X;
				break;
			case PROPERTY_Y:
				file >> Y;
				break;
			case PROPERTY_Z:
				file >> Z;
				break;
			case PROPERTY_R:
				file >> R;
				break;
			case PROPERTY_G:
				file >> G;
				break;
			case PROPERTY_B:
				file >> B;
				break;
			case PROPERTY_NX:
				file >> NX;
				break;
			case PROPERTY_NY:
				file >> NY;
				break;
			case PROPERTY_NZ:
				file >> NZ;
				break;
			case PROPERTY_ALPHA:
				file >> ALPHA;
				break;
			case PROPERTY_CONFIDENCE:
				file >> CONFIDENCE;
				break;
			case PROPERTY_INTENSITY:
				file >> INTENSITY;
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_BIG_ENDIAN:
		for (auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				switch (name.type) {
				case PlyPropertyType::INT8: X = read_be<char>(file); break;
				case PlyPropertyType::UINT8: X = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: X = read_be<short>(file); break;
				case PlyPropertyType::UINT16: X = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: X = read_be<int>(file); break;
				case PlyPropertyType::UINT32: X = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: X = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: X = read_be<double>(file); break;
				}
				break;
			case PROPERTY_Y:
				switch (name.type) {
				case PlyPropertyType::INT8: Y = read_be<char>(file); break;
				case PlyPropertyType::UINT8: Y = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: Y = read_be<short>(file); break;
				case PlyPropertyType::UINT16: Y = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: Y = read_be<int>(file); break;
				case PlyPropertyType::UINT32: Y = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Y = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: Y = read_be<double>(file); break;
				}
				break;
			case PROPERTY_Z:
				switch (name.type) {
				case PlyPropertyType::INT8: Z = read_be<char>(file); break;
				case PlyPropertyType::UINT8: Z = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: Z = read_be<short>(file); break;
				case PlyPropertyType::UINT16: Z = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: Z = read_be<int>(file); break;
				case PlyPropertyType::UINT32: Z = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Z = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: Z = read_be<double>(file); break;
				}
				break;
			case PROPERTY_R:
				R = read_be<unsigned char>(file);
				break;
			case PROPERTY_G:
				G = read_be<unsigned char>(file);
				break;
			case PROPERTY_B:
				B = read_be<unsigned char>(file);
				break;
			case PROPERTY_NX:
				switch (name.type) {
				case PlyPropertyType::INT8: NX = read_be<char>(file); break;
				case PlyPropertyType::UINT8: NX = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: NX = read_be<short>(file); break;
				case PlyPropertyType::UINT16: NX = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: NX = read_be<int>(file); break;
				case PlyPropertyType::UINT32: NX = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NX = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: NX = read_be<double>(file); break;
				}
				break;
			case PROPERTY_NY:
				switch (name.type) {
				case PlyPropertyType::INT8: NY = read_be<char>(file); break;
				case PlyPropertyType::UINT8: NY = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: NY = read_be<short>(file); break;
				case PlyPropertyType::UINT16: NY = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: NY = read_be<int>(file); break;
				case PlyPropertyType::UINT32: NY = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NY = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: NY = read_be<double>(file); break;
				}
				break;
			case PROPERTY_NZ:
				switch (name.type) {
				case PlyPropertyType::INT8: NZ = read_be<char>(file); break;
				case PlyPropertyType::UINT8: NZ = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: NZ = read_be<short>(file); break;
				case PlyPropertyType::UINT16: NZ = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: NZ = read_be<int>(file); break;
				case PlyPropertyType::UINT32: NZ = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NZ = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: NZ = read_be<double>(file); break;
				}
				break;
			case PROPERTY_ALPHA:
				ALPHA = read_be<unsigned char>(file);
				break;
			case PROPERTY_CONFIDENCE:
				switch (name.type) {
				case PlyPropertyType::INT8: CONFIDENCE = read_be<char>(file); break;
				case PlyPropertyType::UINT8: CONFIDENCE = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: CONFIDENCE = read_be<short>(file); break;
				case PlyPropertyType::UINT16: CONFIDENCE = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: CONFIDENCE = read_be<int>(file); break;
				case PlyPropertyType::UINT32: CONFIDENCE = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: CONFIDENCE = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: CONFIDENCE = read_be<double>(file); break;
				}
				break;
			case PROPERTY_INTENSITY:
				switch (name.type) {
				case PlyPropertyType::INT8: INTENSITY = read_be<char>(file); break;
				case PlyPropertyType::UINT8: INTENSITY = read_be<unsigned char>(file); break;
				case PlyPropertyType::INT16: INTENSITY = read_be<short>(file); break;
				case PlyPropertyType::UINT16: INTENSITY = read_be<unsigned short>(file); break;
				case PlyPropertyType::INT32: INTENSITY = read_be<int>(file); break;
				case PlyPropertyType::UINT32: INTENSITY = read_be<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: INTENSITY = read_be<float>(file); break;
				case PlyPropertyType::FLOAT64: INTENSITY = read_be<double>(file); break;
				}
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_LITTLE_ENDIAN:
		for (auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				switch (name.type) {
				case PlyPropertyType::INT8: X = read_le<char>(file); break;
				case PlyPropertyType::UINT8: X = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: X = read_le<short>(file); break;
				case PlyPropertyType::UINT16: X = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: X = read_le<int>(file); break;
				case PlyPropertyType::UINT32: X = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: X = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: X = read_le<double>(file); break;
				}
				break;
			case PROPERTY_Y:
				switch (name.type) {
				case PlyPropertyType::INT8: Y = read_le<char>(file); break;
				case PlyPropertyType::UINT8: Y = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: Y = read_le<short>(file); break;
				case PlyPropertyType::UINT16: Y = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: Y = read_le<int>(file); break;
				case PlyPropertyType::UINT32: Y = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Y = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: Y = read_le<double>(file); break;
				}
				break;
			case PROPERTY_Z:
				switch (name.type) {
				case PlyPropertyType::INT8: Z = read_le<char>(file); break;
				case PlyPropertyType::UINT8: Z = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: Z = read_le<short>(file); break;
				case PlyPropertyType::UINT16: Z = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: Z = read_le<int>(file); break;
				case PlyPropertyType::UINT32: Z = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Z = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: Z = read_le<double>(file); break;
				}
				break;
			case PROPERTY_R:
				R = read_le<unsigned char>(file);
				break;
			case PROPERTY_G:
				G = read_le<unsigned char>(file);
				break;
			case PROPERTY_B:
				B = read_le<unsigned char>(file);
				break;
			case PROPERTY_NX:
				switch (name.type) {
				case PlyPropertyType::INT8: NX = read_le<char>(file); break;
				case PlyPropertyType::UINT8: NX = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: NX = read_le<short>(file); break;
				case PlyPropertyType::UINT16: NX = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: NX = read_le<int>(file); break;
				case PlyPropertyType::UINT32: NX = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NX = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: NX = read_le<double>(file); break;
				}
				break;
			case PROPERTY_NY:
				switch (name.type) {
				case PlyPropertyType::INT8: NY = read_le<char>(file); break;
				case PlyPropertyType::UINT8: NY = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: NY = read_le<short>(file); break;
				case PlyPropertyType::UINT16: NY = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: NY = read_le<int>(file); break;
				case PlyPropertyType::UINT32: NY = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NY = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: NY = read_le<double>(file); break;
				}
				break;
			case PROPERTY_NZ:
				switch (name.type) {
				case PlyPropertyType::INT8: NZ = read_le<char>(file); break;
				case PlyPropertyType::UINT8: NZ = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: NZ = read_le<short>(file); break;
				case PlyPropertyType::UINT16: NZ = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: NZ = read_le<int>(file); break;
				case PlyPropertyType::UINT32: NZ = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NZ = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: NZ = read_le<double>(file); break;
				}
				break;
			case PROPERTY_ALPHA:
				ALPHA = read_le<unsigned char>(file);
				break;
			case PROPERTY_CONFIDENCE:
				switch (name.type) {
				case PlyPropertyType::INT8: CONFIDENCE = read_le<char>(file); break;
				case PlyPropertyType::UINT8: CONFIDENCE = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: CONFIDENCE = read_le<short>(file); break;
				case PlyPropertyType::UINT16: CONFIDENCE = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: CONFIDENCE = read_le<int>(file); break;
				case PlyPropertyType::UINT32: CONFIDENCE = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: CONFIDENCE = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: CONFIDENCE = read_le<double>(file); break;
				}
				break;
			case PROPERTY_INTENSITY:
				switch (name.type) {
				case PlyPropertyType::INT8: INTENSITY = read_le<char>(file); break;
				case PlyPropertyType::UINT8: INTENSITY = read_le<unsigned char>(file); break;
				case PlyPropertyType::INT16: INTENSITY = read_le<short>(file); break;
				case PlyPropertyType::UINT16: INTENSITY = read_le<unsigned short>(file); break;
				case PlyPropertyType::INT32: INTENSITY = read_le<int>(file); break;
				case PlyPropertyType::UINT32: INTENSITY = read_le<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: INTENSITY = read_le<float>(file); break;
				case PlyPropertyType::FLOAT64: INTENSITY = read_le<double>(file); break;
				}
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA, CONFIDENCE, INTENSITY);
}


PlyVertex::PlyVertex(double const X, double const Y, double const Z, unsigned char const R = 0, unsigned char const G = 0, unsigned char const B = 0)
{
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255, 1, 0.5);
}

void PlyVertex::set_all_properties(double const X, double const Y, double const Z,
	                               unsigned char const R, unsigned char const G, unsigned char const B,
	                               double const NX, double const NY, double const NZ,
	                               unsigned char const ALPHA, double const CONFIDENCE, double const INTENSITY)
{
	this->__X = X;
	this->__Y = Y;
	this->__Z = Z;
	this->__R = R;
	this->__G = G;
	this->__B = B;
	this->__NX = NX;
	this->__NY = NY;
	this->__NZ = NZ;
	this->__ALPHA = ALPHA;
	this->__CONFIDENCE = CONFIDENCE;
	this->__INTENSITY = INTENSITY;
}

double PlyVertex::X() const
{
	return __X;
}
PlyVertex& PlyVertex::X(double const X)
{
	__X = X;
	return *this;
}
double PlyVertex::Y() const
{
	return __Y;
}
PlyVertex& PlyVertex::Y(double const Y)
{
	__Y = Y;
	return *this;
}
double PlyVertex::Z() const
{
	return __Z;
}
PlyVertex& PlyVertex::Z(double const Z)
{
	__Z = Z;
	return *this;
}
unsigned char PlyVertex::R() const
{
	return __R;
}
PlyVertex& PlyVertex::R(unsigned char const R)
{
	__R = R;
	return *this;
}
unsigned char PlyVertex::G() const
{
	return __G;
}
PlyVertex& PlyVertex::G(unsigned char const G)
{
	__G = G;
	return *this;
}
unsigned char PlyVertex::B() const
{
	return __B;
}
PlyVertex& PlyVertex::B(unsigned char const B)
{
	__B = B;
	return *this;
}
double PlyVertex::NX() const
{
	return __NX;
}
PlyVertex& PlyVertex::NX(double const NX)
{
	__NX = NX;
	return *this;
}
double PlyVertex::NY() const
{
	return __NY;
}
PlyVertex& PlyVertex::NY(double const NY)
{
	__NY = NY;
	return *this;
}
double PlyVertex::NZ() const
{
	return __NZ;
}
PlyVertex& PlyVertex::NZ(double const NZ)
{
	__NZ = NZ;
	return *this;
}
unsigned char PlyVertex::ALPHA() const
{
	return __ALPHA;
}
PlyVertex& PlyVertex::ALPHA(unsigned char const ALPHA)
{
	__ALPHA = ALPHA;
	return *this;
}
double PlyVertex::CONFIDENCE() const
{
	return __CONFIDENCE;
}
PlyVertex& PlyVertex::CONFIDENCE(double const CONFIDENCE)
{
	__CONFIDENCE = CONFIDENCE;
	return *this;
}
double PlyVertex::INTENSITY() const
{
	return __INTENSITY;
}
PlyVertex& PlyVertex::INTENSITY(double const INTENSITY)
{
	__INTENSITY = INTENSITY;
	return *this;
}

bool PlyVertex::operator==(PlyVertex const& vertex) const
{
	bool result = (__X == vertex.X() && __Y == vertex.Y() && __Z == vertex.Z());
	if (has_RGB)
	{
		result = (result && __R == vertex.R() && __G == vertex.G() && __B == vertex.B());
	}
	if (has_normal)
	{
		result = (result && __NX == vertex.NX() && __NY == vertex.NY() && __NZ == vertex.NZ());
	}
	if (has_alpha)
	{
		result = (result && __ALPHA == vertex.ALPHA());
	}
	if (has_confidence)
	{
		result = (result && __CONFIDENCE == vertex.CONFIDENCE());
	}
	if (has_intensity)
	{
		result = (result && __INTENSITY == vertex.INTENSITY());
	}
	return result;
}

bool PlyVertex::operator!=(PlyVertex const& vertex) const
{
	return !(*this == vertex);
}

bool PlyVertex::operator<(PlyVertex const& vertex) const
{
	return __X < vertex.X() || __Y < vertex.Y() || __Z < vertex.Z();
}

bool PlyVertex::operator>(PlyVertex const& vertex) const
{
	return __X > vertex.X() || __Y > vertex.Y() || __Z > vertex.Z();
}

void PlyVertex::offset(double const offset_x, double const offset_y, double const offset_z)
{
	__X += offset_x;
	__Y += offset_y;
	__Z += offset_z;
}
#endif