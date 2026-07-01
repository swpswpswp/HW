#pragma once
#include "CP_Student.h"

class CP_ChainDoubleLink {
public:
	CP_Student m_data;
	CP_ChainDoubleLink* m_previous, * m_next;
public:
	CP_ChainDoubleLink():m_previous(nullptr),m_next(nullptr){}
	~CP_ChainDoubleLink();

	CP_ChainDoubleLink* mb_createNode();
	void mb_deleteNode(CP_ChainDoubleLink* p);
	CP_ChainDoubleLink* mb_findNodeById(int id);
	CP_ChainDoubleLink* mb_findNodeByScore(int score);
	void mb_sortById();
};