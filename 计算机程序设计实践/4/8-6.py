#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["font.size"] = 10


def plot_3dsurf(X, Y, Z):
    fig = plt.figure(figsize=(12, 8))
    ax = plt.axes(projection="3d")
    surf = ax.plot_surface(X, Y, Z, cmap="rainbow", alpha=0.8)
    fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10)
    ax.view_init(elev=30, azim=45)
    ax.set_xlabel("X轴")
    ax.set_ylabel("Y轴")
    ax.set_zlabel("Z轴")
    ax.set_title("3D曲面图")
    os.makedirs("figures", exist_ok=True)
    plt.savefig("figures/8-5-3d.jpg")
    plt.show()


if __name__ == "__main__":
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    Z = np.sin(np.sqrt(X**2 + Y**2)) * np.exp(-0.1 * (X**2 + Y**2))
    plot_3dsurf(X, Y, Z)
