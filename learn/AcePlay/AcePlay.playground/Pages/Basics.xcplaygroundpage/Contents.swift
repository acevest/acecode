//: Playground - noun: a place where people can play

import UIKit

let str = "Hello, playground.小狗:🐶 锤子:🔨"

// Index
let strInx:String.Index = str.startIndex
strInx.successor()
print(strInx)

for c in str.characters {
    print(c, terminator: "")
}
print()

// Print separator & terminator
var company:Array<String> = [ "Apple", "Google", "Facebook", "Tencent" ]
print(company[0], company[1], company[2], company[3], separator: "#", terminator: " $$$$$\n")

printLine("Count company Array 1")
for (i,v) in company.enumerate() {  // enumerate 返回的是 index value 组成的元组
    print(i, v, separator: " - ", terminator: "\n")
}

printLine("Count company Array 2")
company.insert("Alibaba", atIndex: company.count)
for i in 0..<company.count {
    print(i, company[i], separator: " - ")
}
company.removeLast()

var someIntsA: [Int] = []
var someIntsB = [Int]()
var someIntsC = [Int](count: 10, repeatedValue: 1)
someIntsA.append(1)
someIntsB.replaceRange(Range<Int>(0..<someIntsB.count), with: [1,3,4])
someIntsC.removeAtIndex(4)
someIntsC[1...4] = [1, 2, 3, 4, 5, 6]  //实际赋值量可以与下标Range量不等

printLine("Set")

// Set 只能存储能提供计算出hash value的类型
str.hashValue
3.1415926.hashValue
2005061325.hashValue
true.hashValue

//var SetA: Set<Int> = []
var SetB = Set<Character>()
var SetC: Set<String> = ["ASM", "C", "C++", "go", "Swift"]
//var SetD: Set = ["mov", "pop", "push", "xchg"]  // 可以通过数组类型推断出Set的类型
SetB.insert("A")
SetB.insert("c")
SetB.insert("c")
SetB.count
//SetC.removeFirst()
SetC.remove("ASM")

if let removedVal = SetC.remove("ASM") {
    print("\(removedVal) I'm over it.")
} else {
    print("I never much cared for that.")
    SetC.insert("ASM")
}

if SetC.contains("Swift") {
    print("SetC Contains Swift")
}

for v in SetC.sort() {
    print(v)
}

printLine("Dictionary")
//var DictA = Dictionary<Int, String>()
//var DictB = ["KA":"VA", "KB":"VB", "KC":"VC"]
//var DictC: [String:String] = [:]
var DictD = [Int:String]()

DictD[1]  = "V1"
DictD[4]  = "V2"
DictD[99] = "V3"
DictD[36] = "F4"
if let oldValue = DictD.updateValue("V4", forKey: 36) { // means: if let oldValue = DictD[36]
    print("The old value for Key:36 was \(oldValue)")
}

print("DictD Item Count: ", DictD.count)

for (k, v) in DictD {
    print("Key:", k, " Value: ", v)
}

for key in DictD.keys.sort() {
    print(key)
}

for value in DictD.values.sort() {
    print(value)
}

let keys = [Int](DictD.keys)
print(keys)
