#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["font.size"] = 10

gdp = {
    "中国": 18.54,
    "美国": 30.76,
    "俄罗斯": 2.80,
    "法国": 3.11,
    "英国": 3.70,
    "其他": 65.00,
}
fig = plt.figure(figsize=(10, 8))
plt.pie(
    gdp.values(),
    labels=gdp.keys(),
    autopct="%1.1f%%",
    explode=(0.1, 0, 0, 0, 0, 0),
    wedgeprops={"edgecolor": "black"},
)
plt.title("2025年部分国家GDP（万亿美元）")
plt.savefig("gdp.png")
plt.show()
plt.close()
