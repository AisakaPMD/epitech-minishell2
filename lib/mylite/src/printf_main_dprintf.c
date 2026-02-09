/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing dprintf logic
*/

#include "printf_internals.h"

int my_dprintf(int fd, char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vdprintf(fd, format, arg);
    va_end(arg);
    return written;
}
