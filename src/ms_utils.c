/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** MiniShell utils
** Author:
** Amélie Ambleton--Guth
*/

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

void *my_calloc(size_t count, size_t unit_size)
{
    void *ptr = malloc(count * unit_size);

    if (!ptr)
        return NULL;
    for (size_t i = 0; i < count * unit_size; i++)
        ((char *) ptr)[i] = 0;
    return ptr;
}

int my_str_isnumerical(char const *str)
{
    if (!str)
        return 0;
    for (; *str; str++) {
        if ((*str < '0' || *str > '9') && *str != '-')
            return 0;
    }
    return 1;
}
