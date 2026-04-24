#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>
#include "SortProcessor.h"

int main() {
    SortProcessor processor;

    // 1. 输入数据
    processor.inputNumbers();

    // 2. 执行不去重排序
    processor.sortAndPrintWithVector();

    // 3. 执行去重排序
    processor.sortAndPrintWithSet();

    return 0;
}