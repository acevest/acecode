package main

import (
	"fmt"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %g\n", float64(e))
}

func Sqrt(x float64) (float64, error) {
	z := 1.0
	if x >= 0 {
		for i := 0; i < 10; i++ {
			z = z - (z*z-x)/(2*z)
		}
	} else {
		return 0, ErrNegativeSqrt(x)
	}
	return z, nil
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}
