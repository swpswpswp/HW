#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

a=np.loadtxt('scores.csv', delimiter=',')
print(a)
print("每列的最大值：", np.max(a, axis=0))
print("每列的最小值：", np.min(a, axis=0))
print("每列的均值：", np.mean(a, axis=0))
print("每列的方差：", np.var(a, axis=0))
print("每行的均值：", np.mean(a, axis=1))
a[:,0]=np.sqrt(a[:,0])*10
print("处理后的成绩单：", a)
print("按各行平均值从小到大排序：", a[a[:, 0].argsort()])
np.savetxt('scores_out.csv', a, delimiter=',')
