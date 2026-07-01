#!/usr/bin/env python3
# -*- coding: utf-8 -*-
operations_research = [101, 102, 103, 104, 105, 106, 107]
applied_stats = [103, 104, 105, 108, 109, 110]

# （1）分别创建集合 or_set 和 stats_set
or_set = set(operations_research)
stats_set = set(applied_stats)

# （2）找出同时选了两门课的学生学号
print(or_set & stats_set)

# （3）找出选了第一门、但没选第二门课的学生学号
print(or_set - stats_set)

# （4）找出两门课中所有不重复的学生学号
print(or_set | stats_set)
