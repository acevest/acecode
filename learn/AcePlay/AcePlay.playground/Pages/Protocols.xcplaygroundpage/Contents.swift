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




// 类类型专属协议
protocol SomeClassOnlyProtocol: class {
    func haha() -> String
}

class HahaClass: SomeClassOnlyProtocol {
    func haha() -> String {
        return "Haha Class"
    }
}
// 只能Class继承
//struct HahaStruct : SomeClassOnlyProtocol {
//    func haha() -> String {
//        return "Haha Struct"
//    }
//}

let h = HahaClass()
print(h.haha())



// 协议合成
// 有时候需要同时遵循多个协议，以将多个协议采用 SomeProtocol & AnotherProtocol 这样的格式进行组合
protocol Named {
    var name: String { get }
}

protocol Aged {
    var age: Int { get }
}

struct SomeOne: Named, Aged {
    var name: String
    var age: Int
}


func wishHappyBirthday(to celebrator: Named & Aged) {
    print("Happy Birthday, \(celebrator.name), you're \(celebrator.age)")
}
wishHappyBirthday(to: SomeOne(name: "Ace", age: 18))


// 检查协议一致性
protocol Area {
    var area: Double { get }
}

class Circle: Area {
    var radius: Double
    let pi = 3.1415927
    var area: Double {
        get {
            return pi*radius*radius
        }
    }
    
    init(radius: Double) {self.radius = radius }
}


class Country: Area {
    var area: Double
    init(area: Double) { self.area = area }
}

class Animal {
    var legs: Int
    init(legs: Int) { self.legs = legs }
}

let objects: [AnyObject] = [
    Circle(radius: 45),
    Country(area: 960),
    Animal(legs: 4)
]

for o in objects {
    if let oa = o as? Area {
        print("Area is \(oa.area)")
    } else {
        print("Something that does not have area")
    }
}



// 协议扩展
// 协议可以通过扩展来为遵循协议的类型提供属性、方法以及下标的实现。通过这种方式，可以基于协议本身来实现这些功能，而无需在每个遵循协议的类型中都重复同样的实现，也无需使用全局函数。
extension RandomNumberGenerator {
    func randomBool() -> Bool {
        return random() > 0.5
    }
}

let generator1 = LinearCongruentialGenerator()
print(generator1.randomBool())

// Mutating 方法要求
// 实现协议中的 mutating 方法时，若是类类型，则不用写 mutating 关键字。而对于结构体和枚举，则必须写 mutating 关键字。

protocol Togglable {
    mutating func toggle()
}


enum OnOffSwitch: String, Togglable {
    case On
    case Off
    
    mutating func toggle() {
        switch self {
        case .Off:
            self = .On
        case .On:
            self = .Off
        }
    }
}


var lightSwith = OnOffSwitch.Off
lightSwith.toggle()
print(lightSwith)


// 构造器要求
// 协议可以要求遵循协议的类型实现指定的构造器
// 在协议的定义里写构造器的声明不需要写花括号和构造器的实体

protocol SomeProtocol {
    init(someParameter: Int)
}

// 在遵循协议的类中实现构造器，无论是作为指定构造器，还是作为便利构造器。无论哪种情况，都必须为构造器实现标上 required 修饰符
// 因为使用 required 修饰符可以确保所有子类也必须提供此构造器实现，从而也能符合协议。
// 注意如果`类`已经被标记为final，那么不需要在协议构造器的实现中使用required修饰符，因为final类不能有子类
class SomeClass: SomeProtocol {
    required init(someParameter: Int) {
        
    }
}



// 如果一个子类重写了父类的指定构造器，并且该构造器满足了某个协议的要求，那么该构造器的实现需要同时标注required和override修饰符
protocol InitProtocol {
    init()
}

class InitBaseClass {
    init() { }
}


// 写继承列表应该先写类，再写协议
class InitClass: InitBaseClass, InitProtocol {
    override required init() { }
}


