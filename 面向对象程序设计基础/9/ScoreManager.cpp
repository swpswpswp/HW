#include "ScoreManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// 构造函数
ScoreManager::ScoreManager() {}

// 指令1：从文件读取成绩并添加到当前表单
bool ScoreManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "错误：无法打开文件 " << filename << endl;
        return false;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        StudentScore ss = StudentScore::fromFileFormat(line);
        if (!ss.getId().empty()) {
            // 如果学号已存在，询问是否覆盖
            if (scoreMap.find(ss.getId()) != scoreMap.end()) {
                cout << "学号 " << ss.getId() << " 已存在，是否覆盖？(y/n): ";
                char choice;
                cin >> choice;
                cin.ignore();
                if (choice != 'y' && choice != 'Y') {
                    continue;
                }
            }
            scoreMap[ss.getId()] = ss;
            count++;
        }
    }

    file.close();
    cout << "成功从文件 " << filename << " 读取 " << count << " 条记录" << endl;
    return true;
}

// 指令2：添加学生成绩
void ScoreManager::addScore(const string& id, double score) {
    if (scoreMap.find(id) != scoreMap.end()) {
        cout << "警告：学号 " << id << " 已存在，成绩将被覆盖" << endl;
    }
    scoreMap[id] = StudentScore(id, score);
    cout << "成功添加学号 " << id << " 的成绩: " << score << endl;
}

// 指令3：删除指定学号的成绩
bool ScoreManager::deleteScore(const string& id) {
    auto it = scoreMap.find(id);
    if (it != scoreMap.end()) {
        scoreMap.erase(it);
        cout << "成功删除学号 " << id << " 的成绩" << endl;
        return true;
    }
    else {
        cout << "错误：未找到学号 " << id << endl;
        return false;
    }
}

// 指令4：删除所有成绩
void ScoreManager::clearAllScores() {
    scoreMap.clear();
    cout << "已清空所有成绩记录" << endl;
}

// 指令5：修改指定学号的成绩
bool ScoreManager::updateScore(const string& id, double newScore) {
    auto it = scoreMap.find(id);
    if (it != scoreMap.end()) {
        it->second.setScore(newScore);
        cout << "成功将学号 " << id << " 的成绩修改为: " << newScore << endl;
        return true;
    }
    else {
        cout << "错误：未找到学号 " << id << endl;
        return false;
    }
}

// 指令6：查询指定学号的成绩
bool ScoreManager::queryScore(const string& id) const {
    auto it = scoreMap.find(id);
    if (it != scoreMap.end()) {
        it->second.display();
        return true;
    }
    else {
        cout << "错误：未找到学号 " << id << endl;
        return false;
    }
}

// 指令7：显示所有成绩
void ScoreManager::displayAllScores() const {
    if (scoreMap.empty()) {
        cout << "当前成绩表单为空" << endl;
        return;
    }

    cout << "\n========== 所有学生成绩 ==========" << endl;
    cout << "共有 " << scoreMap.size() << " 条记录" << endl;
    cout << "--------------------------------" << endl;

    for (const auto& pair : scoreMap) {
        pair.second.display();
    }
    cout << "================================\n" << endl;
}

// 指令8：保存成绩到文件
bool ScoreManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "错误：无法创建文件 " << filename << endl;
        return false;
    }

    for (const auto& pair : scoreMap) {
        file << pair.second.toFileFormat() << endl;
    }

    file.close();
    cout << "成功保存 " << scoreMap.size() << " 条记录到文件 " << filename << endl;
    return true;
}

// 获取当前记录数
int ScoreManager::getCount() const {
    return scoreMap.size();
}