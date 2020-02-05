edit: rooms.o items.o adventure.o
	cc -o adventure rooms.o items.o adventure.o

rooms.o: rooms.c items.h
	cc -c rooms.c

items.o: items.c rooms.h
	cc -c items.c

adventure.o: adventure.c rooms.h items.h
	cc -c adventure.c

clean:
	rm adventure adventure.o rooms.o items.o