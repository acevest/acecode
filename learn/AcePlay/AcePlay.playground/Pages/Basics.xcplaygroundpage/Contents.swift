//: Playground - noun: a place where people can play

import UIKit

// String values can be constructed by passing an array of Character values
let catCharacters: [Character] = ["C", "a", "t", " ", "猫"]
let catString = String(catCharacters)
print(catString)

// Character 加到String的方法
var welcome = "Hello World"
let exclamationMark: Character = "!"
welcome.append(exclamationMark)
print(welcome)

// ############# Type Alias ################
typealias AudioSample = UInt

let maxAmplitudeFound = AudioSample.max


// ############# Tuple ################
let http404Error = (404, "Page Not Found")
let (httpRetCode, _) = http404Error
print("Http RetCode \(httpRetCode) Error Message \(http404Error.1)")

let httpStatus = (statusCode: 200, description: "OK")
print("Http RetCode \(httpStatus.statusCode) Message \(httpStatus.description)")


// ############# Optionals ################
let possibleNumber = "123"
let convertNumber : Int? = Int(possibleNumber) // of type Int?

if convertNumber != nil {
    print("ConvertNumber is \(convertNumber)")
    print("ConvertNumber is \(convertNumber!)")
} else {
    print("ConvertNumber is nil")
}

// ############# Optionals Binding ################
if let actualNumber = Int(possibleNumber) {
    print("\"\(possibleNumber)\" has an integer of \(actualNumber)")
} else {
    print("\"\(possibleNumber)\" could not to be converted to an integer")
}

if let firstNumber = Int("4"), let secondNumber = Int("42"), firstNumber < secondNumber && secondNumber < 100 {
    print("\(firstNumber) < \(secondNumber) < 100")
}

// ############# Implicitly Unwrapped Optionals ################
let possibleString: String? = "An Optional String"
let forcedString: String = possibleString!

let assumedString: String! = "An Implicitly Unwrapped Optional String"
let implicitString: String = assumedString

print("\(possibleString!) \(forcedString) \(assumedString) \(implicitString)")

// ############# Nil-Coalescing Operator ################
let defaultColorName = "yellow"
var userDefinedColorName: String?
// 等价于 userDefinedColorName == nil ? defaultColorName : userDefinedColorName
var colorNameToUse = userDefinedColorName ?? defaultColorName
print(colorNameToUse)

userDefinedColorName = "red"
colorNameToUse = userDefinedColorName ?? defaultColorName
print(colorNameToUse)

// ############# Nil-Coalescing Operator ################
for index in 1...5 {
    print("Closed Range Operator \(index) of [1,5]")
}

for index in 0..<5 {
    print("Half-Open Range Operator \(index) of [0,5)")
}

var word = "cafe"
print("the number of characters of \(word) is \(word.characters.count)");
word += "\u{301}"
print("the number of characters of \(word) is \(word.characters.count)");


let str = "Hello, playground.小狗:🐶 锤子:🔨"
// Index
var strInx:String.Index = str.startIndex
str.index(after: strInx)
print(str[strInx])
for strInx in str.characters.indices {
    print("\(str[strInx])", terminator: "")
}
print()

// utf8 编码格式
for c in str.utf8 {
    print(c, terminator: "-")
}
print()

// unicode
for c in str.unicodeScalars {
    print("\(c)\t\(c.value)")
}

welcome.insert("~", at: welcome.endIndex)
print(welcome)
// contentsOf 是一个 Collection 所以要加 .characters
welcome.insert(contentsOf: " Hello Swift".characters, at: welcome.index(before: welcome.endIndex))
print(welcome)

welcome.remove(at: welcome.index(before: welcome.endIndex))
print(welcome)

let range = welcome.index(welcome.endIndex, offsetBy: -12)..<welcome.endIndex
welcome.removeSubrange(range)
print(welcome)



// ############# Working with Characters ################
for c in str.characters {
    print(c, terminator: "")
}
print()

print("The String is: \(str)")


// Print separator & terminator
var company:Array<String> = [ "Apple", "Google", "Facebook", "Tencent" ]
print(company[0], company[1], company[2], company[3], separator: "#", terminator: " $$$$$\n")

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

var someIntsA: [Int] = []
var someIntsB = [Int]()
var someIntsC = [Int](repeating: 1, count: 10)
someIntsA.append(1)
someIntsB.replaceSubrange(CountableRange<Int>(0..<someIntsB.count), with: [1,3,4])
someIntsC.remove(at: 4)
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

for v in SetC.sorted() {
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

for key in DictD.keys.sorted() {
    print(key)
}

for value in DictD.values.sorted() {
    print(value)
}

let keys = [Int](DictD.keys)
print(keys)