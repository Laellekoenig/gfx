SDLINC = -I /opt/homebrew/Cellar/sdl2/2.0.22/include
SDLLINK = -L /opt/homebrew/Cellar/sdl2/2.0.22/lib -l SDL2-2.0.0
COMP = g++
FLAGS = -g -std=c++17

sdl: main.o mesh.o gfx.o
	$(COMP) $(FLAGS) main.o mesh.o gfx.o -o sdl $(SDLLINK)

main.o: main.cpp
	$(COMP) $(FLAGS) -c main.cpp $(SDLINC)

mesh.o: mesh.cpp mesh.h
	$(COMP) $(FLAGS) -c mesh.cpp $(SDLINC)

gfx.o: gfx.cpp gfx.h
	$(COMP) $(FLAGS) -c gfx.cpp $(SDLINC)

clean:
	rm *.o sdl

run:
	./sdl
