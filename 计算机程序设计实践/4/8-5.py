#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["font.size"] = 10

data = np.loadtxt("iris_scatter.csv", delimiter=",", skiprows=1, usecols=(2, 3))

fig = plt.figure(figsize=(10, 8))
plt.scatter(data[:, 0], data[:, 1])
plt.xlabel("花瓣长度")
plt.ylabel("花瓣宽度")
plt.title("花瓣长度与花瓣宽度散点图")
plt.savefig("iris_scatter_scatter.png")
plt.show()
plt.close()
