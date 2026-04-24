#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>

class SortProcessor {
private:
    std::vector<int> dataVector; 
    std::set<int> dataSet;      

    void clearInputStream() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    void inputNumbers() {
        std::cout << "请输入一系列整数（以空格或回车分隔，输入非数字字符结束）：" << std::endl;

        std::string line;
        int num;

        while (std::getline(std::cin, line)) {
            std::istringstream iss(line);
            while (iss >> num) {
                dataVector.push_back(num);
                dataSet.insert(num);
            }

            if (iss.fail() && !iss.eof()) {
                break;
            }
        }

        std::cout << "输入结束，共读取 " << dataVector.size() << " 个整数。" << std::endl;
    }

    void sortAndPrintWithVector() {
        if (dataVector.empty()) {
            std::cout << "没有输入任何整数，无法进行排序。" << std::endl;
            return;
        }

        std::vector<int> sortedVec = dataVector;
        std::sort(sortedVec.begin(), sortedVec.end());

        std::cout << "\n【使用 std::vector + std::sort 排序结果（不去重）】:" << std::endl;
        for (size_t i = 0; i < sortedVec.size(); ++i) {
            std::cout << sortedVec[i] << " ";
        }
        std::cout << std::endl;
    }

    void sortAndPrintWithSet() {
        if (dataSet.empty()) {
            std::cout << "没有输入任何整数，无法进行排序。" << std::endl;
            return;
        }

        std::cout << "\n【使用 std::set 排序结果（去重且升序）】:" << std::endl;
        for (const int& val : dataSet) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    size_t getInputCount() const {
        return dataVector.size();
    }
};