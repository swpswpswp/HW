#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 方式1：import 模块
import package_1.cal_area

# 方式2：from ... import ...
from package_1.cal_area import square_s, square_p

# 方式3：from ... import ... as ...
from package_1 import people as p

print("--- 几何函数测试 ---")
print("圆面积：", package_1.cal_area.circ_s(3))
print("圆周长：", package_1.cal_area.circ_p(3))
print("三角形面积：", package_1.cal_area.tria_s(3, 4, 5))
print("矩形周长：", package_1.cal_area.rect_p(3, 4))
print("正方形面积：", square_s(5))
print("正方形周长：", square_p(5))

print("\n--- People 类测试 ---")
p.People.print_welcome(p.People)
student = p.Student(2, "李学生", "li@tsinghua.edu.cn", "本科生", "计算机科学", 3.8)
student.query_info()
