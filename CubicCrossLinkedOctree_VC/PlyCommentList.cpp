#ifndef __PLY_COMMENT_LIST__
#include "PlyCommentList.h"
#endif

#ifdef __PLY_COMMENT_LIST__
PlyCommentList& PlyCommentList::get()
{
	static PlyCommentList list;
	return list;
}

bool PlyCommentList::add(string comment)
{
	this->comments.push_back(comment);
	return true;
}

vector<string> PlyCommentList::getComments()
{
	return this->comments;
}

PlyCommentList::PlyCommentList()
{

}

PlyCommentList::~PlyCommentList()
{

}
#endif
