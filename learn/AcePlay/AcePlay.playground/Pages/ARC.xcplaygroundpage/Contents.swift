//: [Previous](@previous)

import Foundation

var str = "Hello, Automatic Reference Counting"

//: [Next](@next)


// 引用计数仅仅应用于类的实例。结构体和枚举类型是值类型，不是引用类型，也不是通过引用的方式存储和传递


class Apartment {
    var address: String
    init(address: String) {
        self.address = address
    }
    
    var tenant: Person?
    
    deinit {
        print("Apartment \(self.address) is being deinitialized")
    }
}

class Person {
    var name: String
    
    init(name: String) {
        if name.isEmpty {
            self.name = "[Unnamed]"
        } else {
            self.name = name
        }
        
        print("Person \(name) is being initialized")
    }
    
    
    deinit {
        print("Person \(name) is being deinitialized")
    }

    var apartment: Apartment?
}


var reference1: Person?
var reference2: Person?
var reference3: Person?


reference1 = Person(name: "Ace")
reference2 = reference1
reference3 = reference1

reference1 = nil
reference2 = nil

// 现在这个Person实例还不会被销毁

print("----------destroy reference3------------")
reference3 = nil



// 类间的循环强引用
var abel: Person?
var unit4A: Apartment?

abel = Person(name: "abel")
unit4A = Apartment(address: "Apartment 4A")

abel!.apartment = unit4A
unit4A!.tenant = abel


// 解决实例之间的循环强引用
// 弱引用（ weak reference ）和无主引用（ unowned reference )
// 1. 对于生命周期中会变为 nil 的实例使用弱引用
// 2. 对于初始化赋值后再也不会被赋值为 nil 的实例，使用无主引用


// 弱引用
// 场景1: 一个人可以没有公寓，一个公寓也可以没有租客
class PersonWeak {
    var name: String
    
    init(name: String) {
        if name.isEmpty {
            self.name = "[Unnamed]"
        } else {
            self.name = name
        }
        
        print("PersonWeak \(name) is being initialized")
    }
    
    
    deinit {
        print("PersonWeak \(name) is being deinitialized")
    }
    
    var apartment: ApartmentWeak?
}

class ApartmentWeak {
    var address: String
    init(address: String) {
        self.address = address
    }
    
    
    // 由于弱引用需要允许它们的值为 nil ，它们一定得是可选类型
    weak var tenant: PersonWeak?
    
    deinit {
        print("ApartmentWeak \(self.address) is being deinitialized")
    }
}


// 这意味着当PersonWeak bill的强引用被设置为nil时, ApartmentWeak对PersonWeak的弱引用tenant自动设置为nil
var bill: PersonWeak?
var unit7C: ApartmentWeak?

bill = PersonWeak(name: "Bill")
unit7C = ApartmentWeak(address: "ApartmentWeak 7C")
bill!.apartment = unit7C
unit7C!.tenant = bill
print("----------destroy bill------------")
// PersonWeak实例依然保持对ApartmentWeak实例的强引用
// 但是ApartmentWeak实例现在对PersonWeak实例是弱引用
// 这意味着当断开bill变量所保持的强引用时，再也没有指向PersonWeak实例的强引用了，由于再也没有指向PersonWeak实例的强引用，该实例会被释放
bill = nil


print("----------destroy unit7C------------")
// 现在只剩下来自unit7C变量对ApartmentWeak实例的强引用。如果打断这个强引用，那么ApartmentWeak实例就再也没有强引用了
unit7C = nil



// 无主引用
// 无主引用假定是永远有值的。因此，无主引用总是被定义为非可选类型
// 场景2: 一个用户可以没有信用卡，一张信用卡必须有持有人
class Customer {
    let name: String
    var card: CreditCard?
    
    init(name: String) {
        self.name = name
    }
    
    deinit {
        print("\(name) is being uninitialized")
    }
}

class CreditCard {
    let number: UInt64
    unowned let customer: Customer
    
    init(number: UInt64, customer: Customer) {
        self.number = number
        self.customer = customer
    }
    
    deinit {
        print("Card #\(self.number) is being uninitialized")
    }
}



var carl: Customer?
carl = Customer(name: "Carl")
carl!.card = CreditCard(number: 314_1414_1732, customer: carl!)

