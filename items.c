#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "items.h"

// for struct Item:
struct Item *item(char *name, char *description, struct Item *next)
{
    struct Item *newitem = NULL;
    newitem = (struct Item *)malloc(sizeof(struct Item));
    if (newitem == NULL)
        return NULL;

    newitem->name = name;
    newitem->description = description;
    newitem->next = next;
    return newitem;
}

char *item_name(struct Item *item)
{
    return item->name;
}

char *item_description(struct Item *item)
{
    return item->description;
}

struct Item *item_next(struct Item *item)
{
    return item->next;
}

//take out and delete from list:
struct Item *item_take(struct Item **item, char *des)
{
    struct Item *temp = *item;
    struct Item *prev = *item;
    if (temp != NULL && strcmp(temp->name, des) == 0)
    {
        *item = temp->next;
        return temp;
    }
    while (temp != NULL && strcmp(temp->name, des) != 0)
    {
        prev = temp;
        temp = item_next(temp);
    }
    if (temp == NULL)
        return NULL;
    prev->next = temp->next;

    return temp;
}

//search items in list
int search_item(struct Item *item, char des[]){
    struct Item *temp = item;

    while (temp != NULL) 
    {
        if(strcmp(temp->name, des) == 0){
            return 1;
        } 
        temp = item_next(temp);
    }
    return 0;


}

//add the the head of the linked list:
void push(struct Item** head,  struct Item **new_data) 
{ 
    (*new_data)->next = (*head);  
    (*head) = *new_data; 
} 

// this is the helper method to take the substring out:
void sub_strings(char string1[], int len)
{
    char newstr[50];
    int count = 0;
    for (int i = len; i < 100; i++)
    {
        if (string1[i] == '\0')
        {
            newstr[count] = string1[i];
            break;
        }
        newstr[count] = string1[i];
        count++;
    }
    strcpy(string1, newstr);
}