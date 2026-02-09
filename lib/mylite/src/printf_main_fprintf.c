/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing fprintf logic
*/

#include "printf_internals.h"

int my_fprintf(FILE *stream, char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vfprintf(stream, format, arg);
    va_end(arg);
    return written;
}
