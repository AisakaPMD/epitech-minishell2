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

int my_isnumerical(char c)
{
    return !((c < '0' || c > '9') && c != '-');
}

int my_str_isnumerical(char const *str)
{
    if (!str)
        return 0;
    for (; *str; str++) {
        if (!my_isnumerical(*str))
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

static char is_sign(char c)
{
    return c == '-' || c == '+';
}

static int parse(char const *str, char neg)
{
    int val = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i] != 0 && my_isnum(str[i]); i++)
        val = ((val * 10) + (str[i] - '0')) % 256;
    return neg ? -val : val;
}

int my_getexit(char const *str)
{
    int i;
    char isneg = 0;

    if (!str)
        return 0;
    for (i = 0; str[i] != 0 && is_sign(str[i]); i++) {
        if (str[i] == '-')
            isneg ^= 1;
    }
    return parse(str + i, isneg);
}
