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

func isValidRound(sets []Set, maxSet Set) bool {
	for _, set := range sets {
		if set.blue > maxSet.blue || set.green > maxSet.green || set.red > maxSet.red {
			return false
		}
	}
	return true
}

func main() {

	// Read file
	file, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	sum := 0

	maxSet := Set{blue: 14, green: 13, red: 12}
	// Split to lines
	for _, line := range strings.Split(string(file), "\n") {
		arr := strings.Split(line, ":")

		// Game id
		id, _ := strconv.Atoi(strings.Split(arr[0], " ")[1])

		// Game roundStr
		roundStr := arr[1]

		var sets = []Set{}

		// Parse rounds to sets
		for _, setStr := range strings.Split(roundStr, ";") {
			sets = append(sets, parseSet(setStr))
		}

		if isValidRound(sets, maxSet) {
			sum += id
		}

	}

	fmt.Println(sum)
}
