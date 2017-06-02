/*
 * ------------------------------------------------------------------------
 *   File Name: string.go
 *      Author: Zhao Yanbai
 *              2015-11-28 14:44:55 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	defer fmt.Println("Program Exited...")

	interpretString := "这是一个解释型字符串.\n\\n会换行"
	fmt.Println(interpretString)

	nonInterpretString := `这是一个解释型字符串.\n不会换行`
	fmt.Println(nonInterpretString)

	// 纯ASCII字符串可以通过标准索引法来获取 如s[i]
	// 对字符串取地址非法 &s[i]

	var str string = "This is an example of a string. [这是一个中文示例字符串]"
	fmt.Println(strings.HasPrefix(str, "This"))
	fmt.Println(strings.HasSuffix(str, "string"))
	fmt.Println(strings.Contains(str, "example"))
	fmt.Println(strings.LastIndex(str, "example"))
	fmt.Println(strings.IndexRune(str, '中'))
	fmt.Println(strings.Index(str, "hello"))
	fmt.Println(strings.Count(str, "a"))

	str = strings.Replace(str, "example", "示例", -1) // -1表示替换所有
	fmt.Println(str)

	var words []rune = []rune(str)
	for i, v := range words {
		fmt.Printf("[%02d] : %c\n", i, v)
	}

	var repeat string = "Repeat "
	fmt.Println("Repeat:", strings.Repeat(repeat, 10))
	fmt.Println("ToUpper:", strings.ToUpper(repeat))
	fmt.Println("ToLower:", strings.ToLower(repeat))

	str = "    This is a string    "
	fmt.Printf("RawStr:[%s]\n", str)
	fmt.Printf("TrimLeft:[%s]\n", strings.TrimLeft(str, " "))
	fmt.Printf("TrimRight:[%s]\n", strings.TrimRight(str, " "))
	fmt.Printf("TrimSpace:[%s]\n", strings.TrimSpace(str))

	str = "------This is another string---"
	fmt.Printf("RawStr:[%s]\n", str)
	fmt.Printf("Trim:[%s]\n", strings.Trim(str, "--"))

	str = "This-is-a-string-to-be-splited"
	fmt.Printf("RawStr:[%s]\n", str)
	for _, s := range strings.Split(str, "-") {
		fmt.Println(s)
	}

	str = "This is a string to be splited into word by strins.Fields"
	fmt.Printf("RawStr:[%s]\n", str)
	strfields := strings.Fields(str)
	for _, s := range strfields {
		fmt.Println(s)
	}
	fmt.Printf("JoinStr By ':' : [%s]\n", strings.Join(strfields, ":"))

	fmt.Println("strconv Itoa: ", strconv.Itoa(123))
	val, err := strconv.Atoi("321")
	if err == nil {
		fmt.Println("strconv Atoi: ", val)
	}


	fmt.Printf("%q\n", "hello world")	# 输出字符串前后会带双引号
}
