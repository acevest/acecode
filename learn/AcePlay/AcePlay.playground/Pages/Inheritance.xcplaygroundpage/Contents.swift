//: [Previous](@previous)

import Foundation

var str = "Hello, Inheritance"

//: [Next](@next)

class Vehicle {
    var currentSpeed = 0.0
    var description: String {
        return "traveling at \(currentSpeed) miles per hour"
    }
    
    func makeNoise() {
        // to do nothing
    }
}

let someVehicle = Vehicle()
print("Vehicle: \(someVehicle.description)")

class Bicycle: Vehicle {
    var hasBasket = false
}
let someBicycle = Bicycle()
someBicycle.hasBasket = true
someBicycle.currentSpeed = 13.5
print("Bicycle: \(someBicycle.description)")


class Tandem: Bicycle {
    var currentNumberOfPassengers = 0
}

let someTandem = Tandem()
someTandem.hasBasket = true
someTandem.currentSpeed = 19.9
someTandem.currentNumberOfPassengers = 2
print("Tandem: \(someTandem.description)")

// 重写
// 子类可以为继承来的实例方法，类方法，实例属性，或下标提供自己定制的实现。我们把这种行为叫重写
// 如果要重写某个特性，需要在重写定义的前面加上override关键字
class Train: Vehicle {
    override func makeNoise() {
        print("Choo Choo")
    }
}

let someTrain = Train()
someTrain.makeNoise()


// 重写属性
// 可以重写继承来的实例属性或类型属性，提供自己定制的 getter 和 setter，或添加属性观察器使重写的属性可以观察属性值什么时候发生改变
// 可以将一个继承来的只读属性重写为一个读写属性
// 不可以将一个继承来的读写属性重写为一个只读属性

// 如果在重写属性中提供了setter，那么也一定要提供getter
// 如果不想在重写版本中的getter 里修改继承来的属性值
// 可以直接通过super.someProperty来返回继承来的值，其中someProperty是要重写的属性的名字

class Car: Vehicle {
    var gear = 1
    
    override var description: String {
        return super.description + " in gear \(gear)"
    }
}

let someCar = Car()
someCar.currentSpeed = 72.7
someCar.gear = 3
print("Car: \(someCar.description)")

// 重写属性观察器
// 可以通过重写属性为一个继承来的属性添加属性观察器
class AutomaticCar: Car {
    override var currentSpeed: Double {
        didSet {
            gear = Int(currentSpeed/20.0) + 1
        }
    }
}
let someAutomaticCar = AutomaticCar()
someAutomaticCar.currentSpeed = 67.3
print("AutomaticCar: \(someAutomaticCar.description)")

// 防止重写
// 以通过把方法，属性或下标标记为final来防止它们被重写，只需要在声明关键字前加上final修饰符即可
// 例如：final var，final func，final class func，以及final subscript
// 在类扩展中的方法，属性或下标也可以在扩展的定义里标记为final的
// 可以通过在关键字class前添加final修饰符来将整个类标记为不可被继承的，试图继承这样的类会导致编译报错


