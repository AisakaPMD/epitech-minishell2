/*
** EPITECH PROJECT, 2025
** Linked Lists Lib
** File description:
** Functions adding resources to a linked list
** Author:
** Amélie Ambleton--Guth
*/

#include <stdlib.h>

#include "../include/linked_list.h"

int ll_push(list_t **list, void *data)
{
    int index = 0;

    if (!list)
        return -1;
    for (; *list; index++) {
        list = &(*list)->next;
    }
    *list = malloc(sizeof(list_t));
    if (!*list)
        return -1;
    (*list)->data = data;
    (*list)->next = NULL;
    return index;
}

void ll_unshift(list_t **list, void *data)
{
    list_t *new_list;

    if (!list)
        return;
    new_list = *list;
    *list = malloc(sizeof(list_t));
    if (!*list)
        return;
    (*list)->data = data;
    (*list)->next = new_list;
}

void ll_insert(list_t **list, int index, void *data)
{
    if (!list || index < 0)
        return;
    while (index > 0) {
        index--;
        if (!*list)
            return;
        list = &(*list)->next;
    }
    ll_unshift(list, data);
}
