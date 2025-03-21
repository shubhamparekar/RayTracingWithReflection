compile: build run

build:
	g++ ./src/main.cpp -o ./out/RayTracing.exe -lSDL3

run:
	./out/RayTracing.exe