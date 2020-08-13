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
	NodeCoordinate(unsigned int X, unsigned int Y, unsigned int Z, unsigned char depth) : __X(X), __Y(Y), __Z(Z), __depth(depth)
	{
	}
	~NodeCoordinate() = default;
    [[nodiscard]] unsigned int X() const noexcept
    {
        return __X;
    }
    virtual NodeCoordinate& X(unsigned int const X) noexcept {
        __X = X;
        return *this;
    }
    [[nodiscard]] unsigned int Y() const noexcept
    {
        return __Y;
    }
    virtual NodeCoordinate& Y(unsigned int const Y) noexcept {
        __Y = Y;
        return *this;
    }
    [[nodiscard]] unsigned int Z() const noexcept
    {
        return __Z;
    }
    virtual NodeCoordinate& Z(unsigned int const Z) noexcept {
        __Z = Z;
        return *this;
    }
    [[nodiscard]] unsigned char depth() const noexcept
    {
        return __depth;
    }
    virtual NodeCoordinate& depth(unsigned char const depth) noexcept {
        __depth = depth;
        return *this;
    }

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
		 * @param i The node to be calculated.
		 * @return hash value.
		 */
		size_t operator()(NodeCoordinate const& i) const
		{
            return static_cast<size_t>(i.__depth) << 57 ^
                   static_cast<size_t>(i.__X & 0x7FFFF) << 38 ^
                   static_cast<size_t>(i.__Y & 0x7FFFF) << 19 ^
                   static_cast<size_t>(i.__Z & 0x7FFFF);
		}
	};

	struct Equal
	{
		bool operator()(NodeCoordinate const& left, NodeCoordinate const& right) const
		{
            return left == right;
		}
	};

protected:
    unsigned int __X = 0;
    unsigned int __Y = 0;
    unsigned int __Z = 0;
    unsigned char __depth = 1;
};
#endif