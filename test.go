package main
import "fmt"

func test(a, b int) {
	//defer println("test...")
	println(a/b)
}

func main() {
	var a struct {
		x int `x`
		s string `s`
	}

	var b struct {
		x int
		s string
	}
	//b = a
	fmt.Println(a)
	fmt.Println(b)
}
/*
func main() {
	//a := 10
	//println(a)
	//test(10,0)
	//m := make(map[string]int)
	//m["a"] = 1
	//x, ok := m["b"]
	//println(x, ok)
	//println("a")
	//println("-a")
	type data [2]int;
	var d data = [2]int{1,2}
	fmt.Println(d)
	ca := make(chan int, 2)
	fmt.Println(ca)
	var b chan<- int = ca
	b <- 2
	fmt.Println(b)
}
*/
