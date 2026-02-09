/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit for c conversion specifier
*/

#include "printf_internals.h"

int printf_char(printf_render_params_t *params,
    printf_context_t *ctx)
{
    printf_my_putchar(va_arg(ctx->args, int), ctx);
    return 1;
}
