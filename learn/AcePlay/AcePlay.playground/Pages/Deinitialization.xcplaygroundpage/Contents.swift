//: [Previous](@previous)

import Foundation

var str = "Hello, Deinitialization"

//: [Next](@next)

// 析构器只适用于类类型

// 子类继承了父类的析构器，并且在子类析构器实现的最后，父类的析构器会被自动调用。即使子类没有提供自己的析构器，父类的析构器也同样会被调用

class Bank {
    static var totalCoins = 10000
    
    static func distribute(coins numberOfCoinsRequested: Int) -> Int {
        let numberOfCoinsToVend = min(totalCoins, numberOfCoinsRequested)
        
        totalCoins -= numberOfCoinsToVend
        
        return numberOfCoinsToVend
    }
    
    static func receive(coins: Int) {
        totalCoins += coins
    }
}


class Player {
    var coinsInPurse: Int
    
    init(coins: Int) {
        coinsInPurse = Bank.distribute(coins: coins)
    }
    
    func win(coins: Int) {
        coinsInPurse += Bank.distribute(coins: coins)
    }
    
    deinit {
        Bank.receive(coins: coinsInPurse)
    }
}


var player: Player? = Player(coins: 100)
print("A player has joined the game with \(player!.coinsInPurse) coins")
print("There are now \(Bank.totalCoins) coins left in the bank")

player?.win(coins: 1000)
print("A player won 1000 coins and now has \(player!.coinsInPurse) coins")
print("There are now \(Bank.totalCoins) coins left in the bank")

player = nil
print("the player has left the game")
print("There are now \(Bank.totalCoins) coins left in the bank")
