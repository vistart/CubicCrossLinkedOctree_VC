#pragma once

#ifndef __PLY_COMMENT_LIST__
#define __PLY_COMMENT_LIST__

#define PLY_TAG_COMMENT "comment"

#include <vector>
#include <string>
using namespace std;
class PlyCommentList
{
public:
	static PlyCommentList& get();
	bool add(string);
	vector<string> getComments();
	PlyCommentList& operator<<(string);
protected:
	vector<string> comments;
	PlyCommentList();
	PlyCommentList(PlyCommentList const&) = delete;
	PlyCommentList(PlyCommentList&&) = delete;
	PlyCommentList& operator=(PlyCommentList const&) = delete;
	PlyCommentList& operator=(PlyCommentList&&) = delete;
	~PlyCommentList();
};
#endif