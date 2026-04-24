#include <iostream>
using namespace std;
#include "CP_ChainDoubleLink.h"

CP_ChainDoubleLink::~CP_ChainDoubleLink() {
	if (m_previous == nullptr) {
		return;
	}
	m_previous->m_next = nullptr;
	delete m_next;
}
CP_ChainDoubleLink* CP_ChainDoubleLink::mb_createNode() {
	if (m_previous == nullptr) {
		m_previous = this;
		m_next = this;
		return this;
	}
	CP_ChainDoubleLink* pNew = nullptr;
	pNew = new(nothrow)CP_ChainDoubleLink;
	if (pNew == nullptr) {
		return nullptr;
	}
	CP_ChainDoubleLink* p = m_previous;
	m_previous = pNew;
	m_previous->m_next = this;
	p->m_next = m_previous;
	m_previous->m_previous = p;
	return pNew;
}
void CP_ChainDoubleLink::mb_deleteNode(CP_ChainDoubleLink* p) {
	if (m_previous == nullptr) {
		return;
	}
	if (p == this) {
		if (p->m_previous == this) {
			p->m_previous = nullptr;
			return;
		}
		m_data = p->m_next->m_data;
		p = p->m_next;
	}
	CP_ChainDoubleLink* q;
	for (q = m_next;(q != p) && (q != this);) {
		if (q != nullptr) {
			q = q->m_next;
		}
		else {
			break;
		}
	}
	if (q == this) {
		return;
	}
	if (q != p) {
		return;
	}
	q = p->m_previous;
	q->m_next = p->m_next;
	q = p->m_next;
	q->m_previous = p->m_previous;
	p->m_previous = p;
	delete p;
}
CP_ChainDoubleLink* CP_ChainDoubleLink::mb_findNodeById(int id){
	if (m_previous == nullptr) {
		return nullptr;
	}
	CP_ChainDoubleLink* p = this;
	do {
		if (p->m_data.m_ID == id) {
			return p;
		}
		p = p->m_next;
	} while (p != this);
	return nullptr;
}
CP_ChainDoubleLink* CP_ChainDoubleLink::mb_findNodeByScore(int score) {
	if (m_previous == nullptr) {
		return nullptr;
	}
	CP_ChainDoubleLink* p = this;
	do {
		if (p->m_data.m_score == score) {
			return p;
		}
		p = p->m_next;
	} while (p != this);
	return nullptr;
}
void CP_ChainDoubleLink::mb_sortById() {
	if (m_previous == nullptr) {
		return;
	}
	if (m_previous == this) {
		return;
	}
	CP_ChainDoubleLink* p = this, * q, * q1;
	do {
		q = m_previous;
		do {
			q1 = q->m_previous;
			if (q1->m_data.m_ID > q->m_data.m_ID) {
				gb_swapStudent(q1->m_data, q->m_data);
			}
			q = q1;
		} while (q != p);
	} while (p != m_previous);
}