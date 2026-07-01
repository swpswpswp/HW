#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def tria_p(a, b, c):
    """计算三角形周长，输入三条边长"""
    return a + b + c

def tria_s(a, b, c):
    """计算三角形面积，输入三条边长"""
    s = (a + b + c) / 2
    area = (s * (s - a) * (s - b) * (s - c)) ** 0.5
    return area

def rect_p(a, b):
    """计算矩形周长，输入长和宽"""
    return 2 * (a + b)

def rect_s(a, b):
    """计算矩形面积，输入长和宽"""
    return a * b

def circ_p(r):
    """计算圆形周长，输入半径"""
    return 2 * 3.14 * r

def circ_s(r):
    """计算圆形面积，输入半径"""
    return 3.14 * r ** 2

def square_p(a):
    """计算正方形周长，输入边长"""
    return 4 * a

def square_s(a):
    """计算正方形面积，输入边长"""
    return a * a


if __name__ == "__main__":
    print("三角形周长：", tria_p(3, 4, 5))
    print("三角形面积：", tria_s(3, 4, 5))
    print("矩形周长：", rect_p(3, 4))
    print("矩形面积：", rect_s(3, 4))
    print("圆形周长：", circ_p(3))
    print("圆形面积：", circ_s(3))
    print("正方形周长：", square_p(5))
    print("正方形面积：", square_s(5))
