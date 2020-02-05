#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"

int main(void)
{

    //item: when the player want to interact with an item, that person must type in the name (the name variable of struct Item)
    //The purpose of these items is to distract and confuse players since they just need 1 item to win.
    //a broom:
    struct Item *broom = item("a broom\n", "a long broom", NULL);
    //a key:
    struct Item *key = item("a small key\n", "a small blue key", NULL);
    //a torch:
    struct Item *torch = item("a torch\n", "a medium black portable flash light", NULL);
    //a hammer:
    struct Item *hammer = item("a big hammer\n", "a steel, heavy hammer", NULL);
    //a jacket:
    struct Item *jacket = item("an invisible jacket\n", "a jacket that helps you invisisble", NULL);
    //a watch:
    struct Item *watch = item("a watch\n", "a broken gold watch", NULL);
    //a photo:
    struct Item *photo = item("a photo\n", "a small polaroid family photo", NULL);

    //The room map will look something like this:
    //     W
    // S  -|-  N
    //     E
    // doll house                  garage
    // |                             |    (go up)       (go up)
    // yard <-------> corridor ---> closet<------->stairs<----> master room <-----> small bedroom 3
    // |                             |                            |                  |
    // |                             |                            |                 hall
    // |                             |                            |                  |
    // |                           toilet                   small bedroom 1 <--> small bedroom 2
    // current starting place
    //1st room:
    struct Room *yard = room("It's a big, green with tall and short grass unevenly distributed, it seems like not being cared for a long time", NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    //2nd room:
    struct Room *dollhouse = room("It's a medium-size white doll house which seems pretty new", key, NULL, NULL, yard, NULL, NULL, NULL);
    //3rd room:
    struct Room *corridor = room("You are now on a long corridor covered with premium marbles", NULL, NULL, yard, NULL, NULL, NULL, NULL);
    //4th room:
    struct Room *closet = room("This is a grand closet with four doors. It looks so dark, you could not see anything", jacket, NULL, corridor, NULL, NULL, NULL, NULL);
    //5th room:
    struct Room *toilet = room("This toilet looks weirdly clean", watch, NULL, NULL, NULL, closet, NULL, NULL);
    //6th room:
    struct Room *garage = room("The garage is so dirty", torch, NULL, NULL, closet, NULL, NULL, NULL);
    //stairs:
    struct Room *stair = room("The stair is so dark, we should use some light source", NULL, NULL, NULL, NULL, NULL, NULL, closet);
    //7th room:
    struct Room *masterroom = room("This is the master bedroom", NULL, NULL, NULL, NULL, NULL, NULL, stair);
    //8th room:
    struct Room *smallroom1 = room("This is the first small bedroom", key, NULL, NULL, NULL, masterroom, NULL, NULL);
    //9th room:
    struct Room *smallroom2 = room("This is the second small bedroom", broom, NULL, smallroom1, NULL, NULL, NULL, NULL);
    //Hall:
    struct Room *hall = room("This is the hall", NULL, NULL, NULL, smallroom2, NULL, NULL, NULL);
    //10th room:
    struct Room *smallroom3 = room("This is the third small bedroom", hammer, NULL, masterroom, hall, NULL, NULL, NULL);
    //set room, and the player can go back by going in opposite direction:
    room_exit_west(yard, dollhouse);
    room_exit_north(yard, corridor);
    room_exit_north(corridor, closet);
    room_exit_east(closet, toilet);
    room_exit_west(closet, garage);
    room_exit_up(closet, stair);
    room_exit_up(stair, masterroom);
    room_exit_east(masterroom, smallroom1);
    room_exit_north(smallroom1, smallroom2);
    room_exit_west(smallroom2, hall);
    room_exit_west(hall, smallroom3);

    //this is the linked list for user item (inventory):
    struct Item *user_item = item("User Item List", "Total List", NULL);
    //this is the  copy of the linked list for user item so that we can maintain the head:
    struct Item *copy_user_item = user_item;
    //set first position at yard.
    struct Room *cur = yard;
    //let the player input their name:
    char name[50];
    //condition for the main playing loop, if equals 1 -> win!
    _Bool win = 0;
    //instruction:
    //get name of the player:
    printf("What's your character name?: ");
    fgets(name, 50, stdin);
    printf("______________\n");
    printf("Hi %s", name);
    printf("Welcome to the adventure game. Right now, you are in the room with an injured man on the bed. ");
    printf("He asked you to find some pieces of his memories so that he can recover and remember the accident he had. ");
    printf("The only think he remembers wa the place that the accident happens and there was a cam recorder recording it.\n");
    printf("* To go to any direction, type go DIRECTION, DIRECTION needs to be north, south, east, west, up, down ,and be typed in uncapitalized.\n");
    printf("* To take any item, type take ITEM, ITEM needs to be in the room, can only be commanded when the game asked to, and be typed in uncapitalized.\n");
    printf("* To use an item, type use ITEM, it can only be used when the game asked to, and be typed in uncapitalized.\n");
    printf("* To drop an item, type drop ITEM, it is typed in uncapitalized.\n");
    printf("* To see the room you are in, type: look\n");
    printf("Now, let's start the game, you moved to a big, green garden with tall and short grass unevenly distributed, it seems like not being cared for a long time\n");

    //main loop of the game:
    while (win == 0)
    {
        //check if the player enter valid commands.
        _Bool valid1 = 0;
        while (valid1 == 0)
        {
            char choose[50];
            printf("______________\n");
            printf("Please enter a command: ");
            fgets(choose, 50, stdin);

            //north:
            if (strncmp(choose, "go north\n", sizeof(choose)) == 0)
            {
                if (cur->north != NULL)
                {
                    cur = cur->north;
                    valid1 = 1;
                    break;
                }
                else if (cur->north == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //south:
            else if (strncmp(choose, "go south\n", sizeof(choose)) == 0)
            {
                if (cur->south != NULL)
                {
                    cur = cur->south;
                    valid1 = 1;
                    break;
                }
                else if (cur->south == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //west:
            else if (strncmp(choose, "go west\n", sizeof(choose)) == 0)
            {
                if (cur->west != NULL)
                {
                    cur = cur->west;
                    valid1 = 1;
                    break;
                }
                else if (cur->west == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //east:
            else if (strncmp(choose, "go east\n", sizeof(choose)) == 0)
            {
                if (cur->east != NULL)
                {
                    cur = cur->east;
                    valid1 = 1;
                    break;
                }
                else if (cur->east == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //up:
            else if (strncmp(choose, "go up\n", sizeof(choose)) == 0)
            {
                if (cur->up != NULL)
                {
                    cur = cur->up;
                    valid1 = 1;
                    break;
                }
                else if (cur->up == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //down:
            else if (strncmp(choose, "go down\n", sizeof(choose)) == 0)
            {
                if (cur->down != NULL)
                {
                    cur = cur->down;
                    valid1 = 1;
                    break;
                }
                else if (cur->down == NULL)
                    printf("Sorry, you can not go there\n");
            }

            //look at the room:
            else if (strncmp(choose, "look\n", sizeof(choose)) == 0)
                printf("%s\n", cur->description);

            //drop items:
            else if (strstr(choose, "drop"))
            {
                sub_strings(choose, 5);
                if (search_item(user_item, choose) == 1)
                {
                    //delete from the current user inventory:
                    struct Item *to_push = item_take(&user_item, choose);
                    printf("You have successfully dropped %s\n", to_push->name);
                    push(&cur->items, &to_push);
                }

                //if does not have that item:
                else
                    printf("Sorry, it seems like you do not have it yet.\n");
                break;
            }

            else if (strncmp(choose, "out\n", sizeof(choose)) == 0)
                exit(1);

            //if invalid typing in:
            else
                printf("Sorry, you cannot do it here\n");
        }
        //room state:
        printf("%s\n", cur->description);

        //take item:
        if (cur->items != NULL)
        {
            struct Item *list1 = cur->items;
            printf("This room has: ");
            while (list1 != NULL)
            {
                printf("%s", list1->name);
                list1 = item_next(list1);
            }
            free(list1);

            _Bool take_loop = 0;
            while (take_loop == 0 && cur->items != NULL)
            {
                char pick_item;
                //request to take item (yes or no)
                printf("______________\n");
                printf("Do you want to take any item here (y or n)?: ");
                scanf("%c", &pick_item);
                getchar();

                //if yes:
                if (pick_item == 'y')
                {

                    printf("What do you want to pick? ");

                    char *to_compare;
                    size_t size = 100;
                    to_compare = (char *)malloc(size * sizeof(char));
                    if (to_compare == NULL)
                        return 0;
                    size_t to_compare2 = getline(&to_compare, &size, stdin);
                    sub_strings(to_compare, 5);

                    //if valid item, add to inventory:
                    if (strcmp(cur->items->name, to_compare) == 0)
                    {
                        copy_user_item->next = cur->items;
                        item_take(&cur->items, to_compare);
                        printf("You successfully picked %s", to_compare);
                    }
                    copy_user_item = copy_user_item->next;
                }
                else if (pick_item == 'n')
                    break;
            }
        }

        //these are the two special rooms: stair and closet which allow the user to change state of them if that person has a torch
        if (cur == stair || cur == closet)
        {
            char check1;
            _Bool pass1 = 0;
            char pick_items[100];

            printf("This place seems so dark. Do you want to use A TORCH here(please type full use command)?\n");
            printf("What do you say? ");

            char *to_compare2;
            size_t size = 100;
            to_compare2 = (char *)malloc(size * sizeof(char));
            if (to_compare2 == NULL)
                return 0;
            size_t to_compare3 = getline(&to_compare2, &size, stdin);
            sub_strings(to_compare2, 4);

            if (strcmp(to_compare2, "a torch\n") == 0)
            {
                //check if the player has a torch:
                if (search_item(user_item, "a torch\n") == 1)
                {
                    printf("The area around you is lit up\n");
                    if (cur == stair)
                        stair->description = "The stair area around you is lit up";
                    else if (cur == closet)
                        closet->description = "The closet area around you is lit up";
                    pass1 = 1;
                }
                else
                    printf("Sorry, you do not have a torch with you now to light this room up.\n");
                free(to_compare2);
            }
        }

        //the hall is where the player can unveil the secret and win the game by breaking the wall with a big hammer:
        if (cur == hall)
        {
            //check if the player has a big hammer:
            if (search_item(user_item, "a big hammer\n") == 1)
            {
                printf("There is a big crack on the and it seems suspicious. The hammer you are having might help to break it. Do you want to use it(y or n)?: ");
                char check2;
                scanf("%c", &check2);
                getchar();
                if (check2 == 'y')
                {
                    printf("You are crashing down the wall and you found a video recorder. You decided to open it and saw the whole story of how the man got the accident in this mansion.\n");
                    printf("You are about to bring it back to the man, but he is not there anymore. Noone knows.\n");
                    printf("But you finished the game. YOU WIN!");
                    win = 1;
                    break;
                }
            }
            // if does not have:
            else
                printf("There is a big crack on the and it seems suspicious. You need something strong, let's say oh, a hammer to break it. Too bad, you do not have it now with you. You can find it somewhere else.\n");
        }
    }
    free(yard);
    free(dollhouse);
    free(corridor);
    free(closet);
    free(toilet);
    free(garage);
    free(stair);
    free(masterroom);
    free(smallroom1);
    free(smallroom2);
    free(smallroom3);
    free(hall);
    free(broom);
    free(key);
    free(torch);
    free(hammer);
    free(jacket);
    free(watch);
    free(photo);
}
