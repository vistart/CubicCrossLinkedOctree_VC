#ifndef __PLY_COMMENT_LIST__
#include "PlyCommentList.h"
#endif

#ifdef __PLY_COMMENT_LIST__
PlyCommentList& PlyCommentList::get()
{
	static PlyCommentList instance;
	return instance;
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

PlyCommentList& PlyCommentList::operator<<(string comment)
{
	if (this->add(comment)) {
		
	}
	return *this;
}

PlyCommentList::PlyCommentList()
{

}

PlyCommentList::~PlyCommentList()
{
	this->comments.erase(this->comments.begin(), this->comments.end());
}
#endif
