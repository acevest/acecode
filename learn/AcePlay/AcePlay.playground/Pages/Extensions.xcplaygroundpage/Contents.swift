//: [Previous](@previous)

import Foundation

var str = "Hello, Extensions"

//: [Next](@next)


// 扩展 就是为一个已有的类、结构体、枚举类型或者协议类型添加新功能。这包括在没有权限获取原始源代码的情况下扩展类型的能力

// Swift 中的扩展可以:
// 1. 添加计算型属性和计算型类型属性
// 2. 定义实例方法和类型方法
// 3. 提供新的构造器
// 4. 定义下标
// 5. 定义和使用新的嵌套类型
// 6. 使一个已有类型符合某个协议


// 在 Swift 中，你甚至可以对协议进行扩展，提供协议要求的实现，或者添加额外的功能，从而可以让符合协议的类型拥有这些功能
// 注意:扩展可以为一个类型添加新的功能，但是不能重写已有的功能。

// 语法
//
//extension SomeType {
//    somecode
//}

//
//可以通过扩展来扩展一个已有类型，使其采纳一个或多个协议。在这种情况下，无论是类还是结构体，协议名字的书写方式完全一样：
//
//extension SomeType: SomeProtocol, AnotherProctocol {
//    // 协议实现写到这里
//}

// 注意: 如果你通过扩展为一个已有类型添加新功能，那么新功能对该类型的所有已有实例都是可用的，即使它们是在这个扩展定义之前创建的



// 扩展计算型属性
// 转换成米
extension Double {
    var km: Double { return self*1000 }
    var m:  Double { return self }
    var cm: Double { return self/100 }
    var ft: Double { return self/3.28084 }
}

var tenThousandFeet = 10_000.ft
print("Ten thousand feets is \(tenThousandFeet) meters")

let aMarathon = 42.km + 195.m
print("a marathon is \(aMarathon) meters long")


// 注意: 扩展可以添加新的计算型属性，但是不可以添加存储型属性，也不可以为已有属性添加属性观察器



// 扩展构造器
// 扩展能为类添加新的便利构造器，但是它们不能为类添加新的指定构造器或析构器。指定构造器和析构器必须总是由原始的类实现来提供
// 如果使用扩展为一个值类型添加构造器，同时该值类型的原始实现中未定义任何定制的构造器且所有存储属性提供了默认值，那么就可以在扩展中的构造器里调用默认构造器和逐一成员构造器。
struct Size {
    var width: Double = 0.0
    var height: Double = 0.0
}

struct Point {
    var x: Double = 0.0
    var y: Double = 0.0
}


struct Rect {
    var origin = Point()
    var size = Size()
}


var defaultRect = Rect()
var originRect = Rect(origin: Point(x: 2.0, y:2.0), size: Size(width: 5.0, height: 5.0))


// 可以为Rect扩展一个指定中心点和Size的构造器
extension Rect {
    init(center: Point, size: Size) {
        let originX = center.x - size.width / 2
        let originY = center.y - size.height / 2
        self.init(origin: Point(x: originX, y: originY), size: size)
    }
}

var centerRect = Rect(center: Point(x: 0.0, y: 0.0), size: Size(width: 5.0, height: 5.0))


// 扩展方法

extension Int {
    func repeatTask(task: (Int) -> Void) {
        for i in 0..<self {
            task(i)
        }
    }
}

func testTask(index: Int) {
    print("it's task[\(index)]'s turn")
}

5.repeatTask(task: testTask)

// 闭包方法
3.repeatTask { index in print("IT'S TASK[\(index)]'s TURN") }

// 扩展可变实例方法
extension Int {
    mutating func square() -> Int {
        self = self * self
        return self
    }
}

var someInt = 3
print(someInt.square())
print(someInt)


// 扩展下标
extension Int {
    subscript(index: Int) -> Int {
        
        var base = 1
        
        for _ in 1..<index {
            base *= 10
        }
        
        return (self / base) % 10
    }
}

print(123456[5])
print(31415926[1])


// 扩展嵌套类型
extension Int {
    enum Kind: String {
        case Negative
        case Zero
        case Positive
    }
    
    var kind: Kind {
        switch self {
        case let x where x > 0:
            return .Positive
        case Int.min..<0 :
            return .Negative
        default:
            return .Zero
        }
    }
}


func printIntegerKinds(_ numbers: [Int]) {
    for n in numbers {
        var s: String = ""
        switch n.kind {
        case .Negative:
            s += "-"
        case .Zero:
            s += " "
        case .Positive:
            s += "+"
        }
        
        s += "\(n.kind)"
        
        print(s)
    }
}


var numbers: [Int] = [1, 2, 3, -1, 0, -8]
printIntegerKinds(numbers)