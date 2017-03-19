//: [Previous](@previous)

import Foundation

var str = "Hello, Optional Chaining"

//: [Next](@next)


// 使用可选链式调用代替强制展开
// 通过在想调用的属性、方法、或下标的可选值后面放一个问号（?），可以定义一个可选链。这一点很像在可选值后面放一个叹号（!）来强制展开它的值。
// 它们的主要区别在于当可选值为空时可选链式调用只会调用失败，然而强制展开将会触发运行时错误。

// 特别地，可选链式调用的返回结果与原本的返回结果具有相同的类型，但是被包装成了一个可选值。
// 例如，使用可选链式调用访问属性，当可选链式调用成功时，如果属性原本的返回结果是Int类型，则会变为Int?类型

class PersonV1 {
    var residence: RecidenceV1?
}

class RecidenceV1 {
    var numberOfRooms = 7
}

let john = PersonV1()

// 当john.residence==nil时以下这句会引发运行错误
// let roomCount == john.residence!.numberOfRooms

if let roomCount = john.residence?.numberOfRooms {
    print("John's residence has \(roomCount) room(s)")
} else {
    print("Unable to retrieve the number of rooms.")
}




john.residence = RecidenceV1()
if let roomCount = john.residence?.numberOfRooms {
    print("John's residence has \(roomCount) room(s)")
} else {
    print("Unable to retrieve the number of rooms.")
}


// 通过使用可选链式调用可以调用多层属性、方法和下标。这样可以在复杂的模型中向下访问各种子属性，并且判断能否访问子属性的属性、方法或下标。
class Person {
    var residence: Recidence?
}

class Recidence {
    var rooms = [Room]()
    var numberOfRooms: Int {
        return rooms.count
    }
    var address: Address?
    
    subscript(i: Int) -> Room {
        get {
            return rooms[i]
        }
        set {
            rooms[i] = newValue
        }
    }
    
    func printNumberOfRooms() {
        print("The number of room is \(numberOfRooms)")
    }

}

class Room {
    let name: String
    init(name: String) {
        self.name = name
    }
}

class Address {
    var buildingName: String?
    var buildingNumber: String?
    var street: String?
    
    func buildingIdentifier() -> String? {
        if buildingName != nil {
            return buildingName
        } else if buildingNumber != nil && street != nil {
            return "\(buildingNumber!) \(street!)"
        } else {
            return nil
        }
    }
}

let obama = Person()
if let roomCount = obama.residence?.numberOfRooms {
    print("Obama's residence has \(roomCount) room(s)")
} else {
    print("Unable to retrieve the number of rooms.")
}


let addr = Address()
addr.buildingNumber = "31"
addr.street = "Wall Street"

obama.residence?.address = addr     // 此时residence==nil，会设置失败
// 上面的赋值过程是可选链式调用的一部分，这意味着可选链式调用失败时，等号右侧的代码不会被执行


func CreateAddress() -> Address {
    print("CreateAddress was Called")
    let addr = Address()
    addr.buildingNumber = "13"
    addr.street = "Pennsylvania Avenue"
    return addr
}

obama.residence?.address = CreateAddress()  // 可以通过并未输出print内容来验证出CreateAddress并未被执行


// 对于Residence.printNumberOfRooms
// 如果在可选值上通过可选链式调用来调用这个方法，该方法的返回类型会是Void?，而不是Void，因为通过可选链式调用得到的返回值都是可选的

if obama.residence?.printNumberOfRooms() == nil {
    print("It was not possible to print the number of rooms.")
} else {
    print("It was possible to print the number of rooms.")
}


// 同样的，可以据此判断通过可选链式调用为属性赋值是否成功
// 即使residence为nil。通过可选链式调用给属性赋值会返回Void?，通过判断返回值是否为nil就可以知道赋值是否成功
if (obama.residence?.address = addr) == nil {
    print("It was not possible to set the address.")
} else {
    print("It was possible to set the address.")
}




// 通过可选链式调用访问下标
// 注意: 通过可选链式调用访问可选值的下标时，应该将问号放在下标方括号的前面而不是后面。可选链式调用的问号一般直接跟在可选表达式的后面。
if let firstRoomName = obama.residence?[0].name {
    print("The first room name is \(firstRoomName).")
} else {
    print("Unable to retrieve the first room name.")
}


print("It's time to buy a house for Obama")
let obamaHouse = Recidence()
obamaHouse.rooms.append(Room(name: "Kitchen"))
obamaHouse.rooms.append(Room(name: "Living Room"))

obama.residence = obamaHouse

if let firstRoomName = obama.residence?[0].name {
    print("The first room name is \(firstRoomName).")
} else {
    print("Unable to retrieve the first room name.")
}




// 访问可选类型的下标
var scores = ["Trump": [59, 48,66], "Obama": [44, 65, 73], "Bush": [23, 32, 45], "Clinton": [37, 76, 19]]
scores["Trump"]?[0] = 58
scores["Bush"]?[2] += 4
// scores["Clinton"]?[5] = 33 // error 因为，可选链会返回一个数组，然后索引为5就超出了范围
scores["Ace"]?[1] = 100 // 调用失败，但不会出错
print(scores.description)



// 连接多层可选链式调用
// 可以通过连接多个可选链式调用在更深的模型层级中访问属性、方法以及下标。然而，多层可选链式调用不会增加返回值的可选层级。
// 也就是说
// 1. 如果你访问的值不是可选的，可选链式调用将会返回可选值
// 2. 如果你访问的值就是可选的，可选链式调用不会让可选返回值变得“更可选”

// 因此
// 通过可选链式调用访问一个Int值，将会返回Int?，无论使用了多少层可选链式调用
// 通过可选链式调用访问Int?值，依旧会返回Int?值，并不会返回Int??


if let obamasStreet = obama.residence?.address?.street {
    print("Obama's street name is \(obamasStreet)")
} else {
    print("Unable to retrieve the address")
}

print("It's time to give address to Obama's House")
obama.residence?.address = CreateAddress()
if let obamasStreet = obama.residence?.address?.street {
    print("Obama's street name is \(obamasStreet)")
} else {
    print("Unable to retrieve the address")
}



// 在方法的可选返回值上进行可选链式调用
// 上面的例子展示了如何在一个可选值上通过可选链式调用来获取它的属性值
// 还可以在一个可选值上通过可选链式调用来调用方法
// 并且可以根据需要继续在方法的可选返回值上进行可选链式调用

if let buildingIdentifier = obama.residence?.address?.buildingIdentifier() {
    print("Obama's building identifier is \(buildingIdentifier)")
}


// 还可以在该方法的返回值上进行链式调用

if let beginWithThe = obama.residence?.address?.buildingIdentifier()?.hasPrefix("The") {
    if beginWithThe {
        print("Obama's building identifier begins with \"The\"")
    } else {
        print("Obama's building identifier does not begins with \"The\"")
    }
}

print("End")
