all:
	g++ src\main.cpp -I ..\SDL3-w64\include -I ..\SDL3-w64\bin -I include -L ..\SDL3-w64\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL3 -o bin\main.exe