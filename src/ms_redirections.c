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

static int redirect_out(int *fdout, char *word, bool append)
{
    if (*fdout != STDOUT_FILENO) {
        my_dprintf(STDERR_FILENO, "Ambiguous output redirect.\n");
        return 1;
    }
    *fdout = open(word, O_WRONLY | O_CREAT | (!append ? O_TRUNC : O_APPEND),
        0644);
    if (*fdout == -1)
        return 1;
    return 0;
}

static int read_heredoc(int fdout, char *word, ms_shell_context_t *context)
{
    char *buf = NULL;
    bool heredoc = true;

    while (heredoc) {
        ms_prompt(context, MS_PROMPT_FOLLOWUP);
        buf = lr_read(context->reader);
        if (!buf)
            return 1;
        if (my_strcmp(buf, word) != 0)
            my_dprintf(fdout, "%s\n", buf);
        else
            heredoc = false;
        free(buf);
    }
    return 0;
}

static int redirect_heredoc(int *fdin, char *word, ms_shell_context_t *context)
{
    int pipefd[2];
    int res = 0;

    if (pipe(pipefd) == -1)
        return 1;
    *fdin = pipefd[0];
    res = read_heredoc(pipefd[1], word, context);
    close(pipefd[1]);
    if (res != 0)
        close(*fdin);
    return res;
}

static int redirect_in(int *fdin, char *word, bool heredoc,
    ms_shell_context_t *context)
{
    if (*fdin != STDIN_FILENO) {
        my_dprintf(STDERR_FILENO, "Ambiguous input redirect.\n");
        return 1;
    }
    if (!heredoc) {
        *fdin = open(word, O_RDONLY, 0);
        if (*fdin == -1)
            return 1;
        return 0;
    }
    return redirect_heredoc(fdin, word, context);
}

int visit_redirection(ms_syntax_tree_t *node,
    ms_shell_context_t *context, int *fdin, int *fdout)
{
    ms_token_t *type;
    ms_syntax_tree_t *word;

    if (!node || !context)
        return 84;
    if (node->type != MS_TREE_REDIRECTION)
        return 84;
    type = ll_shift(&node->children);
    word = ll_shift(&node->children);
    if (!type || !word)
        return 84;
    if (RD_OUT(type->type))
        return redirect_out(fdout, ll_shift(&word->children),
            type->type == MS_TOKEN_DOUBLE_GREATER);
    return redirect_in(fdin, ll_shift(&word->children),
        type->type == MS_TOKEN_DOUBLE_LESS, context);
}
