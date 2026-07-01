#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

a=np.array([[8, 3, 2, 5], [6, 21, 15, 8], [34, 16, 20, 30]])
print("每列的最大值：", np.max(a, axis=0))
print("每列的均值：", np.mean(a, axis=0))
print("按第二列的数值大小对行排序：", a[a[:, 1].argsort()])
print("大于20的元素：", a[a > 20])