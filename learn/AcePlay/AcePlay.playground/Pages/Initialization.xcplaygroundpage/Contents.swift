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

// 每一个类都必须拥有至少一个指定构造器
// 应当只在必要的时候为类提供便利构造器

// 指定构造器语法
// init(parameters) {
//      statements
// }

// 便利构造器语法
// convenience init(parameters) {
//      statements
// }


// 构造器之间的代理规则
// 1. 指定构造器必须调用其直接父类的的指定构造器
// 2. 便利构造器必须调用同类中定义的其它构造器
// 3. 便利构造器必须最终导致一个指定构造器被调用


// 换种说法
// 1. 指定构造器必须总是向上代理
// 2. 便利构造器必须总是横向代理



//
// 两段式构造安全检查
//
// 需要注意`初始化` 和 `赋新值`之间的细微差别
// 1. 指定构造器必须保证它所在类引入的所有属性都必须先`初始化`完成
// 2. 指定构造器必须先向上代理调用父类构造器，然后再为继承的属性`赋新值`
// 3. 便利构造器必须先代理调用同一类中的其它构造器，然后再为任意属性赋新值
// 4. 构造器在第一阶段构造完成之前，不能调用任何实例方法，不能读取任何实例属性的值，不能引用self作为一个值


//
// 阶段 1
//
// 某个指定构造器或便利构造器被调用。
// 完成新实例内存的分配，但此时内存还没有被初始化。
// 指定构造器确保其所在类引入的所有存储型属性都已赋初值。存储型属性所属的内存完成初始化。
// 指定构造器将调用父类的构造器，完成父类属性的初始化。
// 这个调用父类构造器的过程沿着构造器链一直往上执行，直到到达构造器链的最顶部。
// 当到达了构造器链最顶部，且已确保所有实例包含的存储型属性都已经赋值，这个实例的内存被认为已经完全初始化。此时阶段 1 完成。

//
// 阶段 2
//
// 从顶部构造器链一直往下，每个构造器链中类的指定构造器都有机会进一步定制实例。构造器此时可以访问self、修改它的属性并调用实例方法等等。
// 最终，任意构造器链中的便利构造器可以有机会定制实例和使用self



// Swift 中的子类默认情况下不会继承父类的构造器
// 父类的构造器仅会在安全和适当的情况下被继承
// 在编写一个和父类中指定构造器相匹配的子类构造器时，实际上是在重写父类的这个指定构造器。因此必须在定义子类构造器时带上override修饰符
// 如果编写了一个和父类便利构造器相匹配的子类构造器，由于子类不能直接调用父类的便利构造器，因此并不算子类重写父类构造器。所以不需要加override前缀



// Vehicle 只为存储属性提供默认值，而不自定义构造器
// 因此它会自动获得一个默认构造器
class Vehicle {
    var numberOfWheels = 0
    var description: String {
        return "\(numberOfWheels) wheel(s)"
    }
}

let someVehicle = Vehicle()
print("SomeVehicle: \(someVehicle.description)")

class Bicycle: Vehicle {
    override init() {   // 重写默认构造器
        
        super.init()    // 调用父类默认构造器
        
        numberOfWheels = 2  // 赋新值
    }
}

let someBicycle = Bicycle()
print("SomeBicycel: \(someBicycle.description)")





// 构造器的自动继承
// 规则1: 如果子类没有定义任何`指定构造器`，它将自动继承所有父类的指定构造器。
// 规则2: 如果子类提供了所有父类指定构造器的实现——无论是通过规则1继承过来的，还是提供了自定义实现——它将自动继承所有父类的`便利构造器`
// 注意: 
// 1. 即使你在子类中添加了更多的便利构造器，这两条规则仍然适用。
// 2. 对于规则2，子类可以将父类的指定构造器实现为便利构造器。



class Food {
    var name: String

    // 指定构造器
    init(name: String) {
        self.name = name
    }
    
    // 便利构造器
    convenience init() {
        self.init(name: "[Unnamed]")
    }
}


let namedMeat = Food(name: "Bacon")


class RecipeIngredient: Food {    // 食谱 材料 <==> 食材
    var quantity: Int
    
    init(name: String, quantity: Int) {
        self.quantity = quantity
        
        super.init(name: name)
    }
    
    // 重写父类的指定构造器，可以改写成便利构造器
    override convenience init(name: String) {
        
        // 便利构造器只允许调用本类的构造器
        self.init(name: name, quantity: 1)
    }
    
    
    // 由于RecipeIngredient类实现了父类Food的所有指定构造器
    // 因此它自动继承了父类Food的所有便利构造器
    // 在这个例子中是继承了
    //    convenience init() {
    //        self.init(name: "[Unnamed]")
    //    }
    // 只不过继承的这个便利构造器代理的不是Food，而是RecipeIngredient这个类
    // 因此self指的不是Food而是RecipeIngredient
    
    var description: String {
        return "RecipeIngredient: \(self.name) x \(self.quantity)"
    }
}

// 因此有三种方式创建RecipeIngredient的实例

// 1. 调用将父类指定构造器重写为便利构造器的构造器
let oneBacon = RecipeIngredient(name: "Bacon")
print("OneBacon: \(oneBacon.description)")

// 2. 调用新写的指定构造器
let sixEggs = RecipeIngredient(name: "Egg", quantity: 6)
print("SixEggs: \(sixEggs.description)")

// 3. 调用继承自父类的便利构造器
//    需要注意的是此时的构造器代理的不是父类而是当前类
let oneMysterItem = RecipeIngredient()
print("OneMysterItem: \(oneMysterItem.description)")
