#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 输入矩形的长和宽，计算周长和面积
width = float(input("请输入矩形的宽:"))
height = float(input("请输入矩形的长:"))
c = (width + height) * 2
s = width * height

# 使用占位符格式化输出
print("矩形的周长为：%10.2f" % (c,))

# Python3.6之后可以使用f字符串格式化输出
print(f"矩形的面积为：{s:10.2f}")

# 删除变量，不是必须的，Python有引用计数器，自动垃圾回收
del c, s
