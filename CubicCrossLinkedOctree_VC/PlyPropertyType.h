#pragma once
#ifndef __PLY_PROPERTY_TYPE_H__
#define __PLY_PROPERTY_TYPE_H__
#endif

#include <climits>
#include <fstream>
#include <type_traits>
using namespace std;
class PlyPropertyType
{
public:
	enum PropertyDataType { NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64 };
	enum class Endian { LITTLE = 0, BIG = 1 };
	static const int PropertyDataTypeSize[9];
	template <typename T>
	static T swap_endian(T& s)
	{
		static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

		union
		{
			T u;
			unsigned char u8[sizeof(T)];
		} source, dest;

		source.u = s;

		for (size_t k = 0; k < sizeof(T); k++)
			dest.u8[k] = source.u8[sizeof(T) - k - 1];

		return dest.u;
	}

	template<typename T>
	static T read_vertex_binary_le_property(fstream& file)
	{
		T p = 0;
		file.read(reinterpret_cast<char*>(&p), sizeof(T));
		return p;
	}

	template<typename T>
	static T read_vertex_binary_be_property(fstream& file)
	{
		T p = 0;
		file.read(reinterpret_cast<char*>(&p), sizeof(T));
		return swap_endian<T>(p);
	}
	static Endian check_endian();
};
