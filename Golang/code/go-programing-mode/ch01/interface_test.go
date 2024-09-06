package ch01

import (
	"fmt"
	"testing"
)

type Country struct {
	Name string
	city City
}

type City struct {
	Name string
}

func (c Country) PrintName() {
	fmt.Println("Country Name: ", c.Name, c.city.Name)
}

func (c City) PrintName() {
	fmt.Println("City Name: ", c.Name)
}

type Print interface {
	PrintName()
}

func TestPrint(t *testing.T) {
	city := City{
		Name: "Hubei",
	}

	country := Country{
		Name: "China",
		city: city,
	}

	country.PrintName()
	city.PrintName()
}
