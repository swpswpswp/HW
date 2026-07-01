#include <iostream>
using namespace std;
#include "CP_StudentSystem.h"

CP_StudentSystem::CP_StudentSystem() : m_product(m_factory) {}

void CP_StudentSystem::mb_run() {
	cin.tie(nullptr);
	CP_Student s;
	int c;
	do {
		c = 7;
		if (!(cin >> c)) {
			break;
		}
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
				if (s.m_score >= 0 && s.m_ID > 0) {
					m_product.mb_addStudent(s);
				}
			} while (s.m_ID > 0);
			break;
		case 2:
			cout << "删除学生，请输入这位学生的学号：";
			s.m_ID = -1;
			cin >> s.m_ID;
			if (s.m_ID > 0) {
				m_product.mb_deleteById(s.m_ID);
			}
			break;
		case 3:
			cout << "删除学生，请输入这些学生的成绩：";
			s.m_score = -1;
			cin >> s.m_score;
			if (s.m_score >= 0) {
				m_product.mb_deleteByScore(s.m_score);
			}
			break;
		case 4:
			cout << "显示成绩，请输入这位学生的学号：";
			s.m_ID = -1;
			cin >> s.m_ID;
			if (s.m_ID > 0) {
				int score = 0;
				if (m_product.mb_queryScoreById(s.m_ID, score)) {
					cout << score << endl;
				}
			}
			break;
		case 5:
			cout << "显示学号，请输入这些同学的成绩：";
			s.m_score = -1;
			cin >> s.m_score;
			if (s.m_score >= 0) {
				m_product.mb_queryIdsByScore(s.m_score);
			}
			break;
		case 6:
			m_product.mb_printAllStudent();
			break;
		}
		if (cin.peek() == '\n' || cin.peek() == '\r') {
			cin.ignore(10000, '\n');
		}
		cin.clear();
	} while (c >= 0);
}
