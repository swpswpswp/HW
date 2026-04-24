#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "StudentScore.h"
#include <string>
#include <map>

class ScoreManager {
private:
    std::map<std::string, StudentScore> scoreMap;  // 使用map存储，学号为键

public:
    // 构造函数
    ScoreManager();

    // 指令1：从文件读取成绩并添加到当前表单
    bool loadFromFile(const std::string& filename);

    // 指令2：添加学生成绩
    void addScore(const std::string& id, double score);

    // 指令3：删除指定学号的成绩
    bool deleteScore(const std::string& id);

    // 指令4：删除所有成绩
    void clearAllScores();

    // 指令5：修改指定学号的成绩
    bool updateScore(const std::string& id, double newScore);

    // 指令6：查询指定学号的成绩
    bool queryScore(const std::string& id) const;

    // 指令7：显示所有成绩
    void displayAllScores() const;

    // 指令8：保存成绩到文件
    bool saveToFile(const std::string& filename) const;

    // 获取当前记录数
    int getCount() const;
};

#endif