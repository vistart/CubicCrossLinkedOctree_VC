/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#pragma once

#ifndef __PLY_EDGE_H__
#define __PLY_EDGE_H__

#include "PointEdge.h"

/*
 @TODO: Implement it.
 */
class PlyEdge : public PointEdge
{
public:
	enum PropertyNames {
		PROPERTY_NONE,
		PROPERTY_VERTEX1,
		PROPERTY_VERTEX2,
		PROPERTY_RED,
		PROPERTY_GREEN,
		PROPERTY_BLUE
	};
	struct EdgeName {
		int name;
		int type;
	};
};

#endif