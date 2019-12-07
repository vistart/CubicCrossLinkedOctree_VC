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

#ifndef __PLY_COMMENT_LIST_H__
#define __PLY_COMMENT_LIST_H__

#define PLY_TAG_COMMENT "comment"

#include <vector>
#include <string>
using namespace std;
class PlyCommentList
{
public:
	PlyCommentList() = default;
	~PlyCommentList();
	bool add(string);
	vector<string> getComments();
	PlyCommentList& operator<<(string);
protected:
	vector<string> comments;
};
#endif