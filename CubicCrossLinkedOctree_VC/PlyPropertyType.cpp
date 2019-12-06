#ifndef __PLY_PROPERTY_TYPE_H__
#include "PlyPropertyType.h"
#endif

#ifdef __PLY_PROPERTY_TYPE_H__
const int PlyPropertyType::PropertyDataTypeSize[9] = { 0, 1, 1, 2, 2, 4, 4, 4, 8 };
PlyPropertyType::Endian PlyPropertyType::check_endian()
{
    int i = 1;
    char* p = (char*)&i;
    return (p[0] == 1 ? Endian::LITTLE : Endian::BIG);
}

#endif
