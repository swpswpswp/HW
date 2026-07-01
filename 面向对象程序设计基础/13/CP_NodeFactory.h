#pragma once
#include "CP_StudentNode.h"

// 工厂类：存放空闲节点的双向循环链表
class CP_NodeFactory {
	CP_StudentNode* m_poolHead;
public:
	CP_NodeFactory();
	~CP_NodeFactory();
	CP_StudentNode* mb_obtainNode();
	void mb_recycleNode(CP_StudentNode* p);
	void mb_destroyAll();
};
