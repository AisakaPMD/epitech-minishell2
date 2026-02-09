/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit for m conversion specifier
*/

#include <errno.h>
#include <string.h>

#include "printf_internals.h"

int printf_merror(printf_render_params_t *params,
    printf_context_t *ctx)
{
    return printf_my_putstr("The subject doesn't allow us to"
        " specify the error details", ctx);
}
