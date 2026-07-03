#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

plot1 = pd.read_csv("GDP_2005_2025.csv")
plot1.plot(kind="line", x="Year", y=["China", "USA", "Russia", "France", "UK"])
plt.show()
plt.close()

plot2 = pd.read_csv("GDP_POP_2025.csv")
plt.figure(figsize=(10, 5))
ax1 = plt.subplot(1, 3, 1)
plot2.plot(kind="bar", x="Country", y="GDP", ax=ax1)
ax2 = plt.subplot(1, 3, 2)
plot2.plot(kind="bar", x="Country", y="Pop", ax=ax2)
ax3 = plt.subplot(1, 3, 3)
plot2.plot(kind="bar", x="Country", y=["Area"], ax=ax3)
plt.show()
plt.close()

plot3 = pd.read_csv("iris_hist.csv", header=None)
plt.figure(figsize=(10, 5))
ax1 = plt.subplot(1, 4, 1)
plot3[0].plot(kind="hist", bins=20, ax=ax1)
ax2 = plt.subplot(1, 4, 2)
plot3[1].plot(kind="hist", bins=20, ax=ax2)
ax3 = plt.subplot(1, 4, 3)
plot3[2].plot(kind="hist", bins=20, ax=ax3)
ax4 = plt.subplot(1, 4, 4)
plot3[3].plot(kind="hist", bins=20, ax=ax4)
plt.show()
plt.close()
