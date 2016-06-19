//: [Previous](@previous)

import UIKit


//
//闭包采取如下三种形式之一:
//  1. 全局函数是一个有名字但不会捕获任何值的闭包
//  2. 嵌套函数是一个有名字并可以捕获其封闭函数域内值的闭包
//  3. 闭包表达式是一个利用轻量级语法所写的可以捕获其上下文中变量或常量值的匿名闭包
//

//
//Swift闭包语法特点:
//  1. 利用上下文推断参数和返回值类型
//  2. 隐式返回单表达式闭包，即单表达式闭包可以省略return关键字
//  3. 参数名称缩写
//  4. 尾随（Trailing）闭包语法
//


/*
 The sort(_:) method accepts a closure that takes two arguments of the same type as the array’s contents, and returns a Bool value to say whether the first value should appear before or after the second value once the values are sorted. The sorting closure needs to return true if the first value should appear before the second value, and false otherwise.

 */

let company = ["Tencent", "Apple", "Facebook", "Google", "Twitter", "Amazon"]
var sortedCompany: [String] = []

printLine("Sort")
sortedCompany = company.sort()
print(sortedCompany)
sortedCompany = []

printLine("Sort With Function A")
func backwardsA(a: String, b: String) -> Bool {
    return a > b
}
sortedCompany = company.sort(backwardsA)
print(sortedCompany)
sortedCompany = []

printLine("Sort With Backwards Closure A [Closure Expression Syntax]")
sortedCompany = company.sort({ (a: String, b: String) -> Bool in return a>b })
print(sortedCompany)
sortedCompany = []

// 参数及返回类型自动推断
printLine("Sort With Backwards Closure B [Inferring Type From Context]")
sortedCompany = company.sort({ a, b in return a > b })
print(sortedCompany)
sortedCompany = []

// 隐式返回表达式闭包，省略return
printLine("Sort With Backwards Closure C [Implicit Returns from Single-Expression Closures]")
sortedCompany = company.sort({ a, b in a > b })
print(sortedCompany)
sortedCompany = []

// 简写参数名
printLine("Sort With Backwards Closure D [Shorthand Argument Names]")
sortedCompany = company.sort({ $0 > $1 })
print(sortedCompany)
sortedCompany = []

/*
 There’s actually an even shorter way to write the closure expression above. Swift’s String type defines its string-specific implementation of the greater-than operator (>) as a function that has two parameters of type String, and returns a value of type Bool. This exactly matches the function type needed by the sort(_:) method. Therefore, you can simply pass in the greater-than operator, and Swift will infer that you want to use its string-specific implementation:
 */
printLine("Sort With Backwards Closure E [Operator Functions]")
sortedCompany = company.sort(>)
print(sortedCompany)
sortedCompany = []

// Trailing Closure
printLine("Sort With Backwards Closure F [Trailing Closure]")
sortedCompany = company.sort() { a, b in a > b} // 如果闭包参数是这个函数的最后一个参数，是可以采用尾随闭包写法
//sortedCompany = company.sort { a, b in a > b} // 如果闭包参数是这个函数的唯一一个参数，是可以不用写括号的
print(sortedCompany)
sortedCompany = []


let digitNames = [
    0: "零",
    1: "壹",
    2: "贰",
    3: "叁",
    4: "肆",
    5: "伍",
    6: "陆",
    7: "柒",
    8: "捌",
    9: "玖",
]
let numbers = [9876543210, 1413, 110, 64]
// map函数可能不用指定参数类型，但要指定返回值类型
let digitString = numbers.map() {
    (digit) -> String in
    var n = digit   // 参数digit不能在函数体内被修改
    var s = ""
    while n > 0 {
        s = digitNames[n % 10]! + s
        n /= 10
    }
    return s
}

print(digitString)


printLine("Captuare Value")

// 捕获值
func makeIncrementer(step:Int) -> () -> Int {
    var total = 0
    func inc() -> Int {
        total += step
        return total
    }
    
    return inc
}

var closureFuncA = makeIncrementer(1)
print("ClosureFuncA:", closureFuncA())
print("ClosureFuncA:", closureFuncA())
var closureFuncB = closureFuncA
print("ClosureFunnB:", closureFuncB())
var closureFuncC = makeIncrementer(1)
print("ClosureFuncC:", closureFuncC())

