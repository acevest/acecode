//
//  main.swift
//  AppleSwift
//
//  Created by Ace on 15/6/23.
//  Copyright (c) 2015年 Ace. All rights reserved.
//

import Foundation


let Constant = 0x1234   // let 声明常量
var Variable = 0xAFEC   // var 声明变量
var VarInt   = 8421
var VarFloat = 3.1415926
var VarDouble:Double = 2.71828182846    //如果初始类型信息不足，可以在变量后加":类型"
var VarF:Float = 0.1314
var str:String = "Hello, World!"


let ss = str + " " + String(Variable)  // 类型必需显示转换


// 可以通过在客串中加\()的方式把值转换成字符串
let Int2Str = "translate int in string with \(VarInt) \(ss)"
print(Int2Str)


// 数组
var arrayList = ["apple", "microsoft", "xx", "google", "tencent", "twitter"]
arrayList[2] = "amazon"
print(arrayList)

// 字典
var dict = [
    "apple" : "USA",
    "tencnet" : "CN"
]
print(dict)
print(dict["google"] ?? "default value")
print(dict["apple"]!)

// 创建空数组和空字典
var EmptyArray = [String]()
var EmptyDict  = [String:String]()
// or
//var EmptArrayWithNoType = []
//var EmptDictWithNoType = [:]

for cp in arrayList {
    print(cp)
}



var OptionalVar:String? = "hehe"
//OptionalVar = nil
if let name = OptionalVar {
    print("Hello \(OptionalVar)")
}
else
{
    print("sssssss")
}


let word = "ff"

switch word {
case "dd" :
    print("unknown")
case "ff" :
    print("fallthrough")
    fallthrough // 会走到下一个case
case "red apple", "blue apple" :
    print("red")
default:            // 必须在最后。。。
    print("default");
}


// 闭区间
for i in 0...3 {
    print(i, terminator: "")
}
print("")
// 开区间
for i in 0..<3 {
    print(i, terminator: "")
}


for i in 0..<arrayList.count {
    print("arrayList的第\(i+1)个元素为 \(arrayList[i])")
}

//let optIntStr = "ffffffff"
let optIntStr = "123"
let optInt = Int(optIntStr)
if optInt != nil {
    print("\(optIntStr) has integer value of \(optInt!)")
    print("\(optIntStr) has integer value of \(optInt)")
} else {
    print("\(optIntStr) could not be converted to an integer")
}


let possableString:String?="An optional string"
print(possableString!)
let assumedString:String!="An implicitly unwrapped optional string"
print(assumedString)


var opt:String="aaa"
// opt=nil // 如果声明没有? 或 ! 来表明这是一个可选类型，那么 nil的赋值不合法
print(opt, terminator: "")
//assert(opt != "aaa", "assert failed")


// String
var s = "aaaaaa\0bbbbb\tccccc\\\n\"\'"
print(s)

var emptySa = ""
var emptySb = String()

if emptySa.isEmpty && emptySb.isEmpty {
    print("emptySa and emptySb is empty")
}

var emojiStr = "😘😡👿😜"
for c in  emojiStr.characters {
    print(c, terminator: "")
}


var smileChar:Character = "😀"
emojiStr.append(smileChar)
print("  emojistr \(emojiStr) charactor count is \(emojiStr.characters.count)")


s = "Prefix----Suffix"
if s.hasPrefix("Prefix") && s.hasSuffix("Suffix") {
    print(s.lowercased())
    print(s.uppercased())
}


// Array
var IntArray:Array<Int>=[]
for i in 1...5 {
    IntArray.append(i)
}
IntArray += [0, -1, -2, -3, -4]
IntArray[0] = 1024
IntArray[1..<4]=[999, 888, 777]
IntArray.insert(1, at: 0)
IntArray.remove(at: 5)
IntArray.removeLast()
print(IntArray)
for (index, value) in IntArray.enumerated() {
    print("Item \(index+1): \(value)")
}


var StringArray = [String]()
StringArray.append("dd")
StringArray = []

var DoubleArray = [Double](repeating: 9.9, count: 3)
for i in 1...5 {
    DoubleArray.append(Double(i)*1.1)
}
print(DoubleArray)


// Set
var SetA=Set<Int>()
var SetB:Set<Character>=[]
var SetC: Set<Character> = ["a", "b", "b"]

SetA.insert(1)
SetA.insert(2)
SetA.insert(1)
if SetA.contains(1) {
    print(SetA)
}

for genre in SetA.sorted() {
    print("\(genre)")
}

let oddSet:Set = [1, 3, 5, 7, 9]
let evenSet:Set = [0, 2, 4, 6, 8]
print(oddSet.intersection(evenSet).sorted())  // 交
print(oddSet.union(evenSet).sorted())      // 并
print(oddSet.hashValue)


// Dict
var airports: [String:String] = ["TYO" : "Tokyo", "DUB":"Dublin"]
airports["LHR"] = "London"
airports["APL"] = "Apple Internation"
if let oldValue = airports.updateValue("Dublin Internation", forKey: "DUB") {
    print("The old value for DIB was \(oldValue)")
}

for (k, v) in airports {
    print("\(k): \(v)")
}

for k in airports.keys {
    print("Airport Code: \(k)")
}

for v in airports.values {
    print("Airport Name: \(v)")
}

print(airports)
airports["APL"] = nil   // Delete
print(airports)

if let removedValue = airports.removeValue(forKey: "DUB") {
    print("The removed airport's name is \(removedValue)")
} else {
    print("The airports dictionary does not contain a value for DUB")
}

// create an empty dict
var emptyDict = Dictionary<Int, String>()
emptyDict[16] = "sixteen"
emptyDict = [:]







