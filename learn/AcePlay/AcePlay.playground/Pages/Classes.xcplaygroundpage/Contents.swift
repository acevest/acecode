//: [Previous](@previous)

import UIKit

printLine("Classes & Structures")

struct ResolutionA {
    var width = 0
    var height: Int
}

// 如果成员未初始化，在实例化的时候要初始化所有成员
var resolutionA = ResolutionA(width: 2, height: 3)


struct Resolution {
    var width  = 0
    var height = 0
}
var resolutionB = Resolution()  // 成员初始化完了则不用

let vga = Resolution(width: 640, height: 480)
let hd  = Resolution(width: 1920, height: 1080)
var cinema = hd
cinema.width  = 2048

// Struct 是值类型
print("HD: \(hd.width)x\(hd.height)")
print("Cinema: \(cinema.width)x\(cinema.height)")


class VideoMode {
    var resolution = Resolution()
    var interlaced = false
    var frameRate = 0.0
    var name: String?
}

let someVideoMode = VideoMode()
someVideoMode.resolution.width  = 1680  // Class是引用类型，所以纵然someVideoMode是常量，但其指向的是变量
someVideoMode.resolution.height = 1050  // 属性访问是可以级联进行的

let tenEighty = VideoMode()
tenEighty.resolution = hd
tenEighty.interlaced = true
tenEighty.frameRate  = 25.0
tenEighty.name       = "1080i"

let anotherTenEighty = tenEighty         // 引用赋值
anotherTenEighty.frameRate = 30.0
print("Now TenEight Frame Rate: \(tenEighty.frameRate)")


printLine("Identity Operators")
if anotherTenEighty === tenEighty {
    print("tenEighty & anotherTenEighty refer to the same VideoMode instance")
}

if someVideoMode !== tenEighty {
    print("someVideoMode & tenEighty refer to different VideoMode instance")
}