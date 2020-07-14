/*
 * ------------------------------------------------------------------------
 *   File Name: time_fmt_trans.go
 *      Author: Zhao Yanbai
 *              2020-07-14 16:47:39 星期二 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"time"
)

func main() {
	defer fmt.Println("Program Exited...")

	{
		// 时间转时间戳
		now := time.Now()
		timestamp := now.Unix()
		fmt.Println("当前时间转换到时间戳:", timestamp)
	}

	{
		// 时间戳转时间
		timestamp := time.Now().Unix()
		now := time.Unix(timestamp, 0)
		fmt.Println("当前时间戳转换到时间:", now)
	}

	{
		// 时间格式化成字符串
		str := ""
		now := time.Now()

		str = now.Format("2006-01-02 03:04:05")
		fmt.Println("时间格式化成字符串 12小时制:", str)

		str = now.Format("2006-01-02 15:04:05")
		fmt.Println("时间格式化成字符串 24小时制:", str)
	}

	{
		type TimeFmt struct {
			tip string
			fmt string
		}

		var timefmts = []TimeFmt{
			{"ANSIC", time.ANSIC},
			{"UnixDate", time.UnixDate},
			{"RubyDate", time.RubyDate},
			{"RFC822", time.RFC822},
			{"RFC822Z", time.RFC822Z},
			{"RFC850", time.RFC850},
			{"RFC1123", time.RFC1123},
			{"RFC1123Z", time.RFC1123Z},
			{"RFC3339", time.RFC3339},
			{"RFC3339Nano", time.RFC3339Nano},
			{"Kitchen", time.Kitchen},
			{"Stamp", time.Stamp},
			{"StampMilli", time.StampMilli},
			{"StampMicro", time.StampMicro},
			{"StampNano", time.StampNano},
		}

		now := time.Now()
		for _, f := range timefmts {
			fmt.Printf("时间格式化成 %-14s: %s\n", f.tip, now.Format(f.fmt))
		}
	}

	{
		// 时间字符串转换成时间
		str := ""
		const TIME_LAYOUT = "2006-01-02 15:04:05"
		str = time.Now().Format(TIME_LAYOUT)
		now, _ := time.ParseInLocation(TIME_LAYOUT, str, time.Local)
		fmt.Println("时间字符串: ", str, " 转换成本地时间: ", now)
	}

}
