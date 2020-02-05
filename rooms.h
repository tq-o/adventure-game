#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CH_HEAD2
#define CH_HEAD2

//define struct Room:
struct Room
{
    char *description;
    struct Item *items;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Room *up;
    struct Room *down;
};

//for creating struct Room:
struct Room *room(char *description, struct Item *items,
                  struct Room *north, struct Room *south,
                  struct Room *east, struct Room *west,
                  struct Room *up, struct Room *down);
                  
// for connecting the room
void room_exit_north(struct Room *current, struct Room *other);
void room_exit_south(struct Room *current, struct Room *other);
void room_exit_east(struct Room *current, struct Room *other);
void room_exit_west(struct Room *current, struct Room *other);
void room_exit_up(struct Room *current, struct Room *other);
void room_exit_down(struct Room *current, struct Room *other);

#endif