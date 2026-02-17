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

#include "benjalib/my_printf.h"

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

int my_strchr(char const *str, char c)
{
    for (; *str; str++) {
        if (*str == c)
            return 1;
    }
    return 0;
}

int error(char const *format, ...)
{
    va_list lst;

    va_start(lst, format);
    my_vdprintf(STDERR_FILENO, format, lst);
    va_end(lst);
    return 84;
}
