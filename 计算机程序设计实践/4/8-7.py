#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["font.size"] = 10

img = plt.imread("panda.jpg").copy()
plt.imshow(img)
plt.show()
img[:, :, 1:3] = 0  # 把表示绿色和蓝色的像素值设置为0
plt.imshow(img)
plt.imsave("panda_no_green_blue.jpg", img)
plt.show()
