# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 17:30:40 2020

@author: 주원
"""

st = input()


def checkNormal_1(st):
    valid = False
    big_count_left = st.count('[')
    big_count_right = st.count(']')
    middle_count_left = st.count('{')
    middle_count_right = st.count('}')
    small_count_left = st.count('(')
    small_count_right = st.count(')')
    if big_count_left == big_count_right and \
        middle_count_left == middle_count_right and \
            small_count_left == small_count_right:
        valid = True
    return valid

