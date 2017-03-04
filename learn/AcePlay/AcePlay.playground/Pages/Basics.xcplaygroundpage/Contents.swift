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


