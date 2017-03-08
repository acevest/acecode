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

var company = ["Tencent", "Apple", "Facebook", "Google", "Twitter", "Amazon"]
var sortedCompany: [String] = []

printLine("Sort")
sortedCompany = company.sorted()
print(sortedCompany)
sortedCompany = []

printLine("Sort With Function A")
func backwardsA(_ a: String, b: String) -> Bool {
    return a > b
}
sortedCompany = company.sorted(by: backwardsA)
print(sortedCompany)
sortedCompany = []

printLine("Sort With Backwards Closure A [Closure Expression Syntax]")
sortedCompany = company.sorted(by: { (a: String, b: String) -> Bool in return a>b })
print(sortedCompany)
sortedCompany = []

// 参数及返回类型自动推断
printLine("Sort With Backwards Closure B [Inferring Type From Context]")
sortedCompany = company.sorted(by: { a, b in return a > b })
print(sortedCompany)
sortedCompany = []

// 隐式返回表达式闭包，省略return
printLine("Sort With Backwards Closure C [Implicit Returns from Single-Expression Closures]")
sortedCompany = company.sorted(by: { a, b in a > b })
print(sortedCompany)
sortedCompany = []

// 简写参数名
printLine("Sort With Backwards Closure D [Shorthand Argument Names]")
sortedCompany = company.sorted(by: { $0 > $1 })
print(sortedCompany)
sortedCompany = []


// 尾随闭包
// 尾随闭包是一个书写在`函数括号之后`的闭包表达式，函数支持将其作为最后一个参数调用
// 在使用尾随闭包时，不用写出它的参数标签

printLine("Trailing Closures")
sortedCompany = company.sorted() { $0 > $1}
print(sortedCompany)
sortedCompany = []

// 如果闭包表达式是函数或方法的唯一参数，在使用尾随闭包时，可以把`()`省掉
sortedCompany = company.sorted { $0 > $1 }
print(sortedCompany)
sortedCompany = []


/*
 There’s actually an even shorter way to write the closure expression above. Swift’s String type defines its string-specific implementation of the greater-than operator (>) as a function that has two parameters of type String, and returns a value of type Bool. This exactly matches the function type needed by the sort(_:) method. Therefore, you can simply pass in the greater-than operator, and Swift will infer that you want to use its string-specific implementation:
 */
printLine("Sort With Backwards Closure E [Operator Functions]")
sortedCompany = company.sorted(by: >)
print(sortedCompany)
sortedCompany = []

// Trailing Closure
printLine("Sort With Backwards Closure F [Trailing Closure]")
sortedCompany = company.sorted() { a, b in a > b} // 如果闭包参数是这个函数的最后一个参数，是可以采用尾随闭包写法
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
func makeIncrementer(_ step:Int) -> () -> Int {
    var total = 0
    func inc() -> Int {
        total += step
        return total
    }
    
    return inc
}

// 闭包是引用类型
let closureFuncA = makeIncrementer(2)
print("ClosureFuncA:", closureFuncA())
print("ClosureFuncA:", closureFuncA())
let closureFuncB = closureFuncA
print("ClosureFunnB:", closureFuncB())
let closureFuncC = makeIncrementer(1)
print("ClosureFuncC:", closureFuncC())


// 逃逸&非逃逸闭包
// 当一个闭包作为参数传到一个函数中，但是这个闭包在函数返回之后才被执行，则称该闭包从函数中逃逸
// 可以在定义参数时，在参数名前标注@escaping来指明这个闭包是允许逃逸出这个函数的

printLine("Noescaping & Escaping Closesure")
func noescapingClosure(_ closure: () -> Void) {
    closure()
}

var closureHandler: Array<() -> Void> = []
func escapingClosure(_ closure:  @escaping () -> Void) {  // 此时参数前加@noescape会报错
    closureHandler.append(closure)
}


class ClosureClass {
    var x = 10
    func doSomethingAboutEscape() {
        noescapingClosure() { x = 200 }     // 将参数标记为@noescape能在闭包中隐式地引用self
        escapingClosure() { self.x = 100 }  // 将一个闭包参数标记为@escaping意味着必须在闭包中显式地引用self
    }
}

var closureInstance = ClosureClass()
closureInstance.doSomethingAboutEscape()
print(closureInstance.x)

closureHandler[0]()         // 两种调用逃逸闭包的方法
closureHandler.first?()
print(closureInstance.x)


// 自动闭包
printLine("AutoClosure")
print("Now Company Items:", company)
print("Company Item Count:", company.count)
// autoClosureHanlerA的type是 () -> String 不是 String
let autoClosureHandlerA = { company.remove(at: 0) }  // an autoclosure lets you delay evaluation
print("Company Item Count:", company.count) // 在自动闭包被调用前，值不会变
print("No Remove \(autoClosureHandlerA())")
print("Company Item Count:", company.count)


// autoclosure parameter
printLine("AutoClosure Parameter")
func autoClosureFuncParameterA(_ closure: () -> String) {
    print("AutoClosureFuncParameterA \(closure())!")
}
autoClosureFuncParameterA({ company.remove(at: 0) })

func autoClosureFuncParameterB(_ closure: @autoclosure () -> String) {
    print("AutoClosureFuncParameterB \(closure())!")
}

// 用@autoclosure修饰参数 可以在调用的时候少写一对`{}`
// 过度使用@autoclosure会让代码变得难以理解
autoClosureFuncParameterB(company.remove(at: 0))

// @autoclosure 暗含了 noescape 特性
var autoClosureHanlder: [() -> String] = []
func autoClosureFuncParameterC(_ closure: @autoclosure () -> String) {
    //因为参数被@autoclosure修饰了，而@autoclosure暗含@noescape特性，因此以下语句会报错
    //autoClosureHanlder.append(closure)
}

// 如果用了@autoclosure又要用escape特性，则用@autoclosure(escaping)修饰参数
func autoClosureFuncParameterD( _ closure: @autoclosure @escaping () ->String) {
    print("Called autoClosureFuncParameterD")
    autoClosureHanlder.append(closure)
}
autoClosureFuncParameterD(company.remove(at: 0))
autoClosureFuncParameterD(company.remove(at: 0))

for handler in autoClosureHanlder {
    print("autoClosure Handling \(handler())!")
}
