/*
 * ------------------------------------------------------------------------
 *   File Name: pattern.go
 *      Author: Zhao Yanbai
 *              2015-11-28 20:06:28 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"regexp"
	"strconv"
)

func main() {
	defer fmt.Println("Program Exited...")

	SearchStr := "John: 2578.34 William: 4567.23 Steve: 5632.18"
	Pattern := "[0-9]+.[0-9]+"

	fmt.Println(SearchStr)

	if ok, _ := regexp.Match(Pattern, []byte(SearchStr)); ok {
		fmt.Println("Match Found!")
	}

	re, _ := regexp.Compile(Pattern)
	sa := re.ReplaceAllString(SearchStr, "##.#")
	fmt.Println(sa)

	rfunc := func(s string) string {
		v, _ := strconv.ParseFloat(s, 32)

		// FormatFloat(f float64, fmt byte, prec, bitSize int) string
		// f:		要转换的浮点数
		// fmt:		格式标记(b、e、E、f、g、G)
		// prec:	精度a(数字部分的长度，不包括指数部分)
		// bitSize:	指定浮点类型(32:float32、64:float64)
		//
		// 格式标记
		// 'b' (-ddddp±ddd, 二进制指数)
		// 'e' (-dddde±dd,  十进制指数)
		// 'E' (-ddddE±dd,  十进制指数)
		// 'f' (-ddd.dddd,  没有指数)
		// 'g' ('e':大指数，'f':其它情况)
		// 'G' ('E':大指数，'f':其它情况)
		//
		// 如果格式标记为 'e'，'E'和'f'，则 prec 表示小数点后的数字位数
		// 如果格式标记为 'g'，'G'，则 prec 表示总的数字位数（整数部分+小数部分）

		return "$" + strconv.FormatFloat(v*2, 'f', 2, 32)
	}

	sb := re.ReplaceAllStringFunc(SearchStr, rfunc)
	fmt.Println(sb)
}
