/*
 * ------------------------------------------------------------------------
 *   File Name: ksp_planet_transfer_calculator.go
 *      Author: Zhao Yanbai
 *              2017-07-23 10:29:09 Sunday CST
 * Description: 计算 Kerbal Space Program 在天体间轨道转移的相位角
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
	"math"
)

type AstronomicalObject struct {
	name			string
	parent			string
	radius			float64	// 天体半径
	sma				float64	// Semi-major axis 轨道半长轴
	inclination		float64 // 轨道倾角
	eccentricity	float64 // 轨道偏心率,没有使用
	u				float64 // 标准重力参数 u = GM, F=(G*M*m)/(r^2)
	soi				float64	// Sphere of influence 势国作用范围
}

var objects = map[string]AstronomicalObject {
	"Kerbol" : {
		"Kerbol",
		"",
		261600000,
		0,
		0,
		0,
		1.1723328e18,
		math.MaxFloat64,	// 应该是infinity
	},
    "Eve" :
    {
        "Eve",
        "Kerbol",
        700000,
        9832684544,
        2.1,
        0.01,
        8.1717302E12,
        85109365,
    },
	"Duna" :
	{
		"Duna",
		"Kerbol",
		320000,
		20726155264,
		0.06,
		0.051,
		3.0136321e11,
		47921949,
	},
	"Kerbin" :
	{
		"Kerbin",
		"Kerbol",
		600000,
		13599840256,
		0,
		0,
		3.5315984e12,
		84159271,
	},
    "Dress" :
    {
        "Dress",
        "Kerbol",
        138000,
        40839348203,
        5,
        0.145,
        2.1484489e10,
        32832840,
    },
}

func getAstronomicalObjectOrbitalPeriod(sma float64, u float64) float64 {
	return 2*math.Pi*math.Sqrt(math.Pow(sma, 3) / u)
}

func main() {
	defer fmt.Println("Program Exited...")


	// 轨道周期的计算公式为 T=2*Pi*sqrt(sma^3/u)
	// 设源和目标轨道半轴长分别为Rs, Rd
	// 则转移轨道周期为 Tt = 2*Pi*sqrt(((Rs+Rd)/2)^3/u)
	// 则源，目标和平均转移角速度分别为 Ws = 1/Ts, Wd = 1/Td, Wt = 1/Tt
	// 设转移时间为t
	// 则有 t*Wt = Pi   ===> t = Tt*Pi
	// 则有 Wd*t + PhaseAngle = Pi (即经过t时间目标+相位角=霍曼转移经过Pi弧度后会合)
	// ===> (1/Td)*Tt*Pi + PhaseAngle = Pi
	// ===> PhaseAngle = Pi - Tt*Pi/Td 

	aos := objects["Kerbin"]
	aod := objects["Duna"]
	if aos.parent != aod.parent || aos.parent == "" || aod.parent == "" {
		fmt.Println("invalid astronomical object");
		return
	}

	u := objects[aos.parent].u
	Ts := getAstronomicalObjectOrbitalPeriod(aos.sma, u)
	Td := getAstronomicalObjectOrbitalPeriod(aod.sma, u)
	Tt := getAstronomicalObjectOrbitalPeriod((aos.sma+aod.sma)/2, u)

	PhaseAngle := math.Pi - Tt*math.Pi/Td

	fmt.Printf("%.6f %.6f\n", Ts, Td)
	fmt.Printf("phase angle %.2f°\n", PhaseAngle*180/math.Pi);
}
