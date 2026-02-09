/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing snprintf logic
*/

#include "printf_internals.h"

int my_snprintf(char *buf, size_t size, char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vsnprintf(buf, size, format, arg);
    va_end(arg);
    return written;
}
