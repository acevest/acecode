/*
 * ------------------------------------------------------------------------
 *   File Name: u8g2_chinese_font_maker.go
 *      Author: Zhao Yanbai
 *              2018-05-21 11:36:14 Monday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	"fmt"
)

var words = []string{
	//"℃、·、♡、♥、‰、‱、•、←、↑、→、↓、↖、↗、↘、↙、☂、",
	//"▲、△、▶、▷、▼、▽、◀、◁",
	//"：，。；“”？！",
	"°",
	"温度、湿度、压力、强度、浓度、高度、深度、长度、厚度、弧度、速度、角速度、仰角、倾角",
	"土壤、水分、空气、毒气、天然气、液体",
	"次数、计数器、循环",
	"强中弱",
	"车、船",
	"太阳、月亮",
	"接收、发送、处理、等待、心跳、探测、启动、退出、运行、重启、进出、收发包、编解码",
	"占比、比率、比例、百分比",
	"每个十百千万亿兆厘毫微纳皮",
	"安培、伏特、欧姆、法拉、焦耳、赫兹、牛顿、瓦特、亨利、库伦、字节、米、秒、帕斯卡、特斯拉、开尔文、克、分钟、时、日、月、年、世纪、星期",
	"零一二三四五六七八九十",
	"传感器、系统、网络、运行时间、故障、程序、进程、已经、尚未、成功、失败、正常、异常、误差、累积、偏移",
	"电压、电流、电阻、信号",
	"风、霜、雨、雪、雷、光、电、水、气",
	"长、宽、高、时间、体积、压强、平方、立方、流量、含水量",
	"上中下内外前后左右横竖斜东西南北偏、方向、方位",
	"家庭、客厅、卧室、主卧、次卧、阳台、厕所、厨房、花园、泳池、草坪、窗户、门、灯",
	"春夏秋冬、立春、雨水、惊蛰、春分、清明、谷雨、立夏、小满、芒种、夏至、小暑、大暑、立秋、处暑、白露、秋分、寒露、霜降、立冬、小雪、大雪、冬至、小寒、大寒",
	"赵彦柏",
}

func getSingleCharacterFromWords(words []string) string {
	s := ""
	var m = make(map[string]interface{})
	for _, word := range words {
		for _, char := range word {
			m[string(char)] = 0
		}
	}

	for k, _ := range m {
		s += k
	}

	return s
}

// cd u8g2/tools/font/bdfconv
// ./bdfconv -v ../bdf/unifont.bdf -b 0 -f 1 -M self.map -d ../bdf/7x13.bdf -n u8g2_font_unifont_t_acevest -o u8g2_font_unifont_t_acevest.c

func main() {

	chars := getSingleCharacterFromWords(words)
	//fmt.Println(chars)

	fmt.Printf("0-128,\n");

	for _, char := range chars {
		//fmt.Printf("\\u%04X %q\n", char, char)
		fmt.Printf("$%04X,\n", char)
	}

}
