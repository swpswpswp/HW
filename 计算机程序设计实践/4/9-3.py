#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np

data = pd.read_csv(
    "Iris-0625.csv", index_col=0, header=0
)  # 第一列为行索引，第一行为列索引
print(data.head(5))
data.sort_values(by="SepalWidthCm", inplace=True, ascending=False)
print(data)
print(
    "花萼长度最大值：",
    data["SepalLengthCm"].max(),
    "花萼宽度最大值：",
    data["SepalWidthCm"].max(),
    "花瓣长度最大值：",
    data["PetalLengthCm"].max(),
    "花瓣宽度最大值：",
    data["PetalWidthCm"].max(),
)
print(
    "花萼长度最小值：",
    data["SepalLengthCm"].min(),
    "花萼宽度最小值：",
    data["SepalWidthCm"].min(),
    "花瓣长度最小值：",
    data["PetalLengthCm"].min(),
    "花瓣宽度最小值：",
    data["PetalWidthCm"].min(),
)
print(
    "花萼长度平均值：",
    data["SepalLengthCm"].mean(),
    "花萼宽度平均值：",
    data["SepalWidthCm"].mean(),
    "花瓣长度平均值：",
    data["PetalLengthCm"].mean(),
    "花瓣宽度平均值：",
    data["PetalWidthCm"].mean(),
)
print(
    "花萼长度中位数：",
    data["SepalLengthCm"].median(),
    "花萼宽度中位数：",
    data["SepalWidthCm"].median(),
    "花瓣长度中位数：",
    data["PetalLengthCm"].median(),
    "花瓣宽度中位数：",
    data["PetalWidthCm"].median(),
)
print("各列之间相关系数：", data.corr())
group = data.groupby("Species")
print("各组数量：", group.size())
print("各组平均值：", group.mean())
print("各组最小值：", group.min())
print("各组最大值：", group.max())
