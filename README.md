# gommseg

## Description

gommseg is a go wrap for libmmseg: http://www.coreseek.cn/opensource/mmseg/

## Installation

### Compile & Install libmmseg
	
	wget http://www.coreseek.cn/uploads/csft/3.2/mmseg-3.2.14.tar.gz
	tar zxvf mmseg-3.2.14.tar.gz
	cd mmseg-3.2.14
	./bootstrap
	./configure
	make && make install

### Generate libgommseg.so (C wrap for libmmseg)
	
	cd <GOPATH>/src
	git clone https://github.com/hongruiqi/gommseg
	cd gommseg
	./make.bash


### Compile && Install gommseg

	go install
	
## Usage

### Example
	package main

	import (
		"fmt"
		"gommseg"
	)

	func main() {
		err := mmseg.Init("/usr/local/etc") // path for dict & config file
		if err!=nil {
			panic(err)
		}
		segments, err := mmseg.Segment("研究生命起源")
		if err!=nil {
			panic(err)
		}
		fmt.Println(segments)
	}

### Compile

	go build

then copy libgommseg.so to the system library path.

or

	go build -ldflags="r ."

then copy libgommseg.so to the working directory.

## License

MIT: http://www.opensource.org/licenses/mit-license.php
