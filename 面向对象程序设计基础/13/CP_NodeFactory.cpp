#include <new>
using std::nothrow;
#include "CP_NodeFactory.h"

CP_NodeFactory::CP_NodeFactory() {
	m_poolHead = new CP_StudentNode;
}

CP_NodeFactory::~CP_NodeFactory() {
	mb_destroyAll();
	delete m_poolHead;
	m_poolHead = nullptr;
}

CP_StudentNode* CP_NodeFactory::mb_obtainNode() {
	if (m_poolHead->m_previous == nullptr) {
		return new(nothrow) CP_StudentNode;
	}
	CP_StudentNode* p = m_poolHead->m_next;
	if (p == m_poolHead) {
		m_poolHead->m_previous = nullptr;
		m_poolHead->m_next = nullptr;
		p->m_previous = nullptr;
		p->m_next = nullptr;
		return p;
	}
	CP_StudentNode* q = p->m_previous;
	q->m_next = p->m_next;
	p->m_next->m_previous = q;
	if (m_poolHead->m_next == p) {
		m_poolHead->m_next = p->m_next;
	}
	if (m_poolHead->m_previous == p) {
		m_poolHead->m_previous = q;
	}
	p->m_previous = nullptr;
	p->m_next = nullptr;
	return p;
}

void CP_NodeFactory::mb_recycleNode(CP_StudentNode* p) {
	if (p == nullptr) {
		return;
	}
	p->m_data = CP_Student();
	if (m_poolHead->m_previous == nullptr) {
		m_poolHead->m_previous = p;
		m_poolHead->m_next = p;
		p->m_previous = m_poolHead;
		p->m_next = m_poolHead;
		return;
	}
	CP_StudentNode* tail = m_poolHead->m_previous;
	tail->m_next = p;
	p->m_previous = tail;
	p->m_next = m_poolHead;
	m_poolHead->m_previous = p;
}

void CP_NodeFactory::mb_destroyAll() {
	while (m_poolHead->m_previous != nullptr) {
		CP_StudentNode* p = m_poolHead->m_next;
		if (p == m_poolHead) {
			m_poolHead->m_previous = nullptr;
			m_poolHead->m_next = nullptr;
			p->m_previous = nullptr;
			p->m_next = nullptr;
			delete p;
			break;
		}
		CP_StudentNode* q = p->m_next;
		q->m_previous = p->m_previous;
		p->m_previous->m_next = q;
		if (m_poolHead->m_next == p) {
			m_poolHead->m_next = q;
		}
		if (m_poolHead->m_previous == p) {
			m_poolHead->m_previous = p->m_previous;
		}
		delete p;
	}
}
