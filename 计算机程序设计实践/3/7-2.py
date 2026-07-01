#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

num_arr=np.linspace(1,30,30).reshape(10,3)

arr_1=num_arr[6:9,0:3]

arr_2=num_arr[0:9:2,1:3]

arr_3=num_arr[num_arr>10]

arr_4=num_arr[1:9:3,1:3]

print("num_arr:\n",num_arr)
print("arr_1:\n",arr_1)
print("arr_2:\n",arr_2)
print("arr_3:\n",arr_3)
print("arr_4:\n",arr_4)