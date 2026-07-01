#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import math

x = int(input('输入第1个非零整数：'))
y = int(input('输入第2个非零整数：'))
print(f'{x} * {y} = ', x * y)
print(f'{x} ** {y} = ', x ** 2)
print(f'{x} / {y} = ', x / y)
print(f'{x} // {y} = ', x // y)
print(f'{x} + 0.1 = ', x + 0.1)
print(f'{x} 的 {y} 次幂 = ', math.pow(x, y))
print(f'e的 {x}({math.e}) 次幂 = ', math.exp(x))
print(f'{x} 的平方根 = ', math.sqrt(x))
print(f'{x} 的正弦函数值 = ', math.sin(x))
print(f'{x} 的伽玛函数值 = ', math.gamma(x))
