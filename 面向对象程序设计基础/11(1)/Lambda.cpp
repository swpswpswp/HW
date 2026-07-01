#include "Lambda.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

double random_double(double a, double b) {
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_real_distribution<double> dist{ a, b };
    return dist(gen);
}

//重载*运算符为向量数乘
vector<double> operator*(double s, const vector<double>& v) {
    vector<double> result(v.size());
    for (int i = 0; i < v.size(); i++) {
        result[i] = s * v[i];
    }
    return result;
}

//重载*运算符为向量内积
double operator*(const vector<double>& v1, const vector<double>& v2) {
    double result = 0;
    for (int i = 0; i < v1.size(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

//重载<<运算符为向量输出
ostream& operator<<(ostream& os, const vector<double>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

Lambda::Lambda() {
    cout << "Lambda constructor" << endl;
}

Lambda::~Lambda() {}

void Lambda::f(int n) {
    cout << "n = " << n << endl;
    if (n <= 3) {
        cout << "n must be greater than 3" << endl;
        return;
    }
    double s = random_double(1, 10);
    cout << "s = " << s << endl;
    [s, n]()->void {
        vector<double> v1(n);
        vector<double> v2(n);
        for (int i = 0; i < n; i++) {
            v1[i] = random_double(1, 10);
            v2[i] = random_double(1, 10);
        }
        auto r1 = [s, v1]()->vector<double> {return s * v1; };
        auto r2 = [v1, v2]()->double {return v1 * v2; };
        cout << "v1 = " << v1 << endl;
        cout << "v2 = " << v2 << endl;
        cout << "r1 = " << r1() << endl;
        cout << "r2 = " << r2() << endl;
        }();
}