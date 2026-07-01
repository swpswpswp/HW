#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 身份证信息提取
id_num = input("请输入18位身份证号码：")

# （1）输出字符串长度
print(len(id_num))

# （2）截取前17位，判断是否为数字
first_17 = id_num[:17]
print(first_17.isdigit())

# （3）截取前6位，输出地址码
print(id_num[:6])

# （4）截取第7-14位，输出出生日期码
print(id_num[6:14])

# （5）截取第17位（倒着索引），输出性别码
print(id_num[-2])

# （6）截取最后一位（倒着索引），输出校验码，判断是否为字母
check_code = id_num[-1]
print(check_code)
print(check_code.isalpha())
