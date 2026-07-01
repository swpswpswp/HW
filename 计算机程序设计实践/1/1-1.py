#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def print_var(var_a):
    """输出对象的值及其三个属性：
    身份（identity）对象在内存中的地址
    类型（type）对象所属的数据类型
    值（value）对象所表示的数据
    """
    print("值：",var_a)  # 输出对象的值
    print("内存地址：",id(var_a))  # 输出对象的内存地址
    print("对象类型：",type(var_a))
    
# 创建一个str对象
var_str="Hello World!"
print_var(var_str)