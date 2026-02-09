/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** MiniShell translation unit
** containing commands related
** to current dir manipulation
** Author:
** Amélie Ambleton--Guth
** February 2026
*/

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "minishell1.h"

static void fork_callback(char **args, char **env)
{
    execve(args[0], args, env);
    my_dprintf(2, "%s: %s\n", args[0], strerror(errno));
    exit(1);
}

int run_other(char **args, ms_shell_context_t *context)
{
    int status = 0;
    char *full_path = (char[PATH_MAX]) {0};
    char **env_dump;
    __pid_t npid;

    if (!(args[0][0] == '.' || args[0][0] == '/')) {
        if (get_cmd_path(context, args[0], full_path)) {
            args[0] = full_path;
        } else {
            my_dprintf(2, "%s: Command not found.\n", args[0]);
            return -1;
        }
    }
    env_dump = ms_dump_env(context);
    npid = fork();
    if (npid == 0)
        fork_callback(args, env_dump);
    waitpid(npid, &status, 0);
    free_str_arr(env_dump);
    return status;
}

int run_exit(char **args, ms_shell_context_t *context)
{
    char *expr = my_join(" ", args + 1);
    int status;

    if (!expr || strlen(expr) == 0) {
        status = 0;
    } else {
        if (!my_str_isnumerical(expr)) {
            free(expr);
            my_dprintf(2, "exit: Expression Syntax.\n");
            return 1;
        }
        status = my_getnbr(expr);
    }
    free(expr);
    free_str_arr(args);
    ms_teardown(context);
    exit(status);
}

int run_cd(char **args, ms_shell_context_t *context)
{
    char *expr = my_join(" ", args + 1);
    int status = 0;
    char *cwd_buffer;

    if (!expr || strlen(expr) == 0) {
        free(expr);
        expr = my_strdup(ms_get_env_value("HOME", context));
    }
    if (!my_strcmp("-", expr)) {
        free(expr);
        expr = my_strdup(ms_get_env_value("OLDPWD", context));
    }
    cwd_buffer = getcwd(NULL, 0);
    ms_set_env_value("OLDPWD", cwd_buffer, context);
    free(cwd_buffer);
    status = chdir(expr);
    if (status != 0)
        my_dprintf(2, "%s: %s\n", expr, strerror(errno));
    free(expr);
    return status;
}
