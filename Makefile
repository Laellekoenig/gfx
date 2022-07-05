SDLINC = -I sdl2/include
SDLLINK = -L sdl2/lib -l SDL2-2.0.0
COMP = g++
FLAGS = -g -std=c++17 -pthread

sdl: main.o mesh.o gfx.o linalg.o pch.o
	$(COMP) $(FLAGS) main.o mesh.o gfx.o linalg.o pch.o -o sdl $(SDLLINK)

main.o: main.cpp
	$(COMP) $(FLAGS) -c main.cpp $(SDLINC)

mesh.o: gfx/mesh.cpp gfx/mesh.hpp
	$(COMP) $(FLAGS) -c gfx/mesh.cpp $(SDLINC)

gfx.o: gfx/gfx.cpp gfx/gfx.hpp
	$(COMP) $(FLAGS) -c gfx/gfx.cpp $(SDLINC)

linalg.o: gfx/linalg.cpp gfx/linalg.hpp
	$(COMP) $(FLAGS) -c gfx/linalg.cpp $(SDLINC)

pch.o: gfx/pch.cpp gfx/pch.hpp
	$(COMP) $(FLAGS) -c gfx/pch.cpp

clean:
	rm *.o sdl

run:
	./sdl
