//: [Previous](@previous)

import Foundation

var str = "Hello, playground"

//: [Next](@next)

var company:Array<String> = [ "Apple", "Google", "Facebook", "Tencent" ]

// Print separator & terminator
print(company[0], company[1], company[2], company[3], separator: "#", terminator: " $$$$$\n")

// 遍历数组
for v in company {
    print("Company: \(v)")
}

printLine("Count company Array 1")
for (i,v) in company.enumerated() {  // enumerate 返回的是 index value 组成的元组
    print(i, v, separator: " - ", terminator: "\n")
}

printLine("Count company Array 2")
company.insert("Alibaba", at: company.count)
for i in 0..<company.count {
    print(i, company[i], separator: " - ")
}
company.removeLast()

// 定义数组的几种方式
var someIntsA: [Int] = []
// someIntsA.removeLast() error. no element in someIntsA
var someIntsB = [Int]()
var someIntsC = [Int](repeating: 1, count: 10)
var someIntsD: Array<Int> = [1, 2]
var someIntsE: [Int] = [1, 2]
var someIntsF = [1, 2]


someIntsA.append(1)
someIntsB.replaceSubrange(CountableRange<Int>(0..<someIntsB.count), with: [1,3,4])
someIntsC.remove(at: 4)
someIntsC[1...4] = [1, 2, 3, 4, 5, 6]  //实际赋值量可以与下标Range量不等
someIntsD.append(7)
someIntsE += [3, 4, 5]
someIntsF.insert(0, at: 0)
print(someIntsF.removeLast())   // removeLast 会返回删除的元素
someIntsF.remove(at: 1)         // remove(at:) 不会返回
printLine("Set")

// Set 只能存储能提供计算出hash value的类型
str.hashValue
3.1415926.hashValue
2005061325.hashValue
true.hashValue

//var SetA: Set<Int> = []
var SetB = Set<Character>()
var SetC: Set<String> = ["ASM", "C", "C++", "go", "Swift"]
var SetD: Set = ["mov", "pop", "push", "xchg"]  // 可以通过数组类型推断出Set的类型
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

for v in SetC {
    print(v)
}

for (i, v) in SetD.enumerated() {
    print("Iterating Over a Set \(i)\t\(v)")
}

for (i, v) in SetD.sorted().enumerated() {
    print("Iterating Over a Set in Order \(i)\t\(v)")
}

let oddDigits: Set = [1, 3, 5, 7, 9]
let evenDigits: Set = [0, 2, 4, 6, 8]
let singlePrimeDigits: Set<Int> = [2, 3, 5, 7]

// 并
print("Set Union: ", oddDigits.union(evenDigits).sorted())

// 差
print("Set Subtracting: ", oddDigits.subtracting(singlePrimeDigits).sorted())

// 交
print("Set Intersection: ", oddDigits.intersection(singlePrimeDigits).sorted())
    
// 补
print("Set SymmetricDifference: ", oddDigits.symmetricDifference(singlePrimeDigits).sorted())


let houseAnimals: Set = ["🐶", "🐱"]
let farmAnimals: Set = ["🐮", "🐑", "🐶", "🐔", "🐱"]
let cityAnimals: Set = ["🐦", "🐭"]

print(houseAnimals.isSubset(of: farmAnimals))       // 是否是子集
print(houseAnimals.isStrictSubset(of: farmAnimals)) // 是否是真子集
print(farmAnimals.isSuperset(of: houseAnimals))
print(farmAnimals.isDisjoint(with: cityAnimals))    // 是否无交集

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

for key in DictD.keys.sorted() {
    print(key)
}

for value in DictD.values.sorted() {
    print(value)
}

let keys = [Int](DictD.keys)
print(keys)