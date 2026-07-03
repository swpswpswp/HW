#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd

cpi = pd.read_csv("CPI_202505-202605.csv")
cpi.to_excel("CPI_202505-202605.xlsx", index=False)
newcpi = pd.DataFrame(pd.read_excel("CPI_202505-202605.xlsx"))
print(newcpi)
