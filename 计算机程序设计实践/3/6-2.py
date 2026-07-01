#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def del_even(num_list):
    """删除列表中的偶数"""
    del_list = []  # 存放被删除的偶数
    for num in num_list:
        if num % 2 == 0:
            del_list.append(num)  # 原实现直接删除num_list中的偶数，导致遍历时跳过了某些元素，改为先将偶数存入del_list，再统一删除

    for num in del_list:
        num_list.remove(num)

    print("被删除的偶数: ", del_list)
    print("剩余的数: ", numbers)

if __name__ == '__main__':
    numbers = [1, 2, 4, 5, 6, 8, 10]
    del_even(numbers)
