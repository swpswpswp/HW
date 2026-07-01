#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

a=np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print("秩:", a.ndim)
print("形状:", a.shape)
print("转置:", a.T)
print("数据类型:", a.dtype)
print("元素数:", a.size)

b=np.arange(1,13,1)
print("数据类型：", b.dtype)
print("形状：", b.shape)

c=np.linspace(1,20,20,dtype=float)

d=np.full((6,7),5)
