/*
** EPITECH PROJECT, 2025
** C Pool Day 7
** File description:
** String Utils
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += ('a' - 'A');
    }
    return str;
}

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] += ('A' - 'a');
    }
    return str;
}

char *my_strcpy(char *dest, char const *src)
{
    int i;

    for (i = 0; src[i] != 0; i++) {
        dest[i] = src[i];
    }
    dest[i] = 0;
    return dest;
}

char *my_strncpy(char *dest, char const *src, int n)
{
    char ended = 0;

    for (int j = 0; j < n; j++) {
        if (!ended && src[j] == 0)
            ended = 1;
        if (!ended) {
            dest[j] = src[j];
        } else
            dest[j] = 0;
    }
    return dest;
}

char *my_revstr(char *str)
{
    int strlen = my_strlen(str);
    char buf[strlen];

    for (int i = 0; i < strlen; i++) {
        buf[strlen - i - 1] = str[i];
    }
    for (int i = 0; i < strlen; i++) {
        str[i] = buf[i];
    }
    str[strlen] = 0;
    return str;
}
