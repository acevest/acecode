#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: gps.py
#      Author: Zhao Yanbai
#              2018-11-01 22:13:59 Thursday CST
# Description: none
# ------------------------------------------------------------------------

#line = '$GNRMC,135019.000,A,3032.7184,N,10401.4127,E,1.20,51.76,011118,,,A*42'

#from math import sin, cos, sqrt, fabs, atan2
import math
from math import pi

a = 6378245.0;
ee = 0.00669342162296594323;


class Storage(dict) :
    def __getattr__(self, key) :
        try :
            return self[key]
        except KeyError, k:
            raise AttributeError, k

    def __setattr__(self, key, value) :
        self[key] = value

    def __delattr__(self, key) :
        try :
            del self[key]
        except KeyError, k:
            raise AttributeError, k

    def __repr__(self) :
        return '<Storage ' + dict.__repr__(self) + '>'

class GPS(Storage) :
    def __init__(self, lng = 0.0, lat = 0.0) :
        self.lng = lng
        self.lat = lat

gps_data = []

def CalculateDegree(d, m) :
    d = float(d) + float(m) / 60.0
    return d
    return str(d)
    
    
def CalculateGPSDegree(line) :
    fields = line.split(',')
    if len(fields) != 13 :
        return None

    flag, latitude, ulat, longitude, ulon = fields[2], fields[3], fields[4], fields[5], fields[6]

    #print(line)

    if flag == 'N' or flag == 'V' :
        return None
    # s = ''
    # s = s + ulat + '' +  CalculateDegree(latitude[0:2], latitude[2:])  + '\t'
    # s = s + ulon + '' +  CalculateDegree(longitude[0:3], longitude[3:])+ '\n'
    # s = "{{Long:{0},Lat:{1}}},".format(CalculateDegree(longitude[0:3], longitude[3:]), CalculateDegree(latitude[0:2], latitude[2:]))
    # return s

    gps = GPS()
    gps.lng = CalculateDegree(longitude[0:3], longitude[3:])
    gps.lat = CalculateDegree(latitude[0:2], latitude[2:])
    gps_data.append(gps)

def transformLng(x, y) :
    ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * math.sqrt(abs(x));
    ret += (20.0 * math.sin(6.0 * x * pi) + 20.0 * math.sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * math.sin(x * pi) + 40.0 * math.sin(x / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * math.sin(x / 12.0 * pi) + 300.0 * math.sin(x / 30.0 * pi)) * 2.0 / 3.0;
    return ret;

def transformLat(x, y) :
    ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * math.sqrt(abs(x));
    ret += (20.0 * math.sin(6.0 * x * pi) + 20.0 * math.sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * math.sin(y * pi) + 40.0 * math.sin(y / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * math.sin(y / 12.0 * pi) + 320 * math.sin(y * pi / 30.0)) * 2.0 / 3.0;
    return ret;

def wgs82_to_gcj02(lng, lat) :
    dLat = transformLat(lng - 105.0, lat - 35.0)
    dLng = transformLng(lng - 105.0, lat - 35.0)
    radLat = lat / 180.0 * pi
    magic = math.sin(radLat)
    magic = 1 - ee * magic * magic
    sqrtMagic = math.sqrt(magic)

    dLng = (dLng * 180.0) / (a / sqrtMagic * math.cos(radLat) * pi)
    dLat = (dLat * 180.0) / ((a * (1 -ee)) / (magic * sqrtMagic) * pi)

    gcjLng = lng + dLng
    gcjLat = lat + dLat

    x = GPS(gcjLng, gcjLat)
    #print(lng, lat)
    #print(x.lng, x.lat)
    return x

def gcj02_to_bd09(lng, lat) :
    x = lng
    y = lat
    z = math.sqrt(x * x + y * y) + 0.00002 * math.sin(y * pi);
    theta = math.atan2(y, x) + 0.000003 * math.cos(x * pi);
    bdLng = z * math.cos(theta) + 0.0065;
    bdLat = z * math.sin(theta) + 0.006;
    x = GPS(bdLng, bdLat);
    return x

def bd09_to_gcj02(lng, lat) :
    x = lng - 0.0065
    y = lat - 0.006;
    z = math.sqrt(x * x + y * y) - 0.00002 * math.sin(y * pi);
    theta = math.atan2(y, x) - 0.000003 * math.cos(x * pi);
    gcjLng = z * math.cos(theta);
    gcjLat = z * math.sin(theta);

    x = GPS(gcjLng, gcjLat)
    return x

def out_of_china(lng, lat) :
    if lng < 72.004 or lng > 137.8347 :
        return True
    if lat < 0.8293 or lat > 55.8271 :
        return True

    return False

def transform(lng, lat) :
    if (out_of_china(lng, lat)) :
        return GPS(lng, lat)

    dLng = transformLng(lng - 105.0, lat - 35.0);
    dLat = transformLat(lng - 105.0, lat - 35.0);
    radLat = lat / 180.0 * pi;
    magic = math.sin(radLat);
    magic = 1 - ee * magic * magic;
    sqrtMagic = math.sqrt(magic);
    dLng = (dLng * 180.0) / (a / sqrtMagic * math.cos(radLat) * pi);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    mgLng = lng + dLng;
    mgLat = lat + dLat;
    return GPS(mgLng, mgLat);

def gcj02_to_wgs84(lng, lat) :
    gps = transform(lng, lat);
    wgsLng = lng * 2 - gps.lng;
    wgsLat = lat * 2 - gps.lat;
    x = GPS(wgsLng, wgsLat);
    return x


if __name__ == '__main__':
    fd = open('./gps.1.txt')
    lines = fd.readlines()
    fd.close()

    for line in lines :
        CalculateGPSDegree(line)

    for d in gps_data:
        #print('-'*80)
        print("{{Long:{0},Lat:{1}}},".format(d.lng, d.lat))
        g = wgs82_to_gcj02(d.lng, d.lat)
        #print("{{Long:{0},Lat:{1}}},".format(g.lng, g.lat))
        b = gcj02_to_bd09(g.lng, g.lat)
        print("{{Long:{0},Lat:{1}}},".format(b.lng, b.lat))
        #print('-'*80)
        #print(wgs82_to_gcj02(d.lng, d.lat))
        pass


    a1 = bd09_to_gcj02(104.040711667,30.5491566667)
    a2 = gcj02_to_wgs84(a1.lng, a1.lat)
    print(a2)
