#pragma once
#ifndef __PLY_PROPERTY_TYPE_H__
#define __PLY_PROPERTY_TYPE_H__
#endif

#include <climits>
#include <fstream>
#include <type_traits>

#define IS_LITTLE_ENDIAN (1 == *(unsigned char *)&(const int){1})

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
	static typename enable_if<is_arithmetic<T>::value, T>::type read_binary_le_property(fstream& file)
	{
		T p = 0;
		file.read(reinterpret_cast<char*>(&p), sizeof(T));
#ifdef IS_LITTLE_ENDIAN
		return p;
#else
		return swap_endian<T>(p);
#endif
	}

	template<typename T>
	static typename enable_if<is_arithmetic<T>::value, T>::type read_binary_be_property(fstream& file)
	{
		T p = 0;
		file.read(reinterpret_cast<char*>(&p), sizeof(T));
#ifdef IS_LITTLE_ENDIAN
		return swap_endian<T>(p);
#else
		return p;
#endif
	}

	static Endian check_endian();

	template <int N>
	struct TypeSelector {
		using type = double;
	};
};
