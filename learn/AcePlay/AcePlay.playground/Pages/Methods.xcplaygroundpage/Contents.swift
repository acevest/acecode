//: [Previous](@previous)

import Foundation

var str = "Hello, playground"

//: [Next](@next)

class Counter {
    var count = 0
    
    func increment() {
        count += 1
    }
    
    func increment(by amount: Int) {
        count += amount
    }
    
    func reset() {
        count = 0
    }
}

var counter = Counter()

counter.increment()
print(counter.count)
counter.increment(by: 100)
print(counter.count)
counter.reset()
print(counter.count)

struct Point {
    var x = 0.0, y = 0.0
    // 结构体和枚举是值类型。默认情况下，值类型的属性不能在它的实例方法中被修改，如果要修改将关键字mutating 放到方法的func关键字之前
    mutating func move(x deltaX: Double, y deltaY: Double) {
        self.x += deltaX
        self.y += deltaY
    }
    
    // 可变方法能够赋给隐含属性self一个全新的实例
    mutating func moveTo(x deltaX: Double, y deltaY: Double) {
        self = Point(x: deltaX, y: deltaY)
    }
    var description: String {
        get {
            return "Point(\(x), \(y))"
        }
    }
}


var point = Point()
print(point.description)
point.move(x: 1, y: 7)
print(point.description)
point.move(x: 8, y: 4)
print(point.description)
point.moveTo(x: 9, y: 9)
print(point.description)


// 枚举的可变方法可以把self设置为同一枚举类型中不同的成员
enum TriStateSwitch: String {
    case Off
    case Low
    case High
    
    mutating func next() {
        switch self {
        case .Off:
            self = .Low
        case .Low:
            self = .High
        case .High:
            self = .Off
        }
    }
    
    var description: String {
        return "Current State: \(self.rawValue)"
    }
}

var ovenLight = TriStateSwitch.High
print(ovenLight.description)
ovenLight.next()
print(ovenLight.description)
ovenLight.next()
print(ovenLight.description)
ovenLight.next()
print(ovenLight.description)

// 类型方法
class SomeClass {
    // static & class 加在func前都是定义类型方法的关键字
    // 不同的是static的不能被子类重写该方法
    // 而class则可以
    static func descV1() -> String {
        return "BaseDescV1"
    }
    class func descV2() -> String {
        return "BaseDescV2"
    }
}

class SomeDerivedClass: SomeClass {
    /*
    取消注释会编译错误
    override static func descV1() -> String {
        return "BaseDescV1"
    }
    */
    override class func descV2() -> String {
        return "DerivedDescV2"
    }
}

print(SomeClass.descV1())
print(SomeClass.descV2())
print(SomeDerivedClass.descV1())
print(SomeDerivedClass.descV2())


class LevelTracker {
    static var highestUnlockedLevel = 1
    var currentLevel = 1
    
    static func unlock(_ level: Int) {
        if level > highestUnlockedLevel {
            highestUnlockedLevel = level
        }
    }
    
    static func isUnlocked(_ level: Int) -> Bool {
        return level <= highestUnlockedLevel
    }
    
    @discardableResult  // 可以忽略返回值，不会产生警告
    func advance(to level: Int) -> Bool {
        if LevelTracker.isUnlocked(level) {
            currentLevel = level
            return true
        } else {
            return false
        }
    }
}

class Player {
    var tracker = LevelTracker()
    let playerName: String
    
    init(name: String) {
        self.playerName = name
    }
    
    func complete(level: Int) {
        LevelTracker.unlock(level)
        tracker.advance(to: level)
    }
}


var player = Player(name: "Ace")
player.complete(level: 1)
player.complete(level: 2)
if player.tracker.advance(to: 3) {
    print("player is now on level 3")
} else {
    print("level 3 has not yet been unlocked")
}
player.complete(level: 3)
if player.tracker.advance(to: 3) {
    print("- player is now on level 3")
} else {
    print("- level 3 has not yet been unlocked")
}
