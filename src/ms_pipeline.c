/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** MiniShell utils
** Author:
** Amélie Ambleton--Guth
*/

#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "minishell2.h"
#include "benjalib.h"

static pid_t forked_simple_command(ms_syntax_tree_t *node,
    ms_shell_context_t *context, int fdin, int fdout)
{
    pid_t pid;

    if (!node || !context)
        return -1;
    pid = fork();
    if (pid == 0) {
        exit(visit_simple_command(node, context, fdin, fdout));
    }
    return pid;
}

static int build_pipeline(ms_syntax_tree_t *node, ms_shell_context_t *context,
    int *lastin, pid_t *pid)
{
    ms_syntax_tree_t *child;
    int piped[2] = {0};
    bool pipe_status = true;

    for (int index = 0; node->children; index++) {
        child = ll_shift(&node->children);
        if (node->children)
            pipe_status = pipe(piped) == 0;
        else
            piped[1] = STDOUT_FILENO;
        if (!pipe_status)
            return 84;
        pid[index] = forked_simple_command(child, context, *lastin, piped[1]);
        if (*lastin != STDIN_FILENO)
            close(*lastin);
        *lastin = piped[0];
    }
    return 0;
}

int pipeline_handler(ms_syntax_tree_t *node, ms_shell_context_t *context)
{
    int status = 0;
    int lastin = STDIN_FILENO;
    pid_t pid[ll_size(node->children)];

    status = build_pipeline(node, context, &lastin, pid);
    if (status)
        return status;
    for (int index = 0; index < ll_size(node->children); index++) {
        waitpid(pid[index], &status, 0);
        if (status != 0)
            context->last_exit_status = status;
    }
    return context->last_exit_status;
}
