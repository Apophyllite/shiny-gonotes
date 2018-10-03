//
package main

import (
	"math"
	"runtime"
	"sync"
)

//测试目标函数
func count() {
	x := 0
	for i := 0; i < math.MaxUint32; i++ {
		x += i
	}
	println(x)
}

//循环执行
func test(n int) {
	println("test: ", n)
	for i := 0; i < n; i++ {
		count()
	}
}

//并发执行
func test2(n int) {
	println("test2: ", n)
	var wg sync.WaitGroup
	wg.Add(n)

	for i := 0; i < n; i++ {
		go func() {
			count()
			wg.Done()
		} ()
	}

	wg.Wait()
}

func main() {
	//n := runtime.GOMAXPROCS(2)
	n := runtime.GOMAXPROCS(0)
	println("sync procs: ", runtime.GOMAXPROCS(0))
	//test(n)
	test2(n)
}
