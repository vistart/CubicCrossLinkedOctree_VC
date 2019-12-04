#pragma once
#ifndef __PLY_PROPERTY_TYPE_H__
#define __PLY_PROPERTY_TYPE_H__
#endif

class PlyPropertyType
{
public:
	enum PropertyDataType { NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64 };
	static const int PropertyDataTypeSize[9];
};

