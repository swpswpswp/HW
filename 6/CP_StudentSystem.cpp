#include <iostream>
using namespace std;
#include "CP_StudentSystem.h"

void CP_StudentSystem::mb_printAllStudent() {
	if (m_head == nullptr || m_head->m_previous == nullptr) {
		cout << "目前还没有学生。" << endl;
		return;
	}
	CP_ChainDoubleLink* p = m_head;
	int n = 1;
	do {
		cout << "[" << n << "]:ID(" << p->m_data.m_ID << "),Score(" << p->m_data.m_score << ")" << endl;
		p = p->m_next;
		n++;
	} while (p != m_head);
}
void CP_StudentSystem::mb_run() {
	m_head = new CP_ChainDoubleLink;
	if (m_head = nullptr) {
		return;
	}
	CP_Student s;
	CP_ChainDoubleLink* p;
	int c;
	do {
		c = 7;
		cin >> c;
		if (c > 6 || c == 0) {
			cout << "错误：输入格式有误！" << endl;
		}
		switch (c) {
		case 1:
			do {
				s.m_ID = 0;
				s.m_score = -1;
				cout << "添加学生的学号与成绩，以0结束：";
				cin >> s.m_ID;
				if (s.m_ID > 0) {
					cin >> s.m_score;
				}
				if (s.m_ID < 0) {
					cout << "学号是正整数。" << endl;
				}
				if (s.m_score >= 0) {
					p = m_head->mb_createNode();
					if (p != nullptr) {
						p->m_data = s;
						m_head->mb_sortById();
					}
					else {
						cout << "内存申请失败！" << endl;
					}
				}
			} while (s.m_ID > 0);
			break;
		case 2:
			cout << "删除学生，请输入这位学生的学号：";
			s.m_ID = -1;
			cin >> s.m_ID;
			if (s.m_ID > 0) {
				p = m_head->mb_findNodeById(s.m_ID);
				if (p != nullptr) {
					m_head->mb_deleteNode(p);
				}
				else {
					cout << "没有找到该学号的学生。" << endl;
				}
			}
			break;
		case 3:
			cout << "删除学生，请输入这些学生的成绩：";
			s.m_score = -1;
			cin >> s.m_score;
			if (s.m_score >= 0) {
				do {
					p = m_head->mb_findNodeByScore(s.m_score);
					if (p != nullptr) {
						m_head->mb_deleteNode(p);
					}
					else {
						cout << "已经不存在该成绩的学生。" << endl;
						break;
					}
				} while (1);
			}
			break;
		case 4:
			cout << "显示成绩，请输入这位学生的学号：";
			s.m_ID = -1;
			cin >> s.m_ID;
			if (s.m_ID > 0) {
				p = m_head->mb_findNodeById(s.m_ID);
				if (p != nullptr) {
					cout << p->m_data.m_score << endl;
				}
				else {
					cout << "没有找到该学号的学生。" << endl;
				}
			}
			break;
		case 5:
			cout << "显示学号，请输入这些同学的成绩：";
			s.m_score = -1;
			cin >> s.m_score;
			if (s.m_score >= 0) {
				do {
					p = m_head->mb_findNodeByScore(s.m_score);
					if (p != nullptr) {
						cout << p->m_data.m_ID << endl;
					}
					else {
						cout << "已经不存在该成绩的学生。" << endl;
						break;
					}
				} while (1);
			}
			break;
		case 6:
			mb_printAllStudent();
			break;
		}
		cin.clear();
		cin.ignore();
	} while (c >= 0);
	delete m_head;
	m_head = nullptr;
}