/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_COMMENT_LIST_H__
#include "PlyCommentList.h"
#endif

#ifdef __PLY_COMMENT_LIST_H__
bool PlyCommentList::add(string comment)
{
	this->comments.push_back(comment);
	return true;
}

vector<string> PlyCommentList::getComments()
{
	return this->comments;
}

PlyCommentList& PlyCommentList::operator<<(string comment)
{
	if (this->add(comment)) {
		
	}
	return *this;
}

PlyCommentList::~PlyCommentList()
{
	this->comments.erase(this->comments.begin(), this->comments.end());
}
#endif
