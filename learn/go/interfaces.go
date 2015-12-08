/*
 * ------------------------------------------------------------------------
 *   File Name: interfaces.go
 *      Author: Zhao Yanbai
 *              2015-11-14 17:47:59 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"math"
)

type Shaper interface {
	Area() float64
}

type Square struct {
	slide float64
}

func (s *Square) Area() float64 {
	return s.slide*s.slide
}

type Round struct {
	radius float64
}

func (r *Round) Area() float64 {
	return math.Pi*r.radius*r.radius
}


type Rectangular struct {
	width 	float64
	height	float64
}

func (r *Rectangular) Area() float64 {
	return r.width*r.height
}

func main() {
	defer fmt.Println("Program Exited...")

	sq := Square{12.34}
	rd := new(Round)
	rd.radius = 9.99
	rt := Rectangular{0.6, 0.8}

	var shaper Shaper
	shaper = &sq
	fmt.Println("Square Slide", sq.slide, "Area", shaper.Area())


	// rd is pointer
	shaper = rd
	fmt.Println("Round Radius", rd.radius, "Area", shaper.Area())

	shaper = &rt
	fmt.Println("Rectangular Width", rt.width, "Height", rt.height, "Area", shaper.Area())
}
