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
#ifndef __SINGLETON_BASE__
#define __SINGLETON_BASE__
template <class T>
class SingletonBase
{
protected:
	SingletonBase() {}
public:
	SingletonBase(SingletonBase const&) = delete;
	SingletonBase& operator=(SingletonBase const&) = delete;
	static T& instance()
	{
		static T single;
		return single;
	}
};
#endif
