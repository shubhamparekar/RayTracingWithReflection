compile: build run

build:
	g++ ./src/main.cpp -o ./out/RayTracingWithReflection.exe -lSDL3

run:
	./out/RayTracingWithReflection.exe