// 可失败构造器要求
// 遵循协议的类型可以通过可失败构造器（init?）或非可失败构造器（init）来满足协议中定义的可失败构造器要求
// 协议中定义的非可失败构造器要求可以通过非可失败构造器（init）或隐式解包可失败构造器（init!）来满足。




// 协议作为类型
// 作为函数、方法或构造器中的参数类型或返回值类型
// 作为常量、变量或属性的类型
// 作为数组、字典或其他容器中的元素类型
class Dice {
    let sides: Int
    let generator: RandomNumberGenerator
    
    init(sides: Int, generator: RandomNumberGenerator) {
        self.sides = sides
        self.generator = generator
    }
    
    func roll() -> Int {
        return Int(generator.random()*Double(self.sides)) + 1
    }
}

let dice = Dice(sides: 6, generator: LinearCongruentialGenerator())
print("Roll: \(dice.roll())")
print("Roll: \(dice.roll())")
print("Roll: \(dice.roll())")
print("Roll: \(dice.roll())")


// 委托(代理)模式
// 委托模式允许类或结构体将一些需要它们负责的功能委托给其他类型的实例
// 委托模式定义协议来封装那些需要被委托的功能，这样就能确保遵循协议的类型能提供这些功能
// 委托模式可以用来响应特定的动作，或者接收外部数据源提供的数据，而无需关心外部数据源的类型


// DiceGame 协议可以被任意涉及骰子的游戏遵循。
protocol DiceGame {
    var dice: Dice { get }
    func Play()
}

// DiceGameDelegate 协议可以被任意类型遵循，用来追踪 DiceGame 的游戏过程
protocol DiceGameDelegate {
    func GameDidStart(_ game: DiceGame)
    func game(_ game: DiceGame, didStartNewTurnWithDiceRoll diceRoll: Int)
    func GameDidEnd(_ game: DiceGame)
}


class SnakesAndLadders: DiceGame {
    let dice = Dice(sides: 6, generator: LinearCongruentialGenerator())
    let finalSquare = 25
    
    var board: [Int]
    var delegate: DiceGameDelegate?
    
    init() {
        board = [Int](repeating:0, count: finalSquare + 1)
        board[03] = +08; board[06] = +11; board[09] = +09; board[10] = +02
        board[04] = -10; board[19] = -11; board[22] = -02; board[24] = -08
    }
    
    func Play() {
        var square = 0
        
        // 因为 delegate 是一个 DiceGameDelegate 类型的可选属性，
        // 因此在 play() 方法中通过可选链式调用来调用它的方法
        // 若 delegate 属性为 nil，则调用方法会优雅地失败，并不会产生错误
        delegate?.GameDidStart(self)
        gameLoop: while square != finalSquare {
            let diceRoll = dice.roll()
            delegate?.game(self, didStartNewTurnWithDiceRoll: diceRoll)
            switch square + diceRoll {
            case finalSquare:
                break gameLoop
            case let newSquare where newSquare > finalSquare:
                continue gameLoop
            default:
                square += diceRoll
                square += board[square]
            }
        }
        delegate?.GameDidEnd(self)
    }
}

class DiceTracker: DiceGameDelegate {
    var numberOfTurns = 0
    func GameDidStart(_ game: DiceGame) {
        if game is SnakesAndLadders {
            print("Start a new game of Snakes and Ladders")
        }
        print("The game is using a \(game.dice.sides)-sided game")
    }
    func game(_ game: DiceGame, didStartNewTurnWithDiceRoll diceRoll: Int) {
        numberOfTurns += 1
        print("Rolled a \(diceRoll)")
    }
    func GameDidEnd(_ game: DiceGame) {
        print("Game lasts for \(numberOfTurns) turns")
    }
}

let tracker = DiceTracker()
let game = SnakesAndLadders()

game.delegate = tracker
game.Play()

// 通过扩展添加协议一致性
protocol TextRepesentable {
    var textualDescription: String { get }
}
