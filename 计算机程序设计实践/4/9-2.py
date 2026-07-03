#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np

a = np.array(
    [
        [19.40, 14.05, 960],
        [30.62, 3.37, 983],
        [2.56, 1.46, 1710],
        [3.37, 0.68, 55],
        [4.00, 0.69, 24],
    ]
)
data = pd.DataFrame(
    a, columns=["GDP", "Pop", "Area"], index=["China", "USA", "Russia", "France", "UK"]
)
print(data.iloc[1:4, 1:3])
print(data[(data["GDP"] > 10) & (data["Area"] > 900)])  # 输出GDP>10且Area>900的行
data["CPI"] = [-0.4, 2.9, 8.1, 0.9, 3.8]
print(data)
data.loc["UK", "Area"] = 24.41
data.drop(columns=["GDP"], inplace=True)
print(data)
