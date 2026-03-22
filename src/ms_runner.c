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

static int trigger_command(char **args, ms_shell_context_t *context,
    int in, int out)
{
    int old_in = dup(STDIN_FILENO);
    int old_out = dup(STDOUT_FILENO);
    int res = 0;

    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    res = run_command(args, context);
    free(args);
    if (in != STDIN_FILENO)
        close(in);
    if (out != STDOUT_FILENO)
        close(out);
    dup2(old_in, STDIN_FILENO);
    dup2(old_out, STDOUT_FILENO);
    return res;
}

static int visit_command(ms_syntax_tree_t *node,
    ms_shell_context_t *context, int fdin, int fdout)
{
    char **args;
    ms_syntax_tree_t *word;

    if (!node || !context)
        return 84;
    if (node->type != MS_TREE_COMMAND)
        return 84;
    args = calloc(ll_size(node->children) + 1, sizeof(char *));
    if (!args)
        return 84;
    for (int i = 0; node->children; i++) {
        word = ll_shift(&node->children);
        if (word->type != MS_TREE_WORD)
            return 84;
        args[i] = ll_shift(&word->children);
    }
    return trigger_command(args, context, fdin, fdout);
}

static int redirect_out(int *fdout, char *word, bool append)
{
    if (*fdout != STDOUT_FILENO) {
        fprintf(stderr, "Ambiguous output redirect.\n");
        return 1;
    }
    *fdout = open(word, O_WRONLY | O_CREAT | (!append ? O_TRUNC : O_APPEND),
        0644);
    if (*fdout == -1)
        return 1;
    return 0;
}

static int redirect_in(int *fdin, char *word, bool heredoc)
{
    if (*fdin != STDIN_FILENO) {
        fprintf(stderr, "Ambiguous input redirect.\n");
        return 1;
    }
    if (!heredoc) {
        *fdin = open(word, O_RDONLY, 0);
        if (*fdin == -1)
            return 1;
        return 0;
    }
    return 0;
}

static int visit_redirection(ms_syntax_tree_t *node,
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
        type->type == MS_TOKEN_DOUBLE_LESS);
}

int visit_simple_command(ms_syntax_tree_t *node, ms_shell_context_t *context,
    int fdin, int fdout)
{
    ms_syntax_tree_t *cmd;
    ms_syntax_tree_t *child;
    int redir_status = 0;

    if (!node || !context)
        return 84;
    if (!node->children || ((ms_syntax_tree_t *) node->children->data)->type
        != MS_TREE_COMMAND)
        return 84;
    cmd = ll_shift(&node->children);
    while (node->children) {
        child = ll_shift(&node->children);
        redir_status = visit_redirection(child, context, &fdin, &fdout);
        if (redir_status)
            return redir_status;
    }
    return visit_command(cmd, context, fdin, fdout);
}

static int visit_pipeline(ms_syntax_tree_t *node, ms_shell_context_t *context)
{
    pid_t pid;
    int status = 0;

    if (VIS_VALID(node && context, node, MS_TREE_PIPELINE))
        return 84;
    if (node->children && !node->children->next)
        return visit_simple_command(ll_shift(&node->children), context,
            STDIN_FILENO, STDOUT_FILENO);
    pid = fork();
    if (pid == 0)
        exit(pipeline_handler(node, context));
    if (pid == -1)
        return 84;
    waitpid(pid, &status, 0);
    return status;
}

static int visit_and_or(ms_syntax_tree_t *node, ms_shell_context_t *context)
{
    ms_syntax_tree_t *child;
    int res = 0;

    while (node->children && res == 0) {
        child = ll_shift(&node->children);
        if (child->type == MS_TREE_PIPELINE)
            res = visit_pipeline(child, context);
    }
    return res;
}

static int visit_sequence(ms_syntax_tree_t *node, ms_shell_context_t *context)
{
    ms_syntax_tree_t *child;
    int res = 0;

    context->last_exit_status = 0;
    if (VIS_VALID(node && context, node, MS_TREE_SEQUENCE))
        return 84;
    while (node->children) {
        child = ll_shift(&node->children);
        res = visit_and_or(child, context);
        if (res != 0)
            context->last_exit_status = res;
    }
    return res;
}

int ms_runner(list_t *tokens, ms_shell_context_t *context)
{
    ms_syntax_tree_t *ast;

    if (!tokens || !context)
        return 84;
    ast = ms_generate_ast(tokens);
    if (!ast)
        return 84;
    return visit_sequence(ast, context);
}
