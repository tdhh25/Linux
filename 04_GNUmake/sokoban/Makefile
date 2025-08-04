
objects = main.o game.o map.o player.o\
			render.o

sokoban: $(objects)
	gcc -o sokoban $(objects)

main.o: main.c game.h map.h player.h
#	gcc -c main.c

game.o: game.h map.h player.h render.h
#	gcc -c game.c

map.o: map.h
#	gcc -c map.c

player.o: player.h map.h
#	gcc -c player.c

render.o: render.h map.h
#	gcc -c render.c

.PHONY: clean
clean:
	-rm $(objects) sokoban
