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
	auto& instance = this->get();
	if (instance.add(comment)) {
		
	}
	return instance;
}

PlyCommentList::PlyCommentList()
{

}

PlyCommentList::~PlyCommentList()
{
	auto& instance = this->get();
	instance.getComments().clear();
}
#endif
