#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 1、元组装包
tuple_China = '中国', 14.12, '北京', ['上海', '广州', '深圳']

# 2、修改元组中的可变元素
tuple_China[3].append('杭州')
print("人口（亿）: ", tuple_China[1])
print("主要城市: ", tuple_China[-1])

# 3、元组与列表互相转换
list_China = list(tuple_China)
tuple_China = tuple(list_China)
print(list_China, type(tuple_China))

# 4、元组解包
country, population, capital, major_cities = tuple_China
print(country, population, major_cities, sep='\n')
