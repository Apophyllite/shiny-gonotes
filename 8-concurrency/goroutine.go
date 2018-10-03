package main

import (
	"time"
)

var c int

func counter() int {
	c++
	return c
}

func main() {
	a := 100

	go func(x, y int) {
		time.Sleep(time.Second)		//在main之后计算
		println("go:", x, y)   //go: 100, 1
	} (a, counter())   //立即计算 并复制参数

	a += 100
	println("main:", a, counter())	//main: 200, 2

	time.Sleep(time.Second * 3)
}
