package main

import (
	"runtime"
	//"time"
)

func main() {
	runtime.GOMAXPROCS(1)
	exit := make(chan struct{})

	go func() {	//任务a
		defer close(exit)

		go func() {	//任务b, 放在此处确保a先执行
			println("b")
		} ()

		for i := 0; i < 4; i++ {
			//time.Sleep(time.Second)
			println("a:", i)

			if (i == 1) {
				//让出当前线程, 调度执行任务b
				runtime.Gosched()
			}
		}
	} ()

	<-exit
}
