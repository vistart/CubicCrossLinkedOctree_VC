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
#ifndef __NODE_COORDINATE_H__
#define __NODE_COORDINATE_H__

#include <unordered_map>

using namespace std;

class NodeCoordinate
{
public:
    NodeCoordinate() = default;
	NodeCoordinate(unsigned int X, unsigned int Y, unsigned int Z, unsigned char depth) : X(X), Y(Y), Z(Z), depth(depth)
	{
	}
	~NodeCoordinate() = default;

	/**
	 * Determine whether the two coordinates are equal.
	 * Return true if XYZ and the depth must be completely equal.
	 *
	 * @param node_coordinate The coordinate to be compared.
	 * @return true if XYZ and the depth completely equal.
	 */
    virtual bool operator==(NodeCoordinate const& node_coordinate) const;

	struct Hash
	{
		/**
		 * Calculate the hash value based on the coordinates and depth.
		 * 
		 * Because the depth range is limited to 1~127, only 7 bits of binary are needed. 
		 * The remaining 57 bits are divided equally into three dimensions, each of which occupies 19 bits, 
         * that is, the value of each dimension ranges from 0 to 524287.
         * If the coordinate value exceeds this range, only the last 19 bits will be accepted,
         * and the high bits will be discarded.
         *
         * For example:
         * The NodeCoordinate instance is (X:16, Y:15, Z:14, depth:5)
         *
         * The calculated hash value is 0x0A0004000078000E.
         * The corresponding binary is:
         * 0000 1010 0000 0000
         * 0000 0100 0000 0000
         * 0000 0000 0111 1000
         * 0000 0000 0000 1110
		 * 
		 * @param i The node to be calculated.
		 * @return hash value.
		 */
		size_t operator()(NodeCoordinate const& i) const
		{
            return static_cast<size_t>(i.depth) << 57 ^
                   static_cast<size_t>(i.X & 0x7FFFF) << 38 ^
                   static_cast<size_t>(i.Y & 0x7FFFF) << 19 ^
                   static_cast<size_t>(i.Z & 0x7FFFF);
		}
	};
    /*
	struct Equal
	{
		bool operator()(NodeCoordinate const& left, NodeCoordinate const& right) const
		{
            return left == right;
		}
	};
	*/

	/**
	 * Node coordinate X.
	 */
    unsigned int X = 0;
	/**
	 * Node coordinate Y.
	 */
    unsigned int Y = 0;
	/**
	 * Node coordinate Z.
	 */
    unsigned int Z = 0;
	/**
	 * Node coordinate depth.
	 */
    unsigned char depth = 1;
};
#endif