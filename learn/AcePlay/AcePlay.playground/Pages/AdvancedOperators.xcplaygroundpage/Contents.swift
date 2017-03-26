//: [Previous](@previous)

import Foundation

var str = "Hello, Advanced Operators"

//: [Next](@next)


// 自定义运算符
// 除了实现标准运算符，在 Swift 中还可以声明和实现自定义运算符
// 要指定 prefix、infix 或者 postfix 前缀 中缀 后缀

struct Vector2D {
    var x = 0.0
    var y = 0.0
}


prefix operator +++
infix operator +-: AdditionPrecedence // 此运算符属于 AdditionPrecedence 优先组

extension Vector2D {
    
    static func + (left: inout Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x+right.x, y: left.y+right.y)
    }
    
    static func += (left: inout Vector2D, right: Vector2D) {
        left = left + right
    }

    
    static prefix func +++ (vector: inout Vector2D) -> Vector2D {
        vector += vector
        return vector
    }
    
    static func +- (left: Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x + right.x, y: left.x - right.y)
    }
}


var va = Vector2D(x: 1.0, y: 2.0)
print(+++va)

let firstVector = Vector2D(x: 2.0, y: 3.0)
let secondVector = Vector2D(x: 3.0, y: 4.0)
print(firstVector +- secondVector)



