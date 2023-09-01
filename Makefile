all:
	g++  src/*.cpp executelib/*.c -I executelib/  -I lib/  -o 42api