// 现在Customer实例对CreditCard实例有一个强引用，并且CreditCard实例对Customer实例有一个无主引用
// 由于 Customer 的无主引用，当断开 john 变量持有的强引用时，那么就再也没有指向 Customer 实例的强引用了
// 因为不再有 Customer 的强引用，该实例被释放了。其后，再也没有指向 CreditCard 实例的强引用，该实例也随之被释放了
print("----------destroy carl------------")
carl = nil






// 无主引用和隐式展开的可选属性
// 除了两个属性的值都允许为nil和一个属性的值允许为nil，而另一个属性的值不允许为nil的场景
// 还有第三种场景，在这种场景中，两个属性都必须有值，并且初始化完成后永远不会为nil。在这种场景中，需要一个类使用无主属性，而另外一个类使用隐式展开的可选属性

// 场景三: 一个国家必定有首都城市，一个城市必定属于一个国家
class Country {
    let name: String
    var capital: City!
    
    init(name: String, capitalName: String) {
        self.name = name
        self.capital = City(name: capitalName, country: self)
    }
    
    deinit {
        print("Country: \(name) is being uninitialized")
    }
}


class City {
    let name: String
    unowned let country: Country
    
    init(name: String, country: Country) {
        self.name = name
        self.country = country
    }
    
    deinit {
        print("City: \(name) is being uninitialized")
    }
}

var country: Country? = Country(name: "Canada", capitalName: "Ottwa")
print("\(country!.name)'s capital city is called \(country!.capital.name)")

print("----------destroy country------------")
country = nil





// 闭包的循环强引用

class HTMLElement {
    
    let name: String
    let text: String?
    
    lazy var asHTML: () -> String = {
        if let text = self.text {
            return "<\(self.name)>\(text)</\(self.name)>"
        } else {
            return "<\(self.name) />"
        }
    }
    
    init(name: String, text: String? = nil) {
        self.name = name
        self.text = text
    }
    
    deinit {
        print("HTMLElement: \(name) is being deinitialized")
    }
    
}

var paragraph: HTMLElement? = HTMLElement(name: "p", text: "hello, world")
print(paragraph!.asHTML())

// 此时就处把paragraph设置为nil，paragraph曾指向的实例和闭包之间还是强引用
// HTMLElement 实例和它的闭包都不会被释放
paragraph = nil


// Swift通过闭包捕获列表来解决这个问题
// Swift要求在闭包中引用self成员时使用self.someProperty或者self.someMethod 而不只是 someProperty或someMethod）。这有助于提醒可能会一不小心就捕获了self

// 捕获列表中的每一项都由 weak 或 unowned 关键字与类实例的引用（如 self ）或初始化过的变量（如 delegate = self.delegate! ）成对组成。这些项写在方括号中用逗号分开。
// 把捕获列表放在形式参数和返回类型前边，如果它们存在的话


//lazy var someClosure: (Int, String) -> String = {
//    [unowned self, weak delegate = self.delegate!] (index: Int, stringToProcess: String) -> String in
//    // closure body goes here
//}


// 如果闭包没有指明形式参数列表或者返回类型，是因为它们会通过上下文推断，那么就把捕获列表放在关键字 in 前边，闭包最开始的地方
//lazy var someClosure: Void -> String = {
//    [unowned self, weak delegate = self.delegate!] in
//    // closure body goes here
//}



// 弱引用和无主引用
// 在闭包和捕获的实例总是互相引用并且总是同时释放时，将闭包内的捕获定义为无主引用
// 在被捕获的引用可能会变为 nil 时，定义一个弱引用的捕获。弱引用总是可选项，当实例的引用释放时会自动变为 nil 。这使我们可以在闭包体内检查它们是否存在
// 如果被捕获的引用永远不会变为 nil ，应该用无主引用而不是弱引用

class HTMLElementV2 {
    
    let name: String
    let text: String?
    
    lazy var asHTML: () -> String = {
        [unowned self] in
        if let text = self.text {
            return "<\(self.name)>\(text)</\(self.name)>"
        } else {
            return "<\(self.name) />"
        }
    }
    
    init(name: String, text: String? = nil) {
        self.name = name
        self.text = text
    }
    
    deinit {
        print("HTMLElementV2: \(name) is being deinitialized")
    }
}

print("----------destroy paragraph2------------")
var paragraph2: HTMLElementV2? = HTMLElementV2(name: "p", text: "hello ARC")
paragraph2 = nil

print("begin deinit")
