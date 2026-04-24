#ifndef STUDENTSCORE_H
#define STUDENTSCORE_H

#include <string>
#include <iostream>

class StudentScore {
private:
    std::string studentId;
    double score;

public:
    // 构造函数
    StudentScore();
    StudentScore(const std::string& id, double s);

    // 获取学号
    std::string getId() const;

    // 获取成绩
    double getScore() const;

    // 设置成绩
    void setScore(double s);

    // 显示学生信息
    void display() const;

    // 转换为文件存储格式
    std::string toFileFormat() const;

    // 从文件格式解析
    static StudentScore fromFileFormat(const std::string& line);
};

#endif