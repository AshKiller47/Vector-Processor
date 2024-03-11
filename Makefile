all: build execute

build:
	g++ -std=c++17 -o bin\vector_processor vector_processor.cpp

execute:
	bin\vector_processor

clean:
	del bin\vector_processor.exe