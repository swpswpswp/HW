#include <iostream>
using namespace std;
#include "CP_StudentProduct.h"

CP_StudentProduct::CP_StudentProduct(CP_NodeFactory& factory)
	: m_factory(factory), m_head(nullptr) {
	m_head = new CP_StudentNode;
}

CP_StudentProduct::~CP_StudentProduct() {
	mb_destroyAll();
	delete m_head;
	m_head = nullptr;
}

void CP_StudentProduct::mb_printAllStudent() {
	if (m_head == nullptr || m_head->m_previous == nullptr) {
		cout << "目前还没有学生。" << endl;
		return;
	}
	CP_StudentNode* p = m_head->m_next;
	int n = 1;
	do {
		cout << "[" << n << "]:ID(" << p->m_data.m_ID << "),Score(" << p->m_data.m_score << ")" << endl;
		p = p->m_next;
		n++;
	} while (p != m_head);
}

CP_StudentNode* CP_StudentProduct::mb_createNode() {
	if (m_head->m_previous == nullptr) {
		CP_StudentNode* p = m_factory.mb_obtainNode();
		if (p == nullptr) {
			return nullptr;
		}
		m_head->m_previous = p;
		m_head->m_next = p;
		p->m_previous = m_head;
		p->m_next = m_head;
		return p;
	}
	CP_StudentNode* pNew = m_factory.mb_obtainNode();
	if (pNew == nullptr) {
		return nullptr;
	}
	CP_StudentNode* p = m_head->m_previous;
	m_head->m_previous = pNew;
	m_head->m_previous->m_next = m_head;
	p->m_next = m_head->m_previous;
	m_head->m_previous->m_previous = p;
	return pNew;
}

void CP_StudentProduct::mb_deleteNode(CP_StudentNode* p) {
	if (m_head->m_previous == nullptr) {
		return;
	}
	if (p == m_head) {
		if (p->m_previous == m_head) {
			p->m_previous = nullptr;
			return;
		}
		m_head->m_data = p->m_next->m_data;
		p = p->m_next;
	}
	CP_StudentNode* q;
	for (q = m_head->m_next; (q != p) && (q != m_head);) {
		if (q != nullptr) {
			q = q->m_next;
		}
		else {
			break;
		}
	}
	if (q == m_head) {
		return;
	}
	if (q != p) {
		return;
	}
	q = p->m_previous;
	q->m_next = p->m_next;
	q = p->m_next;
	q->m_previous = p->m_previous;
	if (p->m_next == m_head && p->m_previous == m_head) {
		m_head->m_previous = nullptr;
		m_head->m_next = nullptr;
	}
	else if (p->m_next == m_head) {
		m_head->m_previous = p->m_previous;
	}
	else if (p->m_previous == m_head) {
		m_head->m_next = p->m_next;
	}
	p->m_previous = nullptr;
	p->m_next = nullptr;
	m_factory.mb_recycleNode(p);
}

CP_StudentNode* CP_StudentProduct::mb_findNodeById(int id) {
	if (m_head->m_previous == nullptr) {
		return nullptr;
	}
	CP_StudentNode* p = m_head->m_next;
	do {
		if (p->m_data.m_ID == id) {
			return p;
		}
		p = p->m_next;
	} while (p != m_head);
	return nullptr;
}

CP_StudentNode* CP_StudentProduct::mb_findNodeByScore(int score) {
	if (m_head->m_previous == nullptr) {
		return nullptr;
	}
	CP_StudentNode* p = m_head->m_next;
	do {
		if (p->m_data.m_score == score) {
			return p;
		}
		p = p->m_next;
	} while (p != m_head);
	return nullptr;
}

void CP_StudentProduct::mb_sortById() {
	if (m_head->m_previous == nullptr || m_head->m_next == m_head->m_previous) {
		return;
	}
	bool swapped;
	do {
		swapped = false;
		CP_StudentNode* q = m_head->m_next;
		while (q->m_next != m_head) {
			CP_StudentNode* q1 = q->m_next;
			if (q->m_data.m_ID > q1->m_data.m_ID) {
				gb_swapStudent(q->m_data, q1->m_data);
				swapped = true;
			}
			q = q1;
		}
	} while (swapped);
}

void CP_StudentProduct::mb_addStudent(const CP_Student& s) {
	CP_StudentNode* p = mb_createNode();
	if (p != nullptr) {
		p->m_data = s;
		mb_sortById();
	}
	else {
		cout << "内存申请失败！" << endl;
	}
}

bool CP_StudentProduct::mb_deleteById(int id) {
	CP_StudentNode* p = mb_findNodeById(id);
	if (p != nullptr) {
		mb_deleteNode(p);
		return true;
	}
	cout << "没有找到该学号的学生。" << endl;
	return false;
}

void CP_StudentProduct::mb_deleteByScore(int score) {
	bool removed = false;
	CP_StudentNode* p;
	do {
		p = mb_findNodeByScore(score);
		if (p != nullptr) {
			mb_deleteNode(p);
			removed = true;
		}
		else {
			break;
		}
	} while (1);
	if (!removed) {
		cout << "已经不存在该成绩的学生。" << endl;
	}
}

bool CP_StudentProduct::mb_queryScoreById(int id, int& score) {
	CP_StudentNode* p = mb_findNodeById(id);
	if (p != nullptr) {
		score = p->m_data.m_score;
		return true;
	}
	cout << "没有找到该学号的学生。" << endl;
	return false;
}

void CP_StudentProduct::mb_queryIdsByScore(int score) {
	if (m_head->m_previous == nullptr) {
		cout << "已经不存在该成绩的学生。" << endl;
		return;
	}
	bool found = false;
	CP_StudentNode* p = m_head->m_next;
	do {
		if (p->m_data.m_score == score) {
			cout << p->m_data.m_ID << endl;
			found = true;
		}
		p = p->m_next;
	} while (p != m_head);
	if (!found) {
		cout << "已经不存在该成绩的学生。" << endl;
	}
}

void CP_StudentProduct::mb_destroyAll() {
	while (m_head != nullptr && m_head->m_previous != nullptr) {
		CP_StudentNode* p = m_head->m_next;
		if (p == m_head) {
			mb_deleteNode(m_head);
			break;
		}
		mb_deleteNode(p);
	}
}
