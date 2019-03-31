package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"sort"
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

	dirname := "." + string(filepath.Separator)

	d, err := os.Open(dirname)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer d.Close()

	files, err := d.Readdir(-1)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	var linesToRename []string
	for _, file := range files {
		if file.Mode().IsRegular() {
			if filepath.Ext(file.Name()) == ("." + *extension) {
				linesToRename = append(linesToRename, file.Name())
			}
		}
	}

	sort.Strings(linesToRename)

	for i := 0; i < len(linesToRename); i++ {
		fileName := fmt.Sprintf("%02d - %s.%s", i+1, lines[i], *extension)
		fmt.Printf("%s -> %s\n", linesToRename[i], fileName)
		err := os.Rename(linesToRename[i], fileName)
		if err != nil {
			log.Fatal(err)
		}
	}

}
