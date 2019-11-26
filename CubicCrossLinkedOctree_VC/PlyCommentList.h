#pragma once

#ifndef __PLY_COMMENT_LIST__
#define __PLY_COMMENT_LIST__

#include <vector>
#include <string>
using namespace std;
class PlyCommentList
{
public:
	PlyCommentList();
	PlyCommentList(string);
	~PlyCommentList();
protected:
	vector<string> comments;
};
#endif