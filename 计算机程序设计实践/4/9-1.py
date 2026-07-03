#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np

x = [5, 3, 9, 1, 8, 7]
y = [2, 1, 5, 3, 4, 6]
index_x = ["j", "b", "c", "d", "e", "f"]
index_y = ["a", "b", "c", "d", "e", "f"]
s_1 = pd.Series(x, index=index_x)
s_2 = pd.Series(y, index=index_y)
z = np.sin(s_1) + np.cos(s_2)
print(z)
