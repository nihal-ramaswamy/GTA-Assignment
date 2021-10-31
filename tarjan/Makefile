FILE = tarjan

all: build
	./${FILE} < input.txt > output.txt

build:
	g++ -std=c++17 -O2 -I ../include/ ${FILE}.cpp -o ${FILE}

clean:
	rm -rf ${FILE} .DS_Store *.dSYM
