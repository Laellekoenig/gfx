SDLINC = -I /opt/homebrew/Cellar/sdl2/2.0.22/include
SDLLINK = -L /opt/homebrew/Cellar/sdl2/2.0.22/lib -l SDL2-2.0.0
COMP = g++

sdl: main.o mesh.o gfx.o
	$(COMP) -g main.o mesh.o gfx.o -o sdl $(SDLLINK)

main.o: main.cpp
	$(COMP) -g -c main.cpp $(SDLINC)

mesh.o: mesh.cpp mesh.h
	$(COMP) -g -c mesh.cpp $(SDLINC)

gfx.o: gfx.cpp gfx.h
	$(COMP) -g -c gfx.cpp $(SDLINC)

clean:
	rm *.o sdl

run:
	./sdl
