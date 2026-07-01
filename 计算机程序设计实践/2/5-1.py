#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import shutil

MY_ID = "2025011999"
DATA_DIR = "data"
CSV_PATH = os.path.join(DATA_DIR, f"{MY_ID}.csv")
BACKUP_PATH = os.path.join("..", f"{MY_ID}.csv.backup")


def is_chinese(text):
    return bool(text) and bool(re.fullmatch(r"[\u4e00-\u9fff]+", text))


def input_student(index):
    while True:
        student_id = input(f"请输入第{index}位学生的学号（10位数字）：").strip()
        if not re.fullmatch(r"\d{10}", student_id):
            print("学号格式错误，请重新输入。")
            continue

        name = input(f"请输入第{index}位学生的姓名（中文，不能为空）：").strip()
        if not is_chinese(name):
            print("姓名格式错误，请重新输入。")
            continue

        gender = input(f"请输入第{index}位学生的性别（中文，不能为空）：").strip()
        if not is_chinese(gender):
            print("性别格式错误，请重新输入。")
            continue

        grade_str = input(f"请输入第{index}位学生的成绩（0-100的整数）：").strip()
        if not grade_str.isdigit() or not (0 <= int(grade_str) <= 100):
            print("成绩格式错误，请重新输入。")
            continue

        return f"{student_id},{name},{gender},{grade_str}"


os.makedirs(DATA_DIR, exist_ok=True)

with open(CSV_PATH, "w", encoding="utf-8") as f:
    for i in range(1, 6):
        f.write(input_student(i) + "\n")

shutil.copy(CSV_PATH, BACKUP_PATH)

with open(BACKUP_PATH, "r", encoding="utf-8") as f:
    for line in f:
        print(line, end="")
