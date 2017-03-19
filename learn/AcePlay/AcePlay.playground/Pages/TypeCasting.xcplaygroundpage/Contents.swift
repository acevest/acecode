//: [Previous](@previous)

import Foundation

var str = "Hello, TypeCasting"

//: [Next](@next)


class MediaItem {
    var name: String
    
    init(name: String) {
        self.name = name
    }
}


class Movie: MediaItem {
    var director: String
    init(name: String, director: String) {
        self.director = director
        
        super.init(name: name)
    }
}

class Song: MediaItem {
    var artist: String
    init(name: String, artist: String) {
        self.artist = artist
        
        super.init(name: name)
    }
}


// 这个数组将会被推断为MediaItem类型
let library = [
    Movie(name: "Casablanca", director: "Michael Curtiz"),
    Song(name: "Blue Suede Shoes", artist: "Elvis Presley"),
    Movie(name: "Citizen Kane", director: "Orson Welles"),
    Song(name: "The One And Only", artist: "Chesney Hawkes"),
    Song(name: "Never Gonna Give You Up", artist: "Rick Astley")
]



var movieCount = 0
var songCount = 0

for i in library {
    if i is Movie {
        movieCount += 1
    } else if i is Song {
        songCount += 1
    }
}

print("Media Library contains \(movieCount) Movies and \(songCount) Songs")
print("------------------------------------------------------------------")



// 向下转型
// 某类型的一个常量或变量可能在幕后实际上属于一个子类。当确定是这种情况时，你可以尝试向下转到它的子类型，用类型转换操作符（as? 或 as!）
// 因为向下转型可能会失败，类型转型操作符带有两种不同形式。条件形式as? 返回一个你试图向下转成的类型的可选值。强制形式 as! 把试图向下转型和强制解包转换结果结合为一个操作

for m in library {
    if let movie = m as? Movie {
        print("Movie: \(movie.name) directed by \(movie.director)")
    } else if let song = m as? Song {
        print("Song: \(song.name) by \(song.artist)")
    }
}





// Any和AnyObject的类型转换
// Swift为不确定类型提供了两种特殊的类型别名
// 1. Any可以表示任何类型，包括函数类型
// 2. AnyObject可以表示任何类类型的实例

var things = [Any]()
things.append(99)
things.append(0)
things.append(2.718281828459)
things.append(0.0)
things.append("Hello Swift")
things.append((3, 4))
things.append(Movie(name: "Citizen Kane", director: "Orson Welles"))
things.append( { (name: String) -> String in "Hello \(name)!" } )


print("------------------------------------------------------------------")

for t in things {
    switch t {
    case 0 as Int:
        print("zero as Int")
    case 0 as Double:
        print("zero as Double")
    case let someInt as Int :
        print("an integer value of \(someInt)")
    case let someDouble as Double where someDouble > 0 :
        print("a positive double value of \(someDouble)")
    case is Double:
        print("some other double value that i do not want to print")
    case let someStr as String:
        print("a string value of \"\(someStr)\"")
    case let (x, y) as (Int, Int) :
        print("an (x, y) point at (\(x), \(y)")
    case let movie as Movie:
        print("a movie named \(movie.name) directed by \(movie.director)")
    case let strConverter as (String) -> String :
        print(strConverter("Ace"))
    default:
        print("Something else")
    }
}


// 注意:Any类型可以表示所有类型的值，包括可选类型
// Swift会在你用Any类型来表示一个可选值的时候，给一个警告。如果确实想使用Any类型来承载可选值，你可以使用as操作符显式转换为Any
let optionalNumber: Int? = 3
// things.append(optionalNumber) // 会有warning
things.append(optionalNumber as Any) // 不会有warning
