// BigInt.h
#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>

class BigInt {
private:
    std::string num;  // 存储数字字符串，高位在前，低位在后
    bool isNegative;  // 是否为负数

    // 辅助函数：去除前导零
    void trim();

    // 辅助函数：比较两个正整数的绝对值大小
    // 返回：1 表示 abs(a) > abs(b), -1 表示 a < b, 0 表示相等
    static int compareAbsolute(const std::string& a, const std::string& b);

    // 辅助函数：两个正整数相加（无符号）
    static std::string addAbsolute(const std::string& a, const std::string& b);

    // 辅助函数：两个正整数相减（无符号，要求 a >= b）
    static std::string subtractAbsolute(const std::string& a, const std::string& b);

public:
    // 构造函数
    BigInt();                           // 默认构造，值为0
    BigInt(const std::string& str);     // 从字符串构造
    BigInt(long long n);                // 从整数构造
    BigInt(const BigInt& other);        // 拷贝构造

    // 赋值运算符
    BigInt& operator=(const BigInt& other);

    // 算术运算符重载
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;

    // 复合赋值运算符
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);

    // 比较运算符
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    // 输入输出流运算符（友元）
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
    friend std::istream& operator>>(std::istream& is, BigInt& bi);

    // 获取值（转换为字符串）
    std::string toString() const;

    // 获取绝对值（作为字符串）
    std::string getAbsoluteValue() const;

    // 判断是否为零
    bool isZero() const;
};

#endif