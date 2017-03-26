//: [Previous](@previous)

import Foundation

var str = "Hello, Generics"

//: [Next](@next)

func swapTwoValues<T>(_ a: inout T, _ b: inout T) {
    var c: T
    c = a
    a = b
    b = c
}

var aInt = 3
var bInt = 4

swapTwoValues(&aInt, &bInt)
print(aInt, bInt)


var aStr = "aStr"
var bStr = "bStr"
swapTwoValues(&aStr, &bStr)
print(aStr, bStr)


// 可提供多个类型参数，将它们都写在尖括号中，用逗号分开
// 如Dictionary<Key, Value> 中的 Key 和 Value


class Stack<Element> {
    var stack = [Element]()
    
    func push(_ item: Element) {
        stack.append(item)
    }
    
    func pop() -> Element? {
        return stack.removeLast()
    }
    
    var size: Int {
        return stack.count
    }
}

var stackOfStrings = Stack<String>()
stackOfStrings.push("A")
stackOfStrings.push("B")
stackOfStrings.push("C")
stackOfStrings.push("DEFG")

while stackOfStrings.size > 0 {
    var s = stackOfStrings.pop()
    print(s!)
}



// 类型约束
// 可以在一个类型参数名后面放置一个类名或者协议名，并用冒号进行分隔，来定义类型约束
// 这个函数有两个类型参数。第一个类型参数 T，有一个要求 T 必须是 SomeClass 子类的类型约束；第二个类型参数 U，有一个要求 U 必须符合 SomeProtocol 协议的类型约束
//func someConstraintGenericFunc<T: SomeClass, U: SomeProtocol>(someT: T, someU: U) {
//    
//}


// Swift 标准库中定义了一个 Equatable 协议，该协议要求任何遵循该协议的类型必须实现等式符（==）及不等符(!=)，从而能对该类型的任意两个值进行比较
func findIndex<T: Equatable>(of valueToFind: T, in array: [T]) -> Int? {
    for (index, value) in array.enumerated() {
        if value == valueToFind { // 需要T类型支持Equatable的协议
            return index
        }
    }
    
    return nil
}

print(findIndex(of: 1.2, in: [1.3, 4.0, 5, 8.9]) ?? "can not find 1.2")
print(findIndex(of: "ace", in: ["john", "obama", "ace"]) ?? "nothing")




// 关联类型
// 定义一个协议时，有的时候声明一个或多个关联类型作为协议定义的一部分将会非常有用。
// 关联类型为协议中的某个类型提供了一个占位名（或者说别名），其代表的实际类型在协议被采纳时才会被指定。
// 可以通过 associatedtype 关键字来指定关联类型。

protocol Container {
    associatedtype T
    mutating func append(_ item: T)
    var count: Int { get }
    subscript(i: Int) -> T { get }
}


struct StackB<Element>: Container {
    var stack = [Element]()
    
    mutating func push(_ item: Element) {
        stack.append(item)
    }
    
    mutating func pop() -> Element? {
        return stack.removeLast()
    }
    
    var size: Int {
        return stack.count
    }
    
    mutating func append(_ item: Element) {
        self.push(item)
    }
    
    var count: Int {
        return size
    }
    
    subscript(i: Int) -> Element {
            return stack[i]
    }
}



//
// 通过扩展一个存在的类型来指定关联类型
//
// 通过扩展添加协议一致性中描述了如何利用扩展让一个已存在的类型符合一个协议，这包括使用了关联类型的协议。
//
// Swift 的 Array 类型已经提供 append(_:) 方法，一个 count 属性，以及一个接受 Int 类型索引值的下标用以检索其元素。
// 这三个功能都符合 Container 协议的要求，也就意味着只需简单地声明 Array 采纳该协议就可以扩展 Array，使其遵从 Container 协议。可以通过一个空扩展来实现这点，正如通过扩展采纳协议中的描述：
//
extension Array: Container {}
// 如同上面的泛型 Stack 结构体一样，Array 的 append(_:) 方法和下标确保了 Swift 可以推断出 ItemType 的类型。定义了这个扩展后，可以将任意 Array 当作 Container 来使用。



// 泛型 Where 语句
// C1 必须符合 Container 协议（写作 C1: Container）。
//C2 必须符合 Container 协议（写作 C2: Container）。
//C1 的T必须和C2的T类型相同（写作 C1.T == C2.T）。
//C1 的T必须符合Equatable 协议（写作 C1.T: Equatable）
func allItemsMatch<C1: Container, C2: Container>(_ someContainer: C1, _ anotherContainer: C2) -> Bool where C1.T == C2.T, C1.T: Equatable {
    if someContainer.count != anotherContainer.count {
        return false
    }
    
    for i in 0..<someContainer.count {
        if someContainer[i] != anotherContainer[i] {
            return false
        }
    }
    
    return true
}


var stringStack = StackB<String>()
stringStack.push("abc")
stringStack.push("def")
stringStack.push("xyz")

var stringArray = ["abc", "def", "xyz"]

if allItemsMatch(stringStack, stringArray) {
    print("All items match")
} else {
    print("Not all items match")
}


