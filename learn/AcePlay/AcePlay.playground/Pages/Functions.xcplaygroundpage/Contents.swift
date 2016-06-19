//: [Previous](@previous)

import Foundation


func Hello() -> Void {  // func Hello() -> () { }
    print("Hello Swift World")
}


printLine("Functions")

Hello()

printLine("Multiple Return Types")

func minMax(data:Array<Int>) -> (min:Int, max:Int)? {
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

// 外部参数包能相同, 但内部参数名不能相同
func sameExternalParameterNames( ExName a: Int, ExName b: Int) -> Int {
    return max(a, b)
}
print(sameExternalParameterNames(ExName: 10, ExName: 20))

// 引用传参
func swapTwoInts(inout a: Int, inout _ b: Int) -> Void {
    let t: Int = a
    a = b
    b = t
}

var IntA = 10
var IntB = 20
swapTwoInts(&IntA, &IntB)


