all:
	mkdir -p bin
	g++ src/main.cpp include/box.cpp include/helpers.cpp -I ../SDL3-w64/include -I include -L ../SDL3-w64/lib -w -Wl,-subsystem,windows -lSDL3 -o bin/main.exe
