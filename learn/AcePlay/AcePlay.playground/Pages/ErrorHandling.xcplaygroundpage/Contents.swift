//: [Previous](@previous)

import Foundation

var str = "Hello, Error Handling"

//: [Next](@next)


// 错误用符合Error协议的类型的值来表示。这个空协议表明该类型可以用于错误处理

enum VendingMachineError: Error {
    case invalidSelection
    case outOfSock
    case insufficientFunds(coinsNeeded: Int)
}



struct Item {
    var price: Int
    var count: Int
}

class VendingMachine {
    var inventory = [
        "Candy Bar": Item(price: 5, count: 100),
        "Chips": Item(price: 9, count: 9),
        "Pretzels" :Item(price: 7, count: 11)
    ]
    
    var coinsDeposited = 0
    
    func dispenseSnack(snack: String) {
        print("Dispensing \(snack)")
    }
    
    func vend(itemNamed name: String) throws {
        guard let item = inventory[name] else {
            throw VendingMachineError.invalidSelection
        }
        
        guard item.count > 0 else {
            throw VendingMachineError.outOfSock
        }
        
        guard item.price <= coinsDeposited else {
            throw VendingMachineError.insufficientFunds(coinsNeeded: item.price - coinsDeposited)
        }
        
        coinsDeposited -= item.price
        
        inventory[name]!.count -= 1
        print("Dispensing \(name)")
    }
}


let favoriteSnack = [
    "Alice": "Chips",
    "Bob": "Licorice",
    "Eve": "Pretzels"
]



func buyFavoriteSnack(name: String, vendMachine: VendingMachine) throws {
    let snackName = favoriteSnack[name] ?? "Candy Bar"
    try vendMachine.vend(itemNamed: snackName)  // 因为vend会抛出异常，所以前面加try关键字
}


struct PurchasedSnack {
    let name: String
    
    init(name: String, vendingMachine: VendingMachine) throws { // 构造器也可抛出异常
        try vendingMachine.vend(itemNamed: name)
        self.name = name
    }
}



var vendingMachine = VendingMachine()
vendingMachine.coinsDeposited = 3
do {
    try buyFavoriteSnack(name: "Alice", vendMachine: vendingMachine)
} catch VendingMachineError.invalidSelection {
    print("Invalid Selection")
} catch VendingMachineError.outOfSock {
    print("Out of sock")
} catch VendingMachineError.insufficientFunds(let coinsNeeded) {
    print("Insufficient funds. Please insert an additional \(coinsNeeded) coins")
}


// 将错误转换成可选值
// 可以使用try?通过将错误转换成一个可选值来处理错误。如果在评估try?表达式时一个错误被抛出，那么表达式的值就是nil
//func someThrowingFunction() throws -> Int {
//    // ...
//}
//
//let x = try? someThrowingFunction()
//
//let y: Int?
//do {
//    y = try someThrowingFunction()
//} catch {
//    y = nil
//}
// 如果someThrowingFunction()抛出一个错误，x和y的值是nil。否则x和y的值就是该函数的返回值。
// 注意，无论someThrowingFunction()的返回值类型是什么类型，x和y都是这个类型的可选类型。例子中此函数返回一个整型，所以x和y是可选整型。


// 禁用错误传递
// 有时知道某个throwing函数实际上在运行时是不会抛出错误的，可以在表达式前面写try!来禁用错误传递
// 这会把调用包装在一个不会有错误抛出的运行时断言中
// 如果真的抛出了错误，会得到一个运行时错误




// 指定清理操作
func testDefer() {
    print("\(#function):\(#line)")
    defer {
        print("Top Level Defer")
    }
    
    print("\(#function):\(#line)")
    if arc4random_uniform(100) < 50 {
        print("\(#function):\(#line)")
        defer {
            print("Sub Level if Defer")
        }
        print("\(#function):\(#line)")
    } else {
        print("\(#function):\(#line)")
        defer {
            print("Sbu Level else Defer")
        }
        print("\(#function):\(#line)")
    }
    
    print("\(#function):\(#line)")
    print("End of Function \(#function)")
}


testDefer()
