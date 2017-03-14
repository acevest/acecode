//: [Previous](@previous)

import Foundation

var str = "Hello, Initialization"

//: [Next](@next)

// 构造过程

// 可以在构造器中为存储型属性赋初值，也可以在定义属性时为其设置默认值
// 为存储型属性设置默认值或者在构造器中为其赋值时，它们的值是被直接设置的，不会触发任何属性观察者

struct Fahrenheit {
    var temperature: Double
    init() {
        temperature = 32.0
    }
}

// 与下述定义方式等价
// struct Fahrenheit {
//      var temperature = 32.0
// }

var f = Fahrenheit()
print("The default temperature is \(f.temperature)° Fahrenheit")


// 构造参数
struct Celsius {
    var temperatureInCelsius: Double
    init(fromFahrenheit fahrenheit: Double) {
        temperatureInCelsius = (fahrenheit - 32.0) / 1.8
    }
    
    init(fromKelvin kelvin: Double) {
        temperatureInCelsius = kelvin - 273.15
    }
    
    init(_ celsius: Double) {
        temperatureInCelsius = celsius
    }
}

let bollingPointOfWather  = Celsius(fromFahrenheit: 212.0)
let freezingPointOfWather = Celsius(fromKelvin: 273.15)


// 构造器并不像函数和方法那样在括号前有一个可辨别的名字
// 因此在调用构造器时，主要通过构造器中的参数名和类型来确定应该被调用的构造器
// 正因为参数如此重要，如果你在定义构造器时没有提供参数的外部名字，Swift会为构造器的每个参数自动生成一个跟内部名字相同的外部名

struct Color {
    var red, green, blue: Double
    
    init(red: Double, green: Double, blue: Double) {
        self.red = red
        self.green = green
        self.blue = blue
    }
    
    init(white: Double) {
        red   = white
        green = white
        blue  = white
    }
}

let magenta  = Color(red: 1.0, green: 0.0, blue: 1.0)
let halfGray = Color(white: 0.5)


// 如果不通过外部参数名字传值，你是没法调用这个构造器的
// 只要构造器定义了某个外部参数名，你就必须使用它，忽略它将导致编译错误
// let green = Color(0.0, 1.0, 0.0) 这段代码会报编译时错误，需要外部名称
let bodyTemperature = Celsius(37.2)

// 常量属性的修改&可选属性类型
class SureyQuestion {
    let text: String
    var response: String?
    
    init(text: String) {
        // 可以在构造过程中的任意时间点给常量属性指定一个值
        // 一旦常量属性被赋值，它将永远不可更改
        // 对于类的实例来说，它的常量属性只能在定义它的类的构造过程中修改；不能在子类中修改
        self.text = text
    }
    
    func ask() {
        print(text)
    }
}


let beetsQuestion = SureyQuestion(text: "How about beets?")
beetsQuestion.ask()
beetsQuestion.response = "I also like beets. (But not with cheese.)"


// 默认构造器
// 如果结构体或类的所有属性都有默认值，同时没有自定义的构造器，那么 Swift 会给这些结构体或类提供一个默认构造器（default initializers）
class ShoppingListItem {
    // name 默认为 nil
    var name: String?
    
    // quantity 默认为 1
    var quantity = 1
    
    // purchased 默认为 false
    var purchased = false
}

var someShoppingListItem = ShoppingListItem()


// 结构体的逐一成员构造器
// 除了上面提到的默认构造器，如果结构体没有提供自定义的构造器，它们将自动获得一个逐一成员构造器，即使结构体的存储型属性没有默认值
struct Size {
    var width  = 0.0
    var height = 0.0
}

let size0 = Size()  // 默认构造器
let size1 = Size(width: 2.3, height: 3.7) // 逐一构造器


// 构造器代理
// 构造器代理的实现规则和形式在值类型和类类型中有所不同

// 值类型（结构体和枚举类型）的构造器代理不支持继承，所以构造器代理的过程相对简单
// 对于值类型，可以使用self.init在自定义的构造器中引用相同类型中的其它构造器。并且只能在构造器内部调用self.init
// 如果为某个值类型定义了一个自定义的构造器，将无法访问到默认构造器（如果是结构体，还将无法访问逐一成员构造器）
// 如果希望默认构造器、逐一成员构造器以及你自己的自定义构造器都能用来创建实例
// 可以将自定义的构造器写到扩展（extension）中，而不是写在值类型的原始定义中

struct Point {
    var x = 0.0, y = 0.0
}

struct Rect {
    var origin = Point()
    var size = Size()
    
    init() { }
    
    init(origin: Point, size: Size) {
        self.origin = origin
        self.size   = size
    }
    
    init(center: Point, size: Size) {
        let originX = center.x - size.width / 2
        let originY = center.y - size.height / 2
        
        self.init(origin: Point(x: originX, y: originY), size: size)
    }
    
    var description: String {
        return "LeftBottom(\(origin.x), \(origin.y)) RightTop(\(origin.x+size.width), \(origin.y+size.height))"
    }
}

let basicRect = Rect()
let originRect = Rect(origin: Point(x: 2.0, y: 2.0), size: Size(width: 100, height: 200))
let centerRect = Rect(center: Point(x: 50, y: 50), size: Size(width: 50, height: 50))

print("BasicRect: \(basicRect.description)")
print("OriginRect: \(originRect.description)")
print("CenterRect: \(centerRect.description)")


// 类的继承和构造过程


