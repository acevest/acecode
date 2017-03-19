//: [Previous](@previous)

import Foundation

var str = "Hello, NestTypes"

//: [Next](@next)


struct BlackjackCard {
    // 嵌套的 Suit 枚举
    enum Suit: Character {
        case Spades = "♠", Hearts = "♡", Diamonds = "♢", Clubs = "♣"
    }
    
    // 嵌套的 Rank 枚举
    enum Rank: Int {
        case Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten
        case Jack, Queen, King, Ace
        struct Values {
            let first: Int, second: Int?
        }
        var values: Values {
            switch self {
            case .Ace:
                return Values(first: 1, second: 11)
            case .Jack, .Queen, .King:
                return Values(first: 10, second: nil)
            default:
                return Values(first: self.rawValue, second: nil)
            }
        }
    }
    
    // BlackjackCard 的属性和方法
    let rank: Rank, suit: Suit
    var description: String {
        var output = "suit is \(suit.rawValue),"
        output += " value is \(rank.values.first)"
        if let second = rank.values.second {
            output += " or \(second)"
        }
        return output
    }
}

let theAceOfSpades = BlackjackCard(rank: .Ace, suit: .Spades)
print("theAceOfSpades: \(theAceOfSpades.description)")


// 引用嵌套类型
// 在外部引用嵌套类型时，在嵌套类型的类型名前加上其外部类型的类型名作为前缀
let heartsSymbol = BlackjackCard.Suit.Hearts.rawValue
print(heartsSymbol)
