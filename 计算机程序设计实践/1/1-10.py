#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import random

lang_tuple = ('Python', 'Java', 'C++')
rules = {
    'Python': 'Java',
    'Java': 'C++',
    'C++': 'Python',
}

while True:
    player_choice = input("请输入编程语言（Python/Java/C++），输入 quit 退出：")
    if player_choice == 'quit':
        break
    if player_choice not in lang_tuple:
        print("输入错误，请输入 Python、Java 或 C++。")
        continue

    pc_choice = random.choice(lang_tuple)
    print(f"电脑选择：{pc_choice}")
    print(f"玩家选择：{player_choice}")

    match (player_choice, pc_choice):
        case (p, c) if p == c:
            result = '平局'
        case (p, c) if rules[p] == c:
            result = '玩家胜'
        case _:
            result = '电脑胜'
    print(f"本局结果：{result}")
