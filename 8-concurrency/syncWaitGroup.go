package main
import (
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup

	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()

			// wg.Add(1)	来不及设置 Wait就退出 故须在goroutine外设置Add
			time.Sleep(time.Second)
			println("goroutine: ", id , " done.")
		} (i)
	}

	println("main...")
	wg.Wait()
	println("main exit...")
}
