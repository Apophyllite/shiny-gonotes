//可以在多处使用wait阻塞
package main

import (
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		wg.Wait()
		//time.Sleep(time.Second)
		println("wait exit...")
	} ()

	go func() {
		time.Sleep(time.Second)
		println("go done")
		wg.Done()
	} ()

	wg.Wait()
	println("main exit...")
	time.Sleep(time.Second * 2)
}
