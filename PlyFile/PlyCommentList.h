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
    /**
     No action is required by default.
     */
	PlyCommentList() = default;

    /**
     All comments need to be cleared first.
     */
	~PlyCommentList();

    /**
     Add comment.
    
     @param string: the comment to be added.
     @return bool: True if comment added.
     */
	bool add(string);

    /**
     Get all the comments.
    
     @return vector<string>: the stored comments.
     */
	vector<string> getComments();

    /**
     Add comment.
    
     @param string: the comment to be added.
     @return PlyCommentList&: itself.
     */
	PlyCommentList& operator<<(string);
protected:
    /**
     * The stored comments.
     */
	vector<string> comments;
};
#endif