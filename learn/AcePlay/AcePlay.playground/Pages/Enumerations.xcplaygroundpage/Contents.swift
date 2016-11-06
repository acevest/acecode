//: [Previous](@previous)

import UIKit

enum CompassPoint {
    case north
    case east
    case south
    case west
}

var directionToHead = CompassPoint.north
directionToHead = .east

switch directionToHead {
    case .north: print("Losts of Plantes Have a North")
    case .east : print("Where the Sun Rises")
    case .south: print("Watch Out for Penguins")
    case .west : print("Where the Skies are Blue")
}


// Associated Values
printLine("Enumeration Associated Values")
enum BarCode {
    case upca(Int, Int, Int, Int)
    case qrCode(String)
}

var productBarCode = BarCode.upca(8, 88488, 66366, 2)
productBarCode = .qrCode("QRCode-123456")

switch productBarCode {
case let .upca(numberSystem, manufacturer, product, check) :
    print("UPC-A: \(numberSystem), \(manufacturer), \(product), \(check)")
case let .qrCode(productCode) :
    print("QR Code: \(productBarCode)")
}


printLine("RawValues")
// Raw Values
enum ASCIIControlCharacter: Character {
    case tab            = "\t"
    case lineFeed       = "\n"
    case carriageReturn = "\r"
}

// Implicitly Assigned Raw Values
// 整型从0开始自增1，每个项的rawValue不能相同
enum Planet: Int {
    case mercury
    case venus
    case earth
    case mars
    case jupiter
    case saturn
    case uranus
    case netpune
}

print(Planet.mercury, Planet.mercury.rawValue)
print(Planet.mars, Planet.mars.rawValue)
print(Planet(rawValue: 5)!, Planet(rawValue: 5)!.rawValue)


// String型，每项默认为枚举项的字符串值
enum CompassPointString: String {
    case North
    case East
    case Sourth
    case West
}


print(CompassPointString.North, CompassPointString.North.rawValue)
print(CompassPointString.East,  CompassPointString.East.rawValue)
print(CompassPointString.Sourth,CompassPointString.Sourth.rawValue)
print(CompassPointString.West,  CompassPointString.West.rawValue)


printLine("Resursive Enumerations")
// 不能忘记 indirect
indirect enum Exp {
    case number(Int)
    case add(Exp, Exp)  // indirect 也可以放在case语句之前
    case mul(Exp, Exp)
}


let exp = Exp.mul(Exp.add(Exp.number(2), Exp.number(5)), Exp.number(7))

func evaluateExp(_ exp: Exp) -> Int {
    switch exp {
    case let .number(n):
        return n
    case let .add(a, b) :
        return evaluateExp(a) + evaluateExp(b)
    case let .mul(a, b):
        return evaluateExp(a) * evaluateExp(b)
    }
}

print(evaluateExp(exp))
