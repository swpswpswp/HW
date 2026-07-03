#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]  # 黑体
plt.rcParams["axes.unicode_minus"] = False  # 解决负号显示为方块
plt.rcParams["font.size"] = 10

data = np.loadtxt("iris_scatter.csv", delimiter=",", skiprows=1, usecols=(0, 1, 2, 3))

fig = plt.figure(figsize=(10, 8))

ax1 = fig.add_subplot(2, 2, 1)
n, bins, patches = ax1.hist(data[:, 0], bins=20)
print("花萼长度直方图：", n, bins)
ax1.set_xlabel("花萼长度")
ax1.set_ylabel("频数")
ax1.set_title("花萼长度直方图")
ax2 = fig.add_subplot(2, 2, 2)
n, bins, patches = ax2.hist(data[:, 1], bins=20)
print("花萼宽度直方图：", n, bins)
ax2.set_xlabel("花萼宽度")
ax2.set_ylabel("频数")
ax2.set_title("花萼宽度直方图")
ax3 = fig.add_subplot(2, 2, 3)
n, bins, patches = ax3.hist(data[:, 2], bins=20)
print("花瓣长度直方图：", n, bins)
ax3.set_xlabel("花瓣长度")
ax3.set_ylabel("频数")
ax3.set_title("花瓣长度直方图")
ax4 = fig.add_subplot(2, 2, 4)
n, bins, patches = ax4.hist(data[:, 3], bins=20)
print("花瓣宽度直方图：", n, bins)
ax4.set_xlabel("花瓣宽度")
ax4.set_ylabel("频数")
ax4.set_title("花瓣宽度直方图")

plt.tight_layout()
plt.savefig("iris_scatter_hist.png")
plt.show()
plt.close()
