#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CH_HEAD
#define CH_HEAD

// define stuct Item:
struct Item
{
    char *name;
    char *description;
    struct Item *next;
};

// methods to interact with struct Item:
struct Item *item(char *name, char *description, struct Item *next);
char *item_name(struct Item *item);
char *item_description(struct Item *item);
struct Item *item_next(struct Item *item);
//take item out and delete from list:
struct Item *item_take(struct Item **item, char *des);
//search item:
int search_item(struct Item *item, char des[]);
//add to a list:
void push(struct Item** head,  struct Item **new_data);
//take sub string:
void sub_strings(char string1[], int len);
#endif