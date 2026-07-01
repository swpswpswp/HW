#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class People:
    institution = "Tsinghua University"

    def __init__(self, id, name, email):
        self.id = id
        self.name = name
        self.email = email

    @classmethod
    def update_institution(cls, new_institution):
        cls.institution = new_institution

    @staticmethod
    def print_welcome(cls):
        print(f"欢迎来到{cls.institution}！")

    def query_info(self):
        print(f"ID: {self.id}, 姓名: {self.name}, 邮箱: {self.email}, 学校: {self.institution}")


class Professor(People):
    def __init__(self, id, name, email, title, salary, course):
        super().__init__(id, name, email)
        self.title = title
        self.salary = salary
        self.course = course

    def update_title(self, new_title):
        self.title = new_title

    def update_salary(self, new_salary):
        self.salary = new_salary

    def update_course(self, new_course):
        self.course = new_course

    def query_info(self):
        super().query_info()
        print(f"职称: {self.title}, 工资: {self.salary}, 课程: {self.course}")


class Student(People):
    def __init__(self, id, name, email, degree, major, gpa):
        super().__init__(id, name, email)
        self.degree = degree
        self.major = major
        self.gpa = gpa

    def update_degree(self, new_degree):
        self.degree = new_degree

    def update_major(self, new_major):
        self.major = new_major

    def update_gpa(self, new_gpa):
        self.gpa = new_gpa

    def query_info(self):
        super().query_info()
        print(f"专业: {self.major}, 绩点: {self.gpa}, 学位: {self.degree}")


if __name__ == "__main__":
    People.print_welcome(People)
    professor = Professor(1, "张教授", "zhang@tsinghua.edu.cn", "教授", 20000, "计算机科学")
    student = Student(2, "李学生", "li@tsinghua.edu.cn", "本科生", "计算机科学", 3.8)
    professor.query_info()
    student.query_info()
