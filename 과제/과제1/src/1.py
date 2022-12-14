# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""


def height():
    mountain = input()
    if mountain[0] == "\\" or mountain[-1] == "/" or \
            mountain.count("\\") != mountain.count("/"):
        print(0)
    else:
        height = 0
        height_list = []
        for i in mountain:
            if i == '/':
                height += 1
            else:
                height -= 1
            height_list.append(height)
        print(max(height_list))


height()
