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
println(Int2Str)


// 数组
var arrayList = ["apple", "microsoft", "xx", "google", "tencent", "twitter"]
arrayList[2] = "amazon"
println(arrayList)

// 字典
var dict = [
    "apple" : "USA",
    "tencnet" : "CN"
]
println(dict)
println(dict["apple"])
println(dict["apple"]!)

// 创建空数组和空字典
var EmptyArray = [String]()
var EmptyDict  = [String:String]()
// or
var EmptArrayWithNoType = []
var EmptDictWithNoType = [:]

for cp in arrayList {
    println(cp)
}



var OptionalVar:String? = "hehe"
//OptionalVar = nil
if let name = OptionalVar {
    println("Hello \(OptionalVar)")
}
else
{
    println("sssssss")
}


let word = "ff"

switch word {
case "dd" :
    println("unknown")
case "ff" :
    println("fallthrough")
    fallthrough // 会走到下一个case
case "red apple", "blue apple" :
    println("red")
default:            // 必须在最后。。。
    println("default");
}


// 闭区间
for i in 0...3 {
    print(i)
}
println("")
// 开区间
for i in 0..<3 {
    print(i)
}


for i in 0..<arrayList.count {
    println("arrayList的第\(i+1)个元素为 \(arrayList[i])")
}

//let optIntStr = "ffffffff"
let optIntStr = "123"
let optInt = optIntStr.toInt()
if optInt != nil {
    println("\(optIntStr) has integer value of \(optInt!)")
    println("\(optIntStr) has integer value of \(optInt)")
} else {
    println("\(optIntStr) could not be converted to an integer")
}


let possableString:String?="An optional string"
println(possableString!)
let assumedString:String!="An implicitly unwrapped optional string"
println(assumedString)


var opt:String="aaa"
// opt=nil // 如果声明没有? 或 ! 来表明这是一个可选类型，那么 nil的赋值不合法
print(opt)
//assert(opt != "aaa", "assert failed")


// String
var s = "aaaaaa\0bbbbb\tccccc\\\n\"\'"
println(s)

var emptySa = ""
var emptySb = String()

if emptySa.isEmpty && emptySb.isEmpty {
    println("emptySa and emptySb is empty")
}

var emojiStr = "😘😡👿😜"
for c in  emojiStr {
    print(c)
}


var smileChar:Character = "😀"
emojiStr.append(smileChar)
println("  emojistr \(emojiStr) charactor count is \(count(emojiStr))")


s = "Prefix----Suffix"
if s.hasPrefix("Prefix") && s.hasSuffix("Suffix") {
    println(s.lowercaseString)
    println(s.uppercaseString)
}


// Array
var IntArray:Array<Int>=[]
for i in 1...5 {
    IntArray.append(i)
}
IntArray += [0, -1, -2, -3, -4]
IntArray[0] = 1024
IntArray[1..<4]=[999, 888, 777]
IntArray.insert(1, atIndex: 0)
IntArray.removeAtIndex(5)
IntArray.removeLast()
println(IntArray)
for (index, value) in enumerate(IntArray) {
    println("Item \(index+1): \(value)")
}


var StringArray = [String]()
StringArray.append("dd")
StringArray = []

var DoubleArray = [Double](count:3, repeatedValue:9.9)
for i in 1...5 {
    DoubleArray.append(Double(i)*1.1)
}
println(DoubleArray)


// Set
var SetA=Set<Int>()
var SetB:Set<Character>=[]
var SetC: Set<Character> = ["a", "b", "b"]

SetA.insert(1)
SetA.insert(2)
SetA.insert(1)
if SetA.contains(1) {
    println(SetA)
}

for genre in sorted(SetA) {
    println("\(genre)")
}

let oddSet:Set = [1, 3, 5, 7, 9]
let evenSet:Set = [0, 2, 4, 6, 8]
println(sorted(oddSet.intersect(evenSet)))  // 交
println(sorted(oddSet.union(evenSet)))      // 并
println(oddSet.hashValue)


// Dict
var airports: [String:String] = ["TYO" : "Tokyo", "DUB":"Dublin"]
airports["LHR"] = "London"
airports["APL"] = "Apple Internation"
if let oldValue = airports.updateValue("Dublin Internation", forKey: "DUB") {
    println("The old value for DIB was \(oldValue)")
}

for (k, v) in airports {
    println("\(k): \(v)")
}

for k in airports.keys {
    println("Airport Code: \(k)")
}

for v in airports.values {
    println("Airport Name: \(v)")
}

println(airports)
airports["APL"] = nil   // Delete
println(airports)

if let removedValue = airports.removeValueForKey("DUB") {
    println("The removed airport's name is \(removedValue)")
} else {
    println("The airports dictionary does not contain a value for DUB")
}

// create an empty dict
var emptyDict = Dictionary<Int, String>()
emptyDict[16] = "sixteen"
emptyDict = [:]







