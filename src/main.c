/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Project's entry point
** Auto-Generated with Episetup by Amélie
** Author:
** Amélie Ambleton--Guth
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include "minishell1.h"

void ms_teardown(ms_shell_context_t *context)
{
    list_t *env = context->env;
    ms_env_entry_t *entry;

    while (env) {
        entry = ll_shift(&env);
        free(entry->key);
        free(entry->value);
        free(entry);
    }
    if (context->last_working_dir)
        free(context->last_working_dir);
}

int run_command(char **args, ms_shell_context_t *context)  
{
    if (!args || !args[0])
        return 0;
    if (!my_strcmp(args[0], "exit"))
        return run_exit(args, context);
    if (!my_strcmp(args[0], "cd"))
        return run_cd(args, context);
    if (!my_strcmp(args[0], "setenv"))
        return ms_env_setenv(args + 1, context);
    if (!my_strcmp(args[0], "unsetenv"))
        return ms_env_unset(args + 1, context);
    if (!my_strcmp(args[0], "env"))
        return ms_env_show(args + 1, context);
    return run_other(args, context);
}

static void display_prompt(ms_shell_context_t *context)
{
    char *cwd = getcwd(NULL, 0);

    my_printf("[%d %s]$ ", context->last_exit_status, cwd);
    free(cwd);
}

static size_t expand_tilde_size(ms_shell_context_t *context, char *line)
{
    size_t expansion_size = 0;
    char *expansion_string = ms_get_env_value("HOME", context);

    for (int chr = 0; line[chr]; chr++) {
        if (line[chr] == '~' && (chr == 0 || line[chr - 1] == ' '))
            expansion_size += my_strlen(expansion_string);
        else
            expansion_size += 1;
    }
    return expansion_size;
}

static char *expand_tilde(ms_shell_context_t *context, char *line)
{
    int expansion_size = 0;
    char *expansion_string = ms_get_env_value("HOME", context);
    char *expanded_line = my_calloc(expand_tilde_size(context, line) + 1,
        sizeof(char));

    if (!expanded_line)
        return NULL;
    for (int chr = 0; line[chr]; chr++) {
        if (line[chr] == '~' && (chr == 0 || line[chr - 1] == ' ')) {
            my_strcpy(expanded_line + expansion_size, expansion_string);
            expansion_size += my_strlen(expansion_string);
        } else {
            expanded_line[expansion_size] = line[chr];
            expansion_size += 1;
        }
    }
    expanded_line[expansion_size] = '\0';
    return expanded_line;
}

static void process_line(ms_shell_context_t *context, char *line)
{
    char *expanded_line = expand_tilde(context, line);
    char **args;

    if (expanded_line) {
        args = my_explode(expanded_line, " \t\n");
        free(expanded_line);
    } else
        args = my_explode(line, " \t\n");
    context->last_exit_status = run_command(args, context);
    free_str_arr(args);
}

int main(int argc, char **argv, char **env)
{
    ms_shell_context_t context = {0};
    size_t bufsize = 0;
    char *buf = NULL;
    ssize_t read;

    ms_populate_env_from_dump(env, &context);
    while (1) {
        display_prompt(&context);
        read = getline(&buf, &bufsize, stdin);
        if (read == -1)
            break;
        if (read == 0)
            continue;
        buf[read - 1] = '\0';
        process_line(&context, buf);
    }
    free(buf);
    ms_teardown(&context);
    my_putstr("\n");
    return context.last_exit_status;
}
