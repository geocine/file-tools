package main

import (
	"bufio"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"os"
)

func main() {
	extension := flag.String("ext", "wmv", "File extension")
	list := flag.String("list", "list.txt", "List to seed the files")
	flag.Parse()

	file, err := os.Open(*list)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println(lines[0])

	for i := 0; i < len(lines); i++ {
		fileName := fmt.Sprintf("%02d - %s.%s", i+1, lines[i], *extension)
		fmt.Println(fileName)
		err := ioutil.WriteFile(fileName, []byte(""), 0755)
		if err != nil {
			fmt.Printf("Unable to write file: %v", err)
		}
	}

}
