SRC_FILES = $(wildcard src/*.cpp)
BUILD_FILES = $(patsubst src/%.cpp, build/%.o, ${SRC_FILES})

all: build ${BUILD_FILES}
	g++ -o build/3DMRI ${BUILD_FILES} -lopengl32 -lglfw3dll -lglew32 -Wl,--stack,8388608
clean:
	-rm -rf build/
build/%.o: src/%.cpp
	g++ -std=c++11 -c -g -o $@ $^
build:
	mkdir build
