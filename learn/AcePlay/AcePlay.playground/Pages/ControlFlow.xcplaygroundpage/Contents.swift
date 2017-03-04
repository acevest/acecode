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
    fallthrough                 // 默认不走到下一个case
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