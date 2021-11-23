/*
 * ------------------------------------------------------------------------
 *   File Name: abstract_factory_test.go
 *      Author: Zhao Yanbai
 *              2021-11-23 11:37:13 Tuesday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package abstract_factory

import "testing"
import "log"

func Test(t *testing.T) {

	var factorys = []Factory{
		&CarFactory{},
		&ComputerFactory{},
		&GameFactory{},
	}

	var factory Factory
	var product Product

	for _, factory = range factorys {
		product = factory.CreateProduct()
		log.Printf("%v", product.Label())
	}

}
