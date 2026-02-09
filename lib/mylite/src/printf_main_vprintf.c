/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit containing vprintf logic
*/

#include "printf_internals.h"

int my_vprintf(char const *format, va_list arg)
{
    return my_vdprintf(1, format, arg);
}
