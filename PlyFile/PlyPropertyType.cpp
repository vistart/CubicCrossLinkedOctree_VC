/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_PROPERTY_TYPE_H__
#include "PlyPropertyType.h"
#endif

#ifdef __PLY_PROPERTY_TYPE_H__
const int PlyPropertyType::PropertyDataTypeSize[9] = { 0, 1, 1, 2, 2, 4, 4, 4, 8 };
PlyPropertyType::Endian PlyPropertyType::check_endian()
{
#ifdef IS_LITTLE_ENDIAN
	return Endian::LITTLE;
#else
	return Endian::BIG;
#endif
}

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::NOTYPE> {
	using type = double;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::INT8> {
	using type = char;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::UINT8> {
	using type = unsigned char;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::INT16> {
	using type = short;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::UINT16> {
	using type = unsigned short;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::INT32> {
	using type = int;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::UINT32> {
	using type = unsigned int;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::FLOAT32> {
	using type = float;
};

template <>
struct PlyPropertyType::TypeSelector<PlyPropertyType::FLOAT64> {
	using type = double;
};
#endif
