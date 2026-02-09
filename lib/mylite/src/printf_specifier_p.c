/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit for p conversion specifier
*/

#include "printf_internals.h"

int printf_ptr(printf_render_params_t *params, printf_context_t *ctx)
{
    void *ptr = va_arg(ctx->args, void *);

    if (ptr == NULL)
        return printf_my_putstr("(nil)", ctx);
    printf_my_putstr("0x", ctx);
    return printf_my_big_putnbr_base((unsigned long long) ptr,
        "0123456789abcdef", ctx) + 2;
}
