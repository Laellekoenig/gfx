compile:
	g++ main.cpp `pkg-config --libs --cflags raylib` lib/gfx.cpp lib/mesh.cpp -o gfx
	./gfx
