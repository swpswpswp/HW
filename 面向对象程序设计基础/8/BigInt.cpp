// BigInt.cpp
#include "BigInt.h"
#include <algorithm>
#include <cctype>

// 去除前导零
void BigInt::trim() {
    if (num.empty()) {
        num = "0";
        isNegative = false;
        return;
    }

    size_t pos = 0;
    while (pos < num.length() - 1 && num[pos] == '0') {
        pos++;
    }
    if (pos > 0) {
        num = num.substr(pos);
    }

    // 如果结果是0，将符号设为正
    if (num == "0") {
        isNegative = false;
    }
}

// 比较两个正整数的绝对值大小
int BigInt::compareAbsolute(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        return a.length() > b.length() ? 1 : -1;
    }
    return a.compare(b);
}

// 两个正整数相加
std::string BigInt::addAbsolute(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// 两个正整数相减（要求 a >= b）
std::string BigInt::subtractAbsolute(const std::string& a, const std::string& b) {
    std::string result;
    int borrow = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0) {
        int diff = (a[i] - '0') - borrow;
        if (j >= 0) diff -= (b[j] - '0');

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result.push_back(diff + '0');
        i--;
        j--;
    }

    std::reverse(result.begin(), result.end());

    // 去除前导零
    size_t pos = 0;
    while (pos < result.length() - 1 && result[pos] == '0') {
        pos++;
    }
    return result.substr(pos);
}

// 默认构造函数
BigInt::BigInt() : num("0"), isNegative(false) {}

// 从字符串构造
BigInt::BigInt(const std::string& str) {
    if (str.empty()) {
        num = "0";
        isNegative = false;
        return;
    }

    size_t start = 0;
    isNegative = false;

    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }
    else if (str[0] == '+') {
        start = 1;
    }

    num = str.substr(start);
    trim();
}

// 从整数构造
BigInt::BigInt(long long n) {
    if (n < 0) {
        isNegative = true;
        n = -n;
    }
    else {
        isNegative = false;
    }

    if (n == 0) {
        num = "0";
        isNegative = false;
        return;
    }

    num = "";
    while (n > 0) {
        num.push_back(n % 10 + '0');
        n /= 10;
    }
    std::reverse(num.begin(), num.end());
}

// 拷贝构造
BigInt::BigInt(const BigInt& other) {
    num = other.num;
    isNegative = other.isNegative;
}

// 赋值运算符
BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        num = other.num;
        isNegative = other.isNegative;
    }
    return *this;
}

// 加法运算符
BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;

    // 情况1：两者同号
    if (isNegative == other.isNegative) {
        result.num = addAbsolute(num, other.num);
        result.isNegative = isNegative;
    }
    // 情况2：符号不同
    else {
        int cmp = compareAbsolute(num, other.num);
        if (cmp > 0) {
            result.num = subtractAbsolute(num, other.num);
            result.isNegative = isNegative;
        }
        else if (cmp < 0) {
            result.num = subtractAbsolute(other.num, num);
            result.isNegative = other.isNegative;
        }
        else {
            result.num = "0";
            result.isNegative = false;
        }
    }

    result.trim();
    return result;
}

// 减法运算符
BigInt BigInt::operator-(const BigInt& other) const {
    // a - b = a + (-b)
    BigInt negOther = other;
    negOther.isNegative = !other.isNegative;
    return *this + negOther;
}

// 复合加法赋值
BigInt& BigInt::operator+=(const BigInt& other) {
    *this = *this + other;
    return *this;
}

// 复合减法赋值
BigInt& BigInt::operator-=(const BigInt& other) {
    *this = *this - other;
    return *this;
}

// 等于运算符
bool BigInt::operator==(const BigInt& other) const {
    return isNegative == other.isNegative && num == other.num;
}

// 不等于运算符
bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

// 小于运算符
bool BigInt::operator<(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        return isNegative;  // 负数为真
    }

    if (isNegative) {
        // 两者都为负数，绝对值大的更小
        return compareAbsolute(num, other.num) > 0;
    }
    else {
        // 两者都为正数
        return compareAbsolute(num, other.num) < 0;
    }
}

// 大于运算符
bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

// 小于等于运算符
bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

// 大于等于运算符
bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

// 输出运算符
std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
    if (bi.isNegative && bi.num != "0") {
        os << '-';
    }
    os << bi.num;
    return os;
}

// 输入运算符
std::istream& operator>>(std::istream& is, BigInt& bi) {
    std::string str;
    is >> str;
    bi = BigInt(str);
    return is;
}

// 转换为字符串
std::string BigInt::toString() const {
    if (isNegative && num != "0") {
        return "-" + num;
    }
    return num;
}

// 获取绝对值
std::string BigInt::getAbsoluteValue() const {
    return num;
}

// 判断是否为零
bool BigInt::isZero() const {
    return num == "0";
}