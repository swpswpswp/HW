#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

a=np.arange(1001,1022)
np.random.shuffle(a)
for i in range(3):
    print(np.random.choice(a, size=5, replace=True))
