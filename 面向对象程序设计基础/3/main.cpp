#include <iostream>
#include <vector>
#include <iomanip>
#include "Shape.h"
#include "Triangle.h"
#include "Square.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Circle.h"
using namespace std;

int main() {
    vector<Shape*> shapes;
    int command;

    cout << fixed << setprecision(2); // 设置输出精度为两位小数

    while (true) {
        cout << "\n请输入命令 (1=三角形, 2=正方形, 3=五边形, 4=六边形, 5=圆, 0=统计并退出): ";
        cin >> command;

        if (command == 0) {
            break;
        }

        double param;
        Shape* shape = nullptr;

        switch (command) {
        case 1:
            cout << "请输入正三角形边长: ";
            cin >> param;
            shape = new Triangle(param);
            break;
        case 2:
            cout << "请输入正方形边长: ";
            cin >> param;
            shape = new Square(param);
            break;
        case 3:
            cout << "请输入正五边形边长: ";
            cin >> param;
            shape = new Pentagon(param);
            break;
        case 4:
            cout << "请输入正六边形边长: ";
            cin >> param;
            shape = new Hexagon(param);
            break;
        case 5:
            cout << "请输入圆的半径: ";
            cin >> param;
            shape = new Circle(param);
            break;
        default:
            cout << "无效命令！" << endl;
            continue;
        }

        if (shape) {
            shapes.push_back(shape);
            cout << "该图形周长: " << shape->getPerimeter() << endl;
            cout << "该图形面积: " << shape->getArea() << endl;
        }
    }

    // 统计汇总
    int totalCount = shapes.size();
    double totalPerimeter = 0.0;
    double totalArea = 0.0;

    for (const auto& s : shapes) {
        totalPerimeter += s->getPerimeter();
        totalArea += s->getArea();
    }

    cout << "\n========== 最终统计 ==========" << endl;
    cout << "图形总个数: " << totalCount << endl;
    cout << "所有图形总周长: " << totalPerimeter << endl;
    cout << "所有图形总面积: " << totalArea << endl;

    // 释放内存
    for (auto s : shapes) {
        delete s;
    }

    return 0;
}