#!/usr/bin/env python3
# -*- coding: utf-8 -*-

id=input("请输入18位身份证号码：")
print("身份证号码长度：", len(id))
print("前17位是否为数字：", id[0:17].isdigit())
print("前6位的地址码：", id[0:6])
print("第7-14位的出生日期码：", id[6:14])
print("第17位的性别码：", id[-2])
print("第18位的校验码：", id[-1])
print("第18位是否为字母：",id[-1].isalpha())