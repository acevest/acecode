//: [Previous](@previous)

import UIKit

enum CompassPoint {
    case North
    case East
    case South
    case West
}

var directionToHead = CompassPoint.North
directionToHead = .East

switch directionToHead {
    case .North: print("Losts of Plantes Have a North")
    case .East : print("Where the Sun Rises")
    case .South: print("Watch Out for Penguins")
    case .West : print("Where the Skies are Blue")
}


// Associated Values
printLine("Enumeration Associated Values")
enum BarCode {
    case UPCA(Int, Int, Int, Int)
    case QRCode(String)
}

var productBarCode = BarCode.UPCA(8, 88488, 66366, 2)
productBarCode = .QRCode("QRCode-123456")

switch productBarCode {
case let .UPCA(numberSystem, manufacturer, product, check) :
    print("UPC-A: \(numberSystem), \(manufacturer), \(product), \(check)")
case let .QRCode(productCode) :
    print("QR Code: \(productBarCode)")
}


printLine("RawValues")
// Raw Values
enum ASCIIControlCharacter: Character {
    case Tab            = "\t"
    case LineFeed       = "\n"
    case CarriageReturn = "\r"
}

// Implicitly Assigned Raw Values
// 整型从0开始自增1，每个项的rawValue不能相同
enum Planet: Int {
    case Mercury
    case Venus
    case Earth
    case Mars
    case Jupiter
    case Saturn
    case Uranus
    case Netpune
}

print(Planet.Mercury, Planet.Mercury.rawValue)
print(Planet.Mars, Planet.Mars.rawValue)
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
    case Number(Int)
    case Add(Exp, Exp)  // indirect 也可以放在case语句之前
    case Mul(Exp, Exp)
}


let exp = Exp.Mul(Exp.Add(Exp.Number(2), Exp.Number(5)), Exp.Number(7))

func evaluateExp(exp: Exp) -> Int {
    switch exp {
    case let .Number(n):
        return n
    case let .Add(a, b) :
        return evaluateExp(a) + evaluateExp(b)
    case let .Mul(a, b):
        return evaluateExp(a) * evaluateExp(b)
    }
}

print(evaluateExp(exp))
