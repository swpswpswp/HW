#include "Lambda.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

double random_double(double a, double b) {
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dist{a, b};
    return dist(gen);
}

Lambda::Lambda() {
    cout << "Lambda constructor" << endl;
}

void Lambda::f() {
    int n;
    do{
        cout << "请输入一个大于3的整数:";
        cin >> n;
    }while(n <= 3);
    double s = random_double(1, 10);
    [s]()->{
        vector<double> v1(n);
        vector<double> v2(n);
        for(int i = 0; i < n; i++) {
            v1[i] = random_double(1, 10);
            v2[i] = random_double(1, 10);
        }
        auto r1 = [s,v1]()->{return s * v1;};
        auto r2 = [v1,v2]()->{return v1 * v2;};
        cout << "r1 = " << r1() << endl;
        cout << "r2 = " << r2() << endl;
    }();
}