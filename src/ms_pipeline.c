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
#include <string.h>

#include "minishell2.h"
#include "benjalib.h"

static pid_t forked_simple_command(ms_syntax_tree_t *node,
    ms_shell_context_t *context, int fdin, int fdout)
{
    pid_t pid;
    int visit_status;

    if (!node || !context)
        return -1;
    pid = fork();
    if (pid == 0) {
        visit_status = visit_simple_command(node, context, fdin, fdout);
        close(fdin);
        close(fdout);
        exit(visit_status);
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
        if (piped[1] != STDOUT_FILENO)
            close(piped[1]);
        *lastin = piped[0];
    }
    return 0;
}

int pipeline_handler(ms_syntax_tree_t *node, ms_shell_context_t *context)
{
    int status = 0;
    int final_status = 0;
    int lastin = STDIN_FILENO;
    int nb_nodes = ll_size(node->children);
    pid_t pid[nb_nodes];

    status = build_pipeline(node, context, &lastin, pid);
    if (status) {
        my_dprintf(STDERR_FILENO, "Pipeline error: %s\n", strerror(status));
        return status;
    }
    for (int index = 0; index < nb_nodes; index++) {
        waitpid(pid[index], &status, 0);
        if (status != 0)
            final_status = WIFEXITED(status) ?
                WEXITSTATUS(status) : WTERMSIG(status);
    }
    return final_status;
}
