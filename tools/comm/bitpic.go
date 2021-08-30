/*
 * ------------------------------------------------------------------------
 *   File Name: bitpic.go
 *      Author: Zhao Yanbai
 *              2020-01-19 12:06:24 星期日 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	//"image/jpeg"
	"log"
	"os"
)

func getKey(x, y, divCntX, divCntY int) string {
	xp := x / divCntX
	yp := y / divCntY

	s := fmt.Sprintf("%v_%v", xp, yp)

	return s
}

func main() {
	defer fmt.Println("Program Exited...")

	var src string
	var dst string
	var divCntX int
	var divCntY int
	flag.StringVar(&src, "f", "", "picture file")
	flag.StringVar(&dst, "o", "", "output picture file")
	flag.IntVar(&divCntX, "x", 32, "square width")
	flag.IntVar(&divCntY, "y", 32, "square height")
	flag.Parse()

	raw_pic_reader, err := os.Open(src)
	if err != nil {
		log.Fatal(err)
	}
	defer raw_pic_reader.Close()

	m, _, err := image.Decode(raw_pic_reader)
	if err != nil {
		log.Fatalf("Decode: %v\n", err)
	}

	bounds := m.Bounds()

	img := image.NewRGBA(bounds)

	data := make(map[string][]color.Color)

	for y := bounds.Min.Y; y < bounds.Max.Y; y++ {
		for x := bounds.Min.X; x < bounds.Max.X; x++ {
			color := m.At(x, y)
			key := getKey(x, y, divCntX, divCntY)
			data[key] = append(data[key], color)
		}
	}

	pix := make(map[string]color.Color)
	for k, v := range data {
		var r int64
		var g int64
		var b int64
		var a int64
		for _, c := range v {
			rt, gt, bt, at := c.RGBA()
			r += int64(rt)
			g += int64(gt)
			b += int64(bt)
			a += int64(at)
		}
		t := len(v)
		p := color.NRGBA64{
			uint16(r / int64(t)),
			uint16(g / int64(t)),
			uint16(b / int64(t)),
			uint16(a / int64(t)),
		}

		pix[k] = p
	}

	for y := bounds.Min.Y; y < bounds.Max.Y; y++ {
		for x := bounds.Min.X; x < bounds.Max.X; x++ {
			key := getKey(x, y, divCntX, divCntY)
			color := pix[key]
			img.Set(x, y, color)
		}
	}

	f, err := os.OpenFile(dst, os.O_WRONLY|os.O_CREATE, 0600)
	defer f.Close()

	//jpeg.Encode(f, img, nil)
	png.Encode(f, img)
}
