#!/usr/bin/env python3
# -*- coding: utf-8 -*-

card_dict={}

def query_balance(id):  # 查询余额
    return card_dict.get(id, 0)

def top_up(id, amount=100):  # 圈存
    if id in card_dict:
        card_dict[id] += amount
    else:
        card_dict[id] = amount

def consume(id, amount=10):  # 消费
    if id in card_dict and card_dict[id] >= amount:
        card_dict[id] -= amount
        return True
    else:
        return False
    
card_id = input("请输入校园卡号：")
card_balance = input("请输入校园卡余额：")
card_dict[card_id] = int(card_balance)
while True:
    operation = input("请输入操作类型（查询余额（i）/圈存（r）/消费（c）/退出（q））：")
    match operation:
        case 'i':
            balance = query_balance(card_id)
            print(f"校园卡号：{card_id}，余额：{balance}")
        case 'r':
            amount = int(input("请输入圈存金额："))
            top_up(card_id,amount)
            print(f"校园卡号：{card_id}，圈存成功，余额：{card_dict[card_id]}")
        case 'c':
            amount = int(input("请输入消费金额："))
            if consume(card_id, amount):
                print(f"校园卡号：{card_id}，消费成功，余额：{card_dict[card_id]}")
            else:
                print(f"校园卡号：{card_id}，余额不足，消费失败")
        case 'q':
            print("退出操作")
            break