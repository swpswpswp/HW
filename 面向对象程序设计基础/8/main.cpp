#include "BigInt.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 测试函数
void testAddition() {
    cout << "========== 加法测试 ==========" << endl;

    // 测试案例1：正数 + 正数（无进位）
    BigInt a1("123");
    BigInt b1("456");
    cout << "案例1 - 正数+正数（无进位）: " << a1 << " + " << b1 << " = " << (a1 + b1) << " (期望: 579)" << endl;

    // 测试案例2：正数 + 正数（有进位）
    BigInt a2("999");
    BigInt b2("1");
    cout << "案例2 - 正数+正数（有进位）: " << a2 << " + " << b2 << " = " << (a2 + b2) << " (期望: 1000)" << endl;

    // 测试案例3：负数 + 正数（结果为正）
    BigInt a3("-5");
    BigInt b3("8");
    cout << "案例3 - 负数+正数（结果为正）: " << a3 << " + " << b3 << " = " << (a3 + b3) << " (期望: 3)" << endl;

    // 测试案例4：负数 + 负数
    BigInt a4("-123");
    BigInt b4("-456");
    cout << "案例4 - 负数+负数: " << a4 << " + " << b4 << " = " << (a4 + b4) << " (期望: -579)" << endl;

    // 测试案例5：零 + 正数
    BigInt a5("0");
    BigInt b5("9999");
    cout << "案例5 - 零+正数: " << a5 << " + " << b5 << " = " << (a5 + b5) << " (期望: 9999)" << endl;

    cout << endl;
}

void testSubtraction() {
    cout << "========== 减法测试 ==========" << endl;

    // 测试案例1：正数 - 正数（结果为正）
    BigInt a1("789");
    BigInt b1("123");
    cout << "案例1 - 正数-正数（结果为正）: " << a1 << " - " << b1 << " = " << (a1 - b1) << " (期望: 666)" << endl;

    // 测试案例2：正数 - 正数（结果为负）
    BigInt a2("100");
    BigInt b2("999");
    cout << "案例2 - 正数-正数（结果为负）: " << a2 << " - " << b2 << " = " << (a2 - b2) << " (期望: -899)" << endl;

    // 测试案例3：负数 - 正数
    BigInt a3("-50");
    BigInt b3("30");
    cout << "案例3 - 负数-正数: " << a3 << " - " << b3 << " = " << (a3 - b3) << " (期望: -80)" << endl;

    // 测试案例4：正数 - 负数
    BigInt a4("100");
    BigInt b4("-200");
    cout << "案例4 - 正数-负数: " << a4 << " - " << b4 << " = " << (a4 - b4) << " (期望: 300)" << endl;

    // 测试案例5：零 - 负数
    BigInt a5("0");
    BigInt b5("-1000");
    cout << "案例5 - 零-负数: " << a5 << " - " << b5 << " = " << (a5 - b5) << " (期望: 1000)" << endl;

    cout << endl;
}

void testLargeNumbers() {
    cout << "========== 大数测试 ==========" << endl;

    BigInt a1("12345678901234567890");
    BigInt b1("98765432109876543210");
    cout << "大数加法: " << a1 << " + " << b1 << " = " << (a1 + b1) << endl;

    BigInt a2("99999999999999999999");
    BigInt b2("1");
    cout << "大数进位: " << a2 << " + " << b2 << " = " << (a2 + b2) << endl;

    BigInt a3("10000000000000000000");
    BigInt b3("1");
    cout << "大数减法: " << a3 << " - " << b3 << " = " << (a3 - b3) << endl;

    cout << endl;
}

void testComparison() {
    cout << "========== 比较运算测试 ==========" << endl;

    BigInt a1("100");
    BigInt b1("200");
    cout << a1 << " < " << b1 << " : " << (a1 < b1 ? "true" : "false") << " (期望: true)" << endl;

    BigInt a2("-100");
    BigInt b2("-200");
    cout << a2 << " > " << b2 << " : " << (a2 > b2 ? "true" : "false") << " (期望: true)" << endl;

    BigInt a3("0");
    BigInt b3("0");
    cout << a3 << " == " << b3 << " : " << (a3 == b3 ? "true" : "false") << " (期望: true)" << endl;

    BigInt a4("500");
    BigInt b4("500");
    cout << a4 << " <= " << b4 << " : " << (a4 <= b4 ? "true" : "false") << " (期望: true)" << endl;

    BigInt a5("-50");
    BigInt b5("-30");
    cout << a5 << " < " << b5 << " : " << (a5 < b5 ? "true" : "false") << " (期望: true)" << endl;

    cout << endl;
}

void testCompoundAssignment() {
    cout << "========== 复合赋值测试 ==========" << endl;

    BigInt a1("100");
    a1 += BigInt("200");
    cout << "+= 测试: 100 += 200 = " << a1 << " (期望: 300)" << endl;

    BigInt a2("500");
    a2 -= BigInt("300");
    cout << "-= 测试: 500 -= 300 = " << a2 << " (期望: 200)" << endl;

    BigInt a3("50");
    a3 += BigInt("-30");
    cout << "+= 负数测试: 50 += -30 = " << a3 << " (期望: 20)" << endl;

    BigInt a4("10");
    a4 -= BigInt("-5");
    cout << "-= 负数测试: 10 -= -5 = " << a4 << " (期望: 15)" << endl;

    BigInt a5("0");
    a5 += BigInt("0");
    cout << "零操作测试: 0 += 0 = " << a5 << " (期望: 0)" << endl;

    cout << endl;
}

void testEdgeCases() {
    cout << "========== 边界情况测试 ==========" << endl;

    BigInt a1("000123");  // 带前导零
    BigInt b1("456");
    cout << "前导零测试: " << a1 << " + " << b1 << " = " << (a1 + b1) << endl;

    BigInt a2("-000");
    cout << "负零测试: " << a2 << " = " << a2 << " (期望: 0)" << endl;

    BigInt a3("+123");
    cout << "正号测试: " << a3 << " = " << a3 << " (期望: 123)" << endl;

    BigInt a4("99999999999999999999");
    BigInt b4("1");
    cout << "最大进位测试: " << a4 << " + 1 = " << (a4 + b4) << endl;

    BigInt a5("1");
    BigInt b5("99999999999999999999");
    cout << "大数相减测试: 1 - " << b5 << " = " << (a5 - b5) << endl;

    cout << endl;
}

int main() {
    cout << "==================== 超长整数类测试程序 ====================" << endl;
    cout << endl;

    testAddition();
    testSubtraction();
    testLargeNumbers();
    testComparison();
    testCompoundAssignment();
    testEdgeCases();

    cout << "==================== 所有测试完成 ====================" << endl;

    return 0;
}