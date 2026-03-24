/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** MiniShell utils
** Author:
** Amélie Ambleton--Guth
*/

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "minishell2.h"

char *join_line(list_t *lst)
{
    char *result = NULL;
    size_t len = 0;
    char *tmp;

    for (list_t *local = lst; local; local = local->next) {
        len += strlen(local->data);
    }
    result = calloc(len + 1, sizeof(char));
    if (!result)
        return NULL;
    while (lst) {
        tmp = ll_shift(&lst);
        strcat(result, tmp);
        free(tmp);
    }
    return result;
}

char *expand_paths(char *string, ms_shell_context_t *ctx, ssize_t len)
{
    list_t *lst = NULL;
    ms_parser_t parser = {0};
    size_t start = 0;

    for (int i = 0; i < len && string[i]; i++) {
        if (PARSER_ESCAPING(&parser))
            continue;
        if (string[i] == '~' && (i == 0 || IS_SEPARATOR(string[i - 1]))) {
            ll_push(&lst, strndup(string + start, i - start));
            ll_push(&lst, strdup(ms_get_env_value("HOME", ctx, 1)));
            start = i + 1;
        }
    }
    ll_push(&lst, strndup(string + start, len - start));
    return join_line(lst);
}
