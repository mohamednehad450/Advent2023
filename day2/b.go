package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Set struct {
	blue  int
	red   int
	green int
}

func parseSet(str string) Set {
	set := Set{}
	for _, setStr := range strings.Split(str, ",") {
		arr := strings.Split(setStr, " ")
		count, err := strconv.Atoi(arr[1])
		if err != nil {
			log.Fatal(err)
		}
		color := arr[2]
		switch color {
		case "green":
			set.green = count
		case "red":
			set.red = count
		case "blue":
			set.blue = count
		}
	}
	return set
}

func main() {

	// Read file
	file, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	sum := 0

	// Split to lines
	for _, line := range strings.Split(string(file), "\n") {

		// Game roundStr
		roundStr := strings.Split(line, ":")[1]

		var minSet = Set{}

		// Parse rounds to sets
		for _, setStr := range strings.Split(roundStr, ";") {
			set := parseSet(setStr)
			minSet.blue = max(minSet.blue, set.blue)
			minSet.red = max(minSet.red, set.red)
			minSet.green = max(minSet.green, set.green)
		}

		sum += minSet.blue * minSet.green * minSet.red

	}

	fmt.Println(sum)
}
