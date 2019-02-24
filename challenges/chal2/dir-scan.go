package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	var files []string
	countFiles := make(map[string]int)

	errPath := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
		files = append(files, path)
		return nil
	})

	if errPath != nil {
		fmt.Println("There was an error with getting the files")
	}

	for _, file := range files {
		info, _ := os.Lstat(file)
		switch mode := info.Mode(); {
		case mode.IsDir():
			countFiles["Directories"]++
		case mode&os.ModeSymlink != 0:
			countFiles["Symbolic links"]++
		case mode&os.ModeTemporary != 0:
			countFiles["Temporary"]++
		default:
			countFiles["Other Files"]++
		}
	}
	fmt.Println("Directory Scanner Tool\n")
	for key, value := range countFiles {
		fmt.Println(key, " : ", value)
	}

	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}
