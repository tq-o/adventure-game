#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rooms.h"

//for struct Room:
struct Room *room(char *description, struct Item *items,
                  struct Room *north, struct Room *south,
                  struct Room *east, struct Room *west,
                  struct Room *up, struct Room *down)
{
    struct Room *newroom = NULL;
    newroom = (struct Room *)malloc(sizeof(struct Room));
    if (newroom == NULL)
        return NULL;

    newroom->description = description;
    newroom->items = items;
    newroom->north = north;
    newroom->south = south;
    newroom->east = east;
    newroom->west = west;
    newroom->up = up;
    newroom->down = down;
    return newroom;
}

//connect the room:
void room_exit_north(struct Room *current, struct Room *other)
{
    current->north = other;
}

void room_exit_south(struct Room *current, struct Room *other)
{
    current->south = other;
}

void room_exit_east(struct Room *current, struct Room *other)
{
    current->east = other;
}

void room_exit_west(struct Room *current, struct Room *other)
{
    current->west = other;
}

void room_exit_up(struct Room *current, struct Room *other)
{
    current->up = other;
}

void room_exit_down(struct Room *current, struct Room *other)
{
    current->down = other;
}
