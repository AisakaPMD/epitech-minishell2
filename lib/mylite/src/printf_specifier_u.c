/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit for u conversion specifier
*/

#include "printf_internals.h"

int printf_unsigned(printf_render_params_t *params,
    printf_context_t *ctx)
{
    return printf_print_unsigned(
        printf_get_sized_uint(ctx->args, params->length_modifier),
        ctx, "0123456789", params->precision);
}
