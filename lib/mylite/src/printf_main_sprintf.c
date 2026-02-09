/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing sprintf logic
*/

#include "printf_internals.h"

int my_sprintf(char *buf, char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vsprintf(buf, format, arg);
    va_end(arg);
    return written;
}
