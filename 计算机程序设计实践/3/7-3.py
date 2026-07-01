#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

A=np.array([[1,2,1],[2,-1,3],[3,1,2]])
b=np.array([[7],[7],[18]])
print("A的行列式的值：", np.linalg.det(A))
print("A的特征值和特征向量：",np.linalg.eig(A))
print("A的逆矩阵：",np.linalg.inv(A))
print("A×b的结果：",np.dot(A,b))
print("Ax=b的解：",np.linalg.solve(A,b))