/*
 * ------------------------------------------------------------------------
 *   File Name: abstract_factory.go
 *      Author: Zhao Yanbai
 *              2021-11-23 11:27:27 Tuesday CST
 * Description: 抽象工厂模式
 * ------------------------------------------------------------------------
 */

package abstract_factory

type Product interface {
	Label() string
}

type Factory interface {
	CreateProduct() Product
}

type CarFactory struct{}
type ComputerFactory struct{}
type GameFactory struct{}

func (f CarFactory) CreateProduct() Product {
	return &Car{}
}

func (f ComputerFactory) CreateProduct() Product {
	return &Computer{}
}

func (f GameFactory) CreateProduct() Product {
	return &Game{}
}

type Car struct{}
type Computer struct{}
type Game struct{}

func (c Car) Label() string {
	return "car"
}

func (c Computer) Label() string {
	return "computer"
}

func (g Game) Label() string {
	return "game"
}
