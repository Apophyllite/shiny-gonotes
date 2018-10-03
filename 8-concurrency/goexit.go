//goexit立即终止当前任务, 确保注册的延迟调用会执行
//不影响其他并发任务 不会引发panic
package main

import (
	"runtime"
	"time"
)

func main() {
	exit := make(chan struct{})

	go func() {
		defer close(exit)
		defer println("a")

		func() {
			defer func() {
				println("b", recover() == nil)
			} ()

			go func() {
				println("e")
				time.Sleep(time.Second * 3)
				println("e done...")
			} ()

			func() {
				println("c")
				runtime.Goexit()
				println("c done...")
			} ()

			println("b done.")	//不会执行
		} ()

		println("a done.")	//不会执行
	} ()
	<-exit
	time.Sleep(time.Second * 3)
	println("main exit...")
}
