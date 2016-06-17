//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground.小狗:🐶 锤子:🔨"


func printLine(title: String) -> Void {
    let line = String(format:"[%@]-----------------------------------", title)
    print(line)
}

// Index
var strInx:String.Index = str.startIndex
strInx.successor()
print(strInx)

for c in str.characters {
    print(c, terminator: "")
}
print()

// Print separator & terminator
var company:Array<String> = [ "Apple", "Google", "Facebook", "Tencent" ]
print(company[0], company[1], company[2], company[3], separator: "#", terminator: " $$$$$\n")

printLine("Count company Array 1")
for (i,v) in company.enumerate() {
    print(i, v, separator: " - ", terminator: "\n")
}

printLine("Count company Array 2")
company.insert("Alibaba", atIndex: company.count)
for i in 0..<company.count {
    print(i, company[i], separator: " - ")
}
company.removeLast()

var someIntsA: [Int] = []
var someIntsB = [Int]()
var someIntsC = [Int](count: 10, repeatedValue: 1)
someIntsA.append(1)
someIntsB.replaceRange(Range<Int>(0..<someIntsB.count), with: [1,3,4])
someIntsC.removeAtIndex(4)

