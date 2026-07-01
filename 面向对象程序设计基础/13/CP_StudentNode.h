#pragma once
#include "CP_Student.h"

class CP_StudentNode {
public:
	CP_Student m_data;
	CP_StudentNode* m_previous;
	CP_StudentNode* m_next;
public:
	CP_StudentNode() :m_previous(nullptr), m_next(nullptr) {}
};
