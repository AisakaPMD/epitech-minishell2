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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#include "benjalib/my.h"
#include "benjalib/my_printf.h"

int my_strindexof(char const *str, char c)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}
