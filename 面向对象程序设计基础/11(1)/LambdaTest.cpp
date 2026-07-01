#include "Lambda.h"
#include "LambdaTest.h"
#include <iostream>

using namespace std;

LambdaTest::LambdaTest() {
    cout << "LambdaTest constructor" << endl;
}

LambdaTest::~LambdaTest() {
    cout << "LambdaTest destructor" << endl;
}

void LambdaTest::test() {
    Lambda lambda;
    lambda.f(1);
    lambda.f(4);
    lambda.f(100);
    lambda.f(10000);
}