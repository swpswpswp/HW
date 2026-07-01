#pragma once
#include "CP_NodeFactory.h"

// 产品类：存放在用学生记录的双向循环链表，节点由工厂提供/回收
class CP_StudentProduct {
	CP_NodeFactory& m_factory;
	CP_StudentNode* m_head;
public:
	explicit CP_StudentProduct(CP_NodeFactory& factory);
	~CP_StudentProduct();
	void mb_printAllStudent();
	void mb_addStudent(const CP_Student& s);
	bool mb_deleteById(int id);
	void mb_deleteByScore(int score);
	bool mb_queryScoreById(int id, int& score);
	void mb_queryIdsByScore(int score);
	void mb_destroyAll();

private:
	CP_StudentNode* mb_createNode();
	void mb_deleteNode(CP_StudentNode* p);
	CP_StudentNode* mb_findNodeById(int id);
	CP_StudentNode* mb_findNodeByScore(int score);
	void mb_sortById();
};
