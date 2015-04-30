// Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"
println(str)

let Constant = 0x1234   // let 声明常量
var Variable = 0xAFEC   // var 声明变量
var VarInt   = 8421
var VarFloat = 3.1415926
var VarDouble:Double = 2.71828182846    //如果初始类型信息不足，可以在变量后加":类型"
var VarF:Float = 0.1314


let s = str + String(Variable)  // 类型必需显示转换


// 可以通过在客串中加\()的方式把值转换成字符串
let Int2Str = "translate int in string with \(VarInt) \(str)"
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


// 创建空数组和空字典
var EmptyArray = [String]()
var EmptyDict  = [String:String]()
// or
var EmptArrayWithNoType = []
var EmptDictWithNoType = [:]

for cp in arrayList {
    println(cp)
}



var OptionalVar: String? = "hehe"
OptionalVar == nil
if let name = OptionalVar {
    println("Hello \(OptionalVar)")
}
else
{
    println("sssssss")
}


let word = "red apple"

//switch word {
//case "dd" :
//}




