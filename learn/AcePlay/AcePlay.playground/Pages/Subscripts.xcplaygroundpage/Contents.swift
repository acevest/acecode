//: [Previous](@previous)

import Foundation

var str = "Hello, Subscripts"

//: [Next](@next)

// 下标可以定义在类、结构体和枚举中

struct TimesTable {
    let multiplier: Int
 
    // subscript(index: Int) -> Int {
    //      get {
    //          返回一个适当的 Int 类型的值
    //      }
    //      set(newValue) {
    //          执行适当的赋值操作
    //      }
    // }

    // 只读下标实现如下
    subscript(index: Int) -> Int {
        return multiplier * index
    }
}

let sevenTimesTable = TimesTable(multiplier: 7)
print("six times seven is \(sevenTimesTable[6])")



class Matrix {
    let rows: Int
    let cols: Int
    var grid: [Double]
    
    init(rows: Int, cols: Int) {
        self.rows = rows
        self.cols = cols
        grid = Array(repeating: 0.0, count: rows * cols)
    }
    
    func indexIsValid(row: Int, col: Int) -> Bool {
        return row >= 0 && row < rows && col >= 0 && col < cols
    }
    
    subscript(row: Int, col: Int) -> Double {
        get {
            assert(indexIsValid(row: row, col: col))
            return grid[row*cols + col]
        }
        
        set {
            assert(indexIsValid(row: row, col: col))
            grid[row*cols + col] = newValue
        }
    }
    
    var description: String {
        var s : String = ""
        for i in 0..<rows {
            for j in 0..<cols {
                s += "Matrix[\(i), \(j)] = \(grid[i*rows + j]) "
            }
            s += "\n"
        }
        
        return s
    }
}


var matrix = Matrix(rows: 2, cols: 2)

print(matrix.description)
matrix[0, 1] = 1.414
matrix[1, 1] = 1.732
print(matrix.description)