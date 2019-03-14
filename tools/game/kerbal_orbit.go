/*
 * ------------------------------------------------------------------------
 *   File Name: kerbal_orbit.go
 *      Author: Zhao Yanbai
 *              2019-03-14 17:35:44 星期四 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
	"math"
	"flag"
)

var G = 6.67408E-11

type AstronomicalObject struct {
	mass	float64
	radius	float64
}

var MassMap = map[string] AstronomicalObject {
	"Moho"		: { 2.5263314E21,  250000 },
	"Eve"		: { 1.2243980E23,  700000 },
	"Gilly"		: { 1.2420363E17,   13000 },
	"Kerbin"	: { 5.2915158E22,  600000 },
	"Mun"		: { 9.7599066E20,  200000 },
	"Minmus"	: { 2.6457580E19,   60000 },
	"Duna"		: { 4.5154270E21,  320000 },
	"Ike"		: { 2.7821615E20,  130000 },
	"Dres"		: { 3.2190937E20,  138000 },
	"Jool"		: { 4.2332127E24, 6000000 },
	"Laythe"	: { 2.9397311E22,  500000 },
	"Vall"		: { 3.1087655E21,  300000 },
	"Tylo"		: { 4.2332127E22,  600000 },
	"Bop"		: { 3.7261090E19,   65000 },
	"Eeloo"		: { 1.1149224E21,  210000 },
}

func main() {
	defer fmt.Println("Program Exited...")

	var Cycle float64
	var CelestialName string
	flag.Float64Var(&Cycle, "c", 0.0, "orbital cicle")
	flag.StringVar(&CelestialName, "n", "", "celestial name")

	flag.Parse()

	fmt.Println(CelestialName)

	if CelestialName == "" || Cycle <= 0.0 {
		flag.Usage();
		return
	}

	o, ok := MassMap[CelestialName]
	if !ok {
		fmt.Printf("not valid celestial name\n");
		return
	}

	M := o.mass

	T := Cycle
	a := math.Pow(G*M*T*T/(4*math.Pi*math.Pi),1/3.0)

	fmt.Printf("%10.0f %10.0f\n", a, a-o.radius)
}
