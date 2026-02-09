/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** Translation unit for s conversion specifier
*/

#include "printf_internals.h"

int printf_str(printf_render_params_t *params, printf_context_t *ctx)
{
    char const *str = va_arg(ctx->args, char *);

    if ((params->precision < 0 || params->precision >= 6) && str == NULL)
        return printf_my_putstr("(null)", ctx);
    if (str == NULL)
        return 0;
    if (params->precision >= 0)
        return printf_my_putstrn(str, params->precision, ctx);
    return printf_my_putstr(str, ctx);
}
