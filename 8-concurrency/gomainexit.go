//无论哪一层, goexit可以直接终止整个调用堆栈
//return 仅退出当前函数
//os.Exit() 可终止进程, 不会执行延迟调用
package main

import (
	"time"
	"runtime"
	"fmt"
	"os"
)

func main() {
	defer func() {
		time.Sleep(time.Second)
		println("defer...")
	} ()
	for i := 0; i < 2; i ++ {
		go func (x int) {
			for n := 0; n < 2; n++ {
				fmt.Printf("%c: %d\n", 'a'+x, n)
				time.Sleep(time.Millisecond)
			}
		} (i)
	}

	os.Exit(1) //os.Exit()终止进程, 不会执行defer
	runtime.Goexit() //main 中调用goexit 会等待所有任务结束 然后进程直接崩溃
	println("main exit...")
}
