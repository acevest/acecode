/*
 * ------------------------------------------------------------------------
 *   File Name: 1.5.go
 *      Author: Zhao Yanbai
 *              2017-06-11 16:09:11 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
//	"fmt"
	"image"
	"image/color"
	"image/gif"
	"io"
	"math"
	"math/rand"
	"os"
)

var palette = []color.Color {
	color.White,
	color.Black,
	color.RGBA{0xFF, 0x00, 0x00, 0xFF},
	color.RGBA{0x00, 0xFF, 0x00, 0xFF},
	color.RGBA{0x00, 0x00, 0xFF, 0xFF},
}

const (
	lineColorIndex = 3
)


func lissajous(out io.Writer) {
	const (
		cycles		= 5
		res			= 0.001
		size		= 100
		nframes		= 128
		delay		= 8		// 80ms
	)

	freq := rand.Float64() * 3.0
	anim := gif.GIF{LoopCount: nframes}
	phase := 0.0

	for i := 0; i<nframes; i++ {
		rect := image.Rect(0, 0, 2*size+1, 2*size+1)
		img := image.NewPaletted(rect, palette)
		for t := 0.0; t<2*math.Pi*cycles; t += res {
			x := math.Sin(t)
			y := math.Sin(t*freq + phase)
			img.SetColorIndex(size+int(x*size+0.5), size+int(y*size+0.5), lineColorIndex)
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
	}

	gif.EncodeAll(out, &anim)
}

func sint(out io.Writer) {
	const (
		cycles		= 5
		res			= 0.001
		size		= 100
		nframes		= 24
		delay		= 8		// 80ms
	)

	anim := gif.GIF{LoopCount: nframes}

	for i := 0; i<nframes; i++ {
		rect := image.Rect(0, 0, 2*size+1, 2*size+1)
		img := image.NewPaletted(rect, palette)

		bgn := float64(i)
		for t := bgn; t<bgn+3.5*math.Pi; t += res {
			x := t
			y := math.Sin(t)
			delta := t - bgn
			colorIndex := uint8(1)
			if delta < math.Pi {
				colorIndex = 2
			} else if delta < 2*math.Pi {
				colorIndex = 3
			} else if delta < 3*math.Pi {
				colorIndex = 4
			}


			img.SetColorIndex(int(x*size/10.0+0.5), size+int(y*size/1.0+0.5), colorIndex)
		}
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
	}

	gif.EncodeAll(out, &anim)
}


func main() {
	//defer fmt.Println("Program Exited...")
	//lissajous(os.Stdout)
	sint(os.Stdout)
}
