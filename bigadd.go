package main

import (
  "fmt"
  "math"
  "sort"
  "strconv"
  "strings"
)

func atoi(c string) int {
  i, _ := strconv.Atoi(c)
  return i
}

func itoa(i int) string {
  return strconv.Itoa(i)
}

func reverse(values []string) []string {
  reversed := make([]string, len(values))
  for i, _ := range values {
    reversed[i] = values[len(values) - i - 1]
  }
  return reversed
}

type BigInt struct {
  values sort.StringSlice
}

func NewBigInt(repr string) BigInt {
  var values []string
  for _, s := range repr {
    values = append(values, string(s))
  }
  return BigInt{reverse(values)}
}

func (i1 BigInt) Add(i2 BigInt) BigInt {
  var bigger BigInt = i1
  var smaller BigInt = i2
  if len(i1.values) < len(i2.values) {
    bigger, smaller = smaller, bigger
  }

  var carry int = 0
  var newValues []string
  for i, _ := range(bigger.values) {
    top := bigger.values[i]
    bottom := "0"
    if i < len(smaller.values) {
      bottom = smaller.values[i]
    }
    sum := NewBigInt(itoa(atoi(top) + atoi(bottom) + carry))
    newValues = append(newValues, sum.values[0])
    if len(sum.values) > 1 {
      carry = 1
    } else {
      carry = 0
    }
  }

  if carry > 0 {
    newValues = append(newValues, "1")
  }

  return BigInt{newValues}
}

func (i1 BigInt) String() string {
  return strings.Join(reverse(i1.values), "")
}

func main() {
  i1 := NewBigInt("1000000000000000000000000000000000000000")
  i2 := NewBigInt("9000000000000000000000000000000000000000")
  i3 := i1.Add(i2)
  fmt.Println(i3)
}
