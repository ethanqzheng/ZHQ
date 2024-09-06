package ch01

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSlice(t *testing.T) {

	sliceChange()
	sliceAppend()
	//deepEqual()
}

// sliceChange slice切片，共享空间的修改，影响原slice的值
func sliceChange() {
	fmt.Println("-------------sliceChange start ------------")
	foo := make([]int, 5)
	foo[3] = 42
	foo[4] = 100
	// foo 值为 [0, 0, 0, 42,100] size:5, cap:5
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	bar := foo[1:4]
	// bar 值为 [0,0,42] size: 3 cap: 4
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	bar[1] = 99
	// bar 值为 [0,99,42] size: 3 cap: 4
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	// foo 值为 [0, 0, 99, 42,100] size:5, cap:5
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	bar[1] = 50
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)
	fmt.Println("-------------sliceChange end ------------")
}

// sliceAppend slice切片，append函数 在空间足够的情况下，不会重新分配，
func sliceAppend() {
	fmt.Println("-------------sliceAppend start ------------")
	foo := make([]int, 5)
	foo[3] = 42
	foo[4] = 100
	// foo 值为 [0, 0, 0, 42,100] size:5, cap:5
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	bar := foo[1:4]
	// bar 值为 [0,0,42] size: 3 cap: 4
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	bar[1] = 99
	// bar 值为 [0,99,42] size: 3 cap: 4
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	// foo 值为 [0, 0, 99, 42,100] size:5, cap:5
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	fmt.Println("--cap 不够用情况下 append--")
	foo = append(foo, 101)
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	bar[1] = 50
	fmt.Println("bar", " \t ", len(bar), " \t ", cap(bar), " \t ", bar)
	fmt.Println("foo", " \t ", len(foo), " \t ", cap(foo), " \t ", foo)

	fmt.Println("-------------sliceAppend end ------------")

}

func deepEqual() {
	v1 := make([]int, 2)
	v2 := make([]int, 2)
	fmt.Println("v1 == v2:", reflect.DeepEqual(v1, v2))
}
