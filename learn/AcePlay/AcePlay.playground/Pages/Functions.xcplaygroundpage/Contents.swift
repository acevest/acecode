//: [Previous](@previous)

import Foundation


func Hello() -> Void {  // func Hello() -> () { }
    print("Hello Swift World")
}

func greetFunc(person: String) -> String {
    let greeting = "Hello \(person)!"
    return greeting
}


printLine("Functions")

Hello()
print(greetFunc(person: "Ace"))
print(greetFunc(person: "AceVest"))

printLine("Multiple Return Types")  // 多重返回

func minMax(_ data:Array<Int>) -> (min:Int, max:Int)? {
    guard data.count > 0 else {
        return nil
    }
    
    var min = data[0]
    var max = data[0]
    
    for i in 1..<data.count {
        min = min > data[i] ? data[i] : min
        max = max < data[i] ? data[i] : max
    }
    
    return (min, max)
}

var Data: Array<Int> = [3, 8, 4, 1, 0, -2, 9, 6, 7]

if let ret = minMax(Data) {
    print("Min:", ret.min, " Max:", ret.max)
}


// 参数标签
// 每个参数都有一个参数标签(argument label)和一个参数名称(parameter name)
// 参数标签在调用函数的时候使用，调用的时候需要把函数的参数标签写在参数的前面
// 参数名称在实现函数的时候使用
// 参数标签要在参数名称前指定，中间以空格分隔
// 如果一个参数有一个标签，那么在调用的时候必须使用标签来标记这个参数
func greetFuncV2(person: String, from hometown: String) -> Void {
    print("Hello \(person), Glad you could visit from \(hometown).")
}

greetFuncV2(person: "Ace", from: "China")


// 忽略参数标签
func greetFuncV3(_ person: String) -> Void {
    print("Hello \(person)")
}

greetFuncV3("Ace")  // 不用在参数列表里写上'person:"Ace"'

// 默认参数值
func greetFuncV4(_ person: String, from hometown:String = "China") {
    print("Hello \(person), Glad you could visit from \(hometown).")
}

greetFuncV4("Ace")
greetFuncV4("Obama", from: "USA")

// 可变参数
// 一个函数最多只能拥有一个可变参数
func Sum(_ numbers: Int...) -> Int {
    var s = 0;
    for n in numbers {
        s += n
    }

    return s
}

print(Sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))

// 外部参数包能相同, 但内部参数名不能相同
func sameExternalParameterNames( ExName a: Int, ExName b: Int) -> Int {
    return max(a, b)
}
print(sameExternalParameterNames(ExName: 10, ExName: 20))

// 引用传参
func swapTwoInts(_ a: inout Int, _ b: inout Int) -> Void {
    let t: Int = a
    a = b
    b = t
}

var IntA = 10
var IntB = 20
swapTwoInts(&IntA, &IntB)
print("IntA: \(IntA) IntB: \(IntB)")


