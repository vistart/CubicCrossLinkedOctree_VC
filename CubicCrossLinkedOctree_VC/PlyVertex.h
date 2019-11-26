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

#ifndef __PLY_VERTEX__
#define __PLY_VERTEX__

#include <fstream>

using namespace std;

class PlyVertex
{
public:
	double GetX();
	double GetY();
	double GetZ();
	char GetR();
	char GetG();
	char GetB();
	PlyVertex();
	PlyVertex(fstream&);
	PlyVertex(double, double, double);
	PlyVertex(double, double, double, char, char, char);
	~PlyVertex();
protected:
	double X;
	double Y;
	double Z;
	char R;
	char G;
	char B;
};

#endif