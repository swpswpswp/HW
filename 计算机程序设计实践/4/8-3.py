#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["font.size"] = 10

population = {"中国": 14.01, "美国": 3.42, "俄罗斯": 1.46, "法国": 0.67, "英国": 0.69}
fig = plt.figure(figsize=(10, 8))
plt.bar(population.keys(), population.values())
plt.xlabel("国家")
plt.ylabel("人口")
plt.yticks(range(2, 15, 2))
plt.title("2025年部分国家人口（亿）")
plt.savefig("population.png")
plt.show()
plt.close()
