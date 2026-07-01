#!/usr/bin/env python3
# -*- coding: utf-8 -*-
list_GDP = [['Year', 'China'],
            [2022, 17.88, 25.74, 2.27],
            [2023, 17.79, 27.36, 2.02]]
GDP_2025 = [2025, 19.40, 30.62, 2.56]
GDP_2024 = [2024, 18.94, 29.20, 2.16]

# （1）在列表 list_GDP 的第一个元素（列表）的最后，插入序列 ['USA', 'France']
list_GDP[0].extend(['USA', 'France'])

# （2）把列表 GDP_2025 插入到列表 list_GDP 的尾部
list_GDP.append(GDP_2025)

# （3）把列表 list_GDP 中的"France"修改为"Russia"
list_GDP[0][list_GDP[0].index('France')] = 'Russia'

# （4）把列表 GDP_2024 插入到列表 list_GDP 的最后一个元素（列表）之前
list_GDP.insert(-1, GDP_2024)

# （5）取出最后一个元素中除第一个元素之外的所有元素，排序后输出最大值
x = list_GDP[-1][1:]
x.sort()
print(max(x))
