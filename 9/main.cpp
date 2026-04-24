#include "ScoreManager.h"
#include <iostream>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\n========== 学生成绩管理系统 ==========" << endl;
    cout << "指令1: 从文件读取成绩" << endl;
    cout << "指令2: 添加学生成绩" << endl;
    cout << "指令3: 删除指定成绩" << endl;
    cout << "指令4: 删除所有成绩" << endl;
    cout << "指令5: 修改学生成绩" << endl;
    cout << "指令6: 查询学生成绩" << endl;
    cout << "指令7: 显示所有成绩" << endl;
    cout << "指令8: 保存成绩到文件" << endl;
    cout << "指令-1: 退出系统" << endl;
    cout << "=====================================" << endl;
    cout << "请输入指令: ";
}

int main() {
    ScoreManager manager;
    int command;
    string input;

    cout << "欢迎使用学生成绩管理系统！" << endl;

    while (true) {
        displayMenu();
        cin >> command;
        cin.ignore();

        if (command == -1) {
            cout << "感谢使用，再见！" << endl;
            break;
        }

        switch (command) {
        case 1:
            cout << "请输入文件名: ";
            getline(cin, input);
            manager.loadFromFile(input);
            break;

        case 2: {
            string id;
            double score;
            cout << "请输入学号: ";
            getline(cin, id);
            cout << "请输入成绩: ";
            cin >> score;
            manager.addScore(id, score);
            break;
        }

        case 3:
            cout << "请输入要删除的学号: ";
            getline(cin, input);
            manager.deleteScore(input);
            break;

        case 4:
            cout << "确认删除所有成绩？(y/n): ";
            cin >> command;
            if (command == 'y' || command == 'Y') {
                manager.clearAllScores();
            }
            break;

        case 5: {
            string id;
            double score;
            cout << "请输入学号: ";
            getline(cin, id);
            cout << "请输入新成绩: ";
            cin >> score;
            manager.updateScore(id, score);
            break;
        }

        case 6:
            cout << "请输入要查询的学号: ";
            getline(cin, input);
            manager.queryScore(input);
            break;

        case 7:
            manager.displayAllScores();
            break;

        case 8:
            cout << "请输入保存的文件名: ";
            getline(cin, input);
            manager.saveToFile(input);
            break;

        default:
            cout << "无效指令，请重新输入" << endl;
        }
    }

    return 0;
}