#include <iostream>
#include <chrono>
using namespace std;
#include "Calendar.h"


int main() {
    int year, month, day;
    // 1. 获取当前时间戳
    std::time_t now = std::time(nullptr);

    // 2. 定义 tm 结构体变量
    std::tm local_tm;

    // 3. 调用 localtime_s
    if (localtime_s(&local_tm, &now) == 0) {
        // 4. 提取年月日 
        year = local_tm.tm_year + 1900;
        month = local_tm.tm_mon + 1;
        day = local_tm.tm_mday;
    }
	Calendar c;
    c.set(year, month, day);
    c.calculate();
	return 0;
}