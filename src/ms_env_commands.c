/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** MiniShell translation unit
** containing commands related
** to env manipulation
** Author:
** Amélie Ambleton--Guth
** February 2026
*/

#include "minishell1.h"

int ms_env_unset(char **args, ms_shell_context_t *context)
{
    if (!args || !args[0]) {
        my_dprintf(2, "unsetenv: Too few arguments.\n");
        return 1;
    }
    if (args[1]) {
        my_dprintf(2, "unsetenv: Too many arguments.\n");
        return 1;
    }
    ms_unset_env_value(args[0], context);
    return 0;
}

int ms_env_show(char **args, ms_shell_context_t *context)
{
    list_t *lst = context->env;
    ms_env_entry_t *entry;

    if (args && args[0]) {
        my_dprintf(2, "env: Too many arguments.\n");
        return 1;
    }
    while (lst) {
        entry = lst->data;
        my_printf("%s=%s\n", entry->key, entry->value);
        lst = lst->next;
    }
    return 0;
}

static int ms_valid_envname(char *key)
{
    if (!my_isalpha(key[0]))
        return error("setenv: Variable name must begin with a letter.\n");
    for (int i = 0; key[i]; i++)
        if (key[i] < 'A' || key[i] > 'Z' &&
            key[i] < 'a' || key[i] > 'z' &&
            key[i] != '_' && key[i] != '.')
            return error("setenv: Variable name must contain "
                "alphanumeric characters.\n");
    return 0;
}

int ms_env_setenv(char **args, ms_shell_context_t *context)
{
    int argc = 0;

    for (char **arg = args; arg[argc]; argc++);
    if (argc > 2) {
        my_dprintf(2, "setenv: Too many arguments.\n");
        return 1;
    }
    if (argc == 0) {
        ms_env_show(NULL, context);
        return 0;
    }
    if (ms_valid_envname(args[0]))
        return 1;
    if (args[1])
        ms_set_env_value(args[0], args[1], context);
    else
        ms_set_env_value(args[0], "", context);
    return 0;
}
