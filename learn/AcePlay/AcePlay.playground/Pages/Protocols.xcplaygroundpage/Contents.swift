//: [Previous](@previous)

import Foundation

var str = "Hello, Protocols"

//: [Next](@next)

//协议语法
//协议的定义方式与类、结构体和枚举的定义非常相似：
//
//protocol SomeProtocol {
//    // 这里是协议的定义部分
//}
//要让自定义类型遵循某个协议，在定义类型时，需要在类型名称后加上协议名称，中间以冒号（:）分隔。遵循多个协议时，各协议之间用逗号（,）分隔：
//
//struct SomeStructure: FirstProtocol, AnotherProtocol {
//    // 这里是结构体的定义部分
//}
//拥有父类的类在遵循协议时，应该将父类名放在协议名之前，以逗号分隔：
//
//class SomeClass: SomeSuperClass, FirstProtocol, AnotherProtocol {
//    // 这里是类的定义部分
//}


//协议可以要求遵循协议的类型提供特定名称和类型的实例属性或类型属性。协议不指定属性是存储型属性还是计算型属性，它只指定属性的名称和类型。此外，协议还指定属性是可读的还是可读可写的。
//
//如果协议要求属性是可读可写的，那么该属性不能是常量属性或只读的计算型属性。如果协议只要求属性是可读的，那么该属性不仅可以是可读的，如果代码需要的话，还可以是可写的。
//
//协议总是用 var 关键字来声明变量属性，在类型声明后加上 { set get } 来表示属性是可读可写的，可读属性则用 { get } 来表示：
//
//protocol SomeProtocol {
//    var mustBeSettable: Int { get set }
//    var doesNotNeedToBeSettable: Int { get }
//}
//在协议中定义类型属性时，总是使用 static 关键字作为前缀。当类类型遵循协议时，除了 static 关键字，还可以使用 class 关键字来声明类型属性：
//
//protocol AnotherProtocol {
//    static var someTypeProperty: Int { get set }
//}



protocol FullNamed {
    var fullName: String { get }
}

struct Person: FullNamed {
    var fullName: String
}

let john = Person(fullName: "John")


class Starship: FullNamed {
    var name: String
    var prefix: String?
    
    init(name: String, prefix: String? = nil) {
        self.name = name
        self.prefix = prefix
    }
    
    var fullName: String {
        return "\(prefix ?? "") \(name)"
    }
}

var ncc1701 = Starship(name: "Enterprise", prefix: "USS")
print(ncc1701.fullName)




// 方法要求
// 协议可以要求遵循协议的类型实现某些指定的实例方法或类方法。这些方法作为协议的一部分，像普通方法一样放在协议的定义中，但是不需要大括号和方法体。
// 可以在协议中定义具有可变参数的方法，和普通方法的定义方式相同。但是，不支持为协议中的方法的参数提供默认值。


//正如属性要求中所述，在协议中定义类方法的时候，总是使用 static 关键字作为前缀。当类类型遵循协议时，除了 static 关键字，还可以使用 class 关键字作为前缀：
//
//protocol SomeProtocol {
//    static func someTypeMethod()
//}


protocol RandomNumberGenerator {
    func random() -> Double
}


class LinearCongruentialGenerator: RandomNumberGenerator {
    var lastRandom = 42.0
    let m = 139968.0
    let a = 3877.0
    let c = 29573.0
    
    func random() -> Double {
        lastRandom = ((lastRandom * a + c).truncatingRemainder(dividingBy:m))
        return lastRandom / m
    }
}

let generator = LinearCongruentialGenerator()
print("Here is a random number: \(generator.random())")
print("Here is another random number: \(generator.random())")

