#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def quadratic(a, b, c):
    """解方程ax^2+bx+c=0"""
    d = b ** 2 - 4 * a * c
    try:
        if d < 0:
            raise ValueError('该方程无解！')
        x1 = (-b + d ** 0.5)/(2 * a)
        x2 = (-b - d ** 0.5)/(2 * a)
        return x1, x2
    except ValueError as e:
        print(e)
        return None, None

if __name__ == '__main__':
    try:
        a = int(input("请输入a的值："))
        b = int(input("请输入b的值："))
        c = int(input("请输入c的值："))
    except ValueError:
        print("输入的值不合法！")
        exit()

    r1, r2 = quadratic(a, b, c)
    print(f'x1 = {r1}', f'x2 = {r2}')
