//: [Previous](@previous)

import Foundation


//: [Next](@next)


for index in 1...5 {
    print("\(index) * 5 = \(index*5)")
}

let base = 2
let power = 10
var answer = 1

for _ in 1...power {
    answer *= base
}

print("\(base) to power of \(power) is \(answer)")


while answer > 0 {
    answer -= 10
}

print("Answer \(answer)")

repeat {
    answer += 10
} while(answer < 1000)

print("Answer \(answer)")


var r = arc4random_uniform(100)

if r % 2 == 1 {
    print("Odd Number \(r)")
} else {
    print("Even Number \(r)")
}


r = arc4random_uniform(100)
if r < 60 {
    print("Failed. Score: \(r)")
} else if r < 80 {
    print("Good. Score: \(r)")
} else {
    print("Perfect. Score: \(r)")
}


let approximateCount = arc4random_uniform(100)
let countedTings = "moon orbiting Saturn"
var naturalCount = ""

switch approximateCount {
case 0:
    naturalCount = "no"
case 1..<5:
    naturalCount = "a few"
case 5:
    // 默认不走到下一个case
    // fallthrough关键字不会检查它下一个将会落入执行的 case 中的匹配条件
    fallthrough
case 6..<12:
    naturalCount = "several"
case 12..<100:
    naturalCount = "dozens of"
case 100..<1000:
    naturalCount = "hundreds of"
default:
    naturalCount = "many"
}

print("There are \(naturalCount) \(countedTings) [\(approximateCount)]")


var x = Int(arc4random_uniform(100))
var y = Int(arc4random_uniform(100))
let s = arc4random_uniform(4)

if s & 1 != 0 {
    x = -x
}

if s & 2 != 0 {
    y = -y
}

let somePoint = (x, y)

switch somePoint {
case (0, 0) :
    print("(0, 0) is at the origin")
    
case (_, 0) :
    print("(\(x), 0) is on the x-axis")

case (0, _) :
    print("(0, \(y)) is on the y-axis")

case (-50...50, -50...50) :
    print("(\(x), \(y)) is inside the box")
    
default:
    print("(\(x), \(y)) is outside the box")
}


// 值绑定 和 where 语句
switch somePoint {
case (let x, 0) :
    print("on the x-axis with a x value of \(x)")

case (0, let y) :
    print("on the y-axis with a y value of \(y)")
    
case let (x, y) where x == y :
    print("(\(x), \(y)) is on the line x = y")

case let (x, y) where x == -y :
    print("(\(x), \(y)) is on the line x = -y")
    
case let (x, y) :
    print("somewhere else at (\(x), \(y))")
}

let alphabet = "abcdefghijklmnopqrstuvwxyz"
let rc = alphabet[alphabet.index(alphabet.startIndex, offsetBy: String.IndexDistance(arc4random_uniform(UInt32(alphabet.characters.count))))]

// 复合匹配
switch  rc {
case "a", "e", "i", "o", "u" :
    print("\(rc) is a vowel")
case "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n",
     "p", "q", "r", "s", "t", "v", "w", "x", "y", "z" :
    print("\(rc) is a consonant")
default:
    print("\(rc) is not a vowel or a consonant")
}

switch somePoint {
case (let distance, 0), (0, let distance) :
    print("On an axis, \(distance) from the origin")
default :
    print("Not on an axis")
}



let finalSquare = 25
var board = [Int](repeating:0, count: finalSquare + 1)

board[03] = +08; board[06] = +11; board[09] = +09; board[10] = +02
board[04] = -10; board[19] = -11; board[22] = -02; board[24] = -08


var diceRoll = 0
var square = 0

gameLoop: while square != finalSquare {
    diceRoll += 1
    
    diceRoll %= 6
    diceRoll += 1
    
    switch diceRoll {
    case finalSquare:
        break gameLoop      // break 会执行gameLoop标签的后一条代码也就是print("Game Over")
    case let newSquare where square > finalSquare:
        continue gameLoop   // continue 会执行gameLoop标签指示的代码
    default:
        square += 1
        diceRoll += board[square]
    }
}

print("Game Over")



// guard
func greet(person: [String:String]) {
    guard let name = person["name"] else {          // guard 总是要跟一个 else
        print("please specify the person's name")
        return                                      // guard 代码体最终必须要退出函数
    }
    
    print("Hello \(name)")
    
    guard let location = person["location"] else {
        print("please specify \(name)'s location")
        return
    }
    
    print("I hope the weather is nice in \(location)")
    
    if #available(iOS 10, macOS 11.12, *) { // 指定代码版本 也可用于 guard 语句
        print("that's right platform")
    } else {
        print("invalid platform")
    }
    
    guard #available(iOS 99, *) else {
        print("Under iOS 99 now")
        return
    }
}

greet(person: ["noname" : "noname"])
greet(person: ["name" : "Ace"])
greet(person: ["name" : "AceVest", "location":"moon"])





