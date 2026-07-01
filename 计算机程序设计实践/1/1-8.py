#!/usr/bin/env python3
# -*- coding: utf-8 -*-
valid_months = (
    '一月', '二月', '三月', '四月', '五月', '六月',
    '七月', '八月', '九月', '十月', '十一月', '十二月'
)
peak_months = ('四月', '五月', '六月', '七月', '八月', '九月', '十月')

month = input("请输入月份（如：一月）：")
age = int(input("请输入年龄："))

if month not in valid_months or age < 0 or age > 100:
    print("输入错误，请检查月份或年龄。")
else:
    if age >= 60 or age < 6:
        price = 0
    elif 6 <= age <= 17:
        base = 30 if month in peak_months else 20
        price = base / 2
    else:
        price = 30 if month in peak_months else 20
    print(f"颐和园门票价格为：{price}元/张")
