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
#include <sys/wait.h>
#include "minishell1.h"

int run_other(char **args, char **env)
{
    __pid_t npid = fork();

    if (npid == 0) {
        execvpe(args[0], args, env);
        dprintf(1, "%s: %m\n", args[0]);
        exit(1);
    }

    // We are the old!
    int status = 0;
    waitpid(npid, &status, 0);
    return status;
}

int run_exit(char **args, char **env)
{
    char *expr = my_join(" ", args + 1);
    char *endptr;
    if (!expr || strlen(expr) == 0) {
        free(expr);
        free_str_arr(args);
        exit(0);
    }
    int status = (int) strtol(expr, &endptr, 10);
    if (*endptr) {
        free(expr);
        dprintf(1, "exit: Expression Syntax.\n");
        return 0;
    }
    free(expr);
    free_str_arr(args);
    exit(status);
}

int run_cd(char **args, char **env)
{
    char *expr = my_join(" ", args + 1);
    int status = 0;

    if (!expr || strlen(expr) == 0)
        return 2;
    status = chdir(expr);
    if (status != 0)
        dprintf(1, "cd: %s: %m\n", expr);
    free(expr);
    return 1;
}

int run_command(char **args, char **env)
{
    if (!strcmp(args[0], "exit"))
        return run_exit(args, env);
    if (!strcmp(args[0], "cd"))
        return run_cd(args, env);
    /*if (!strcmp(args[0], "setenv"))
        return run_setenv(args, env);
    if (!strcmp(args[0], "unsetenv"))
        return run_unsetenv(args, env);
    if (!strcmp(args[0], "env"))
        return run_env(args, env);*/
    return run_other(args, env);
}

int main(int argc, char **argv, char **env)
{
    size_t bufsize = 0;
    char *buf = NULL;
    ssize_t read;
    char *cwd;
    int last_status = 0;

    while (1) {
        cwd = getcwd(NULL, 0);
        printf("[%d %s]$ ", last_status, cwd);
        free(cwd);
        fflush(stdout);
        read = getline(&buf, &bufsize, stdin);
        if (read == -1)
            break;
        if (read == 0)
            continue;
        buf[read - 1] = '\0';
        char **args = my_explode(buf, " ");
        last_status = run_command(args, env);
        free_str_arr(args);
    }
    free(buf);
    return 0;
}
