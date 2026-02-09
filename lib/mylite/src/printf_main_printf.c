/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing printf logic
*/

#include "printf_internals.h"

int my_printf(char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vprintf(format, arg);
    va_end(arg);
    return written;
}
