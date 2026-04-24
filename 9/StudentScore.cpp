#include "StudentScore.h"
#include <iomanip>
#include <sstream>

using namespace std;

// 构造函数实现
StudentScore::StudentScore() : studentId(""), score(0.0) {}

StudentScore::StudentScore(const string& id, double s)
    : studentId(id), score(s) {
}

// 获取学号
string StudentScore::getId() const {
    return studentId;
}

// 获取成绩
double StudentScore::getScore() const {
    return score;
}

// 设置成绩
void StudentScore::setScore(double s) {
    score = s;
}

// 显示学生信息
void StudentScore::display() const {
    cout << "学号: " << studentId << ", 成绩: "
        << fixed << setprecision(2) << score << endl;
}

// 转换为文件存储格式
string StudentScore::toFileFormat() const {
    return studentId + "," + to_string(score);
}

// 从文件格式解析
StudentScore StudentScore::fromFileFormat(const string& line) {
    size_t commaPos = line.find(',');
    if (commaPos == string::npos) {
        return StudentScore();
    }
    string id = line.substr(0, commaPos);
    double s = stod(line.substr(commaPos + 1));
    return StudentScore(id, s);
}