#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: image.py
#      Author: Zhao Yanbai
#              Sat Mar 31 17:56:02 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-
class Image :
    def __init__(self, width, height, filename="", background="#FFFFFF") :
        # 以'__'开头的变量名为私有成员变量
        self.__width    = width
        self.__height   = height
        self.__filename = filename
        self.__background = background

        self.__data     = {}
        self.__colors   = {self.__background}

    @property
    def width(self) :
        return (self.__width)

    #@property
    #def width() :
    #    return self.__width

    @width.setter
    def width(self, width) :
        assert width >= 0, "Width must be non-negative"
        self.__width = width

    @property
    def height(self) :
        return (self.__height)

    @property
    def filename(self) :
        return (self.__filename)

    @property
    def background(self) :
        return (self.__background)

    @property
    def colors(self) :
        return set(self.__colors)

imgA = Image(10, 10)
print(imgA.width)
try :
    imgA.width = -111   # why no assertion error ???????
except AssertionError as aerr :
    print("Error:", aerr) 
print(imgA.width)
