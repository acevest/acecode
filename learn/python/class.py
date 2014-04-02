#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	class.py
#      Author:	Zhao Yanbai
#		Wed Jan 18 20:23:17 2012
# Description:	none
# --------------------------------------------------------------------------
import math
class point :
    def __init__(self, parent=None) :
        print("Class Name: ", self.__class__.__name__)


p1 = point()
try :
    print(p1.x)
except AttributeError as aerr :
    print("Error: ", aerr)

p1.x = 1
print(p1.x)
p1.y = 2
print(p1.y)

p2 = point()

print("-"*72)
class Point :
    def __init__(self, x=0, y=0) :
        self.x = x
        self.y = y
    @property
    def distance_from_origin(self) :
        return math.hypot(self.x, self.y)
    def __eq__(self, other) :
        return self.x == other.x and self.y == other.y
    def __str__(self) :
        return "({0.x!r},{0.y!r})".format(self)

a = Point()
print(a)
b = Point(3, 4)
print(b.distance_from_origin)
print(a == b)


class Circle(Point) :
    def __init__(self, radius, x=0, y=0) :
        super().__init__(x, y)
        self.__radius = radius
    def area(self) :
        return math.pi * (self.radius ** 2)
    area = property(area)
    def __eq__(self, other) :   # 多态
        return super().__eq__(other) and self.radius == other.radius

    @property
    def radius() :
        return radius
    @radius.setter
    def radius(self, radius) :
        assert radius > 0, "Radius must be nonzero and non-negative"
        self.__radius = radius
    @radius.getter
    def radius(self) :
        return self.__radius

c = Circle(radius=100)
print(c.area)
d = Circle(100)
print(c == d)
d.radius = 1
print(c == d)

################
e = c
e.radius = 1
print(e == c)
try :
    e.radius = -1
except AssertionError as aerr :
    print("Error:", aerr) 
