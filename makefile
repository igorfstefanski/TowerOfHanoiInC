all: hanoi

hanoi: hanoi.o hanoi_definitions.o primlib.o
	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

hanoi.o: hanoi.c hanoi_declarations.h primlib.h

hanoi_definitions.o: hanoi_definitions.c hanoi_declarations.h primlib.h

clean:
	-rm primlib.o hanoi.o hanoi_definitions.o hanoi
