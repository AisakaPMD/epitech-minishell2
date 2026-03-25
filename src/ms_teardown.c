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
#include <stdarg.h>

#include "minishell2.h"
#include "benjalib.h"

void free_batch(int count, ...)
{
    va_list args;
    void *current;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        current = va_arg(args, void *);
        if (current != NULL)
            free(current);
    }
    va_end(args);
}

void free_token(ms_token_t *token)
{
    if (!token)
        return;
    safe_free(&token->word_value);
    free(token);
}

void free_grammar(ms_grammar_parser_t *grammar)
{
    while (grammar && grammar->tokens)
        free_token(ll_shift(&grammar->tokens));
}

void free_ast(ms_syntax_tree_t *node)
{
    if (!node)
        return;
    if (node->type == MS_TREE_WORD) {
        free(ll_shift(&node->children));
        free(node);
        return;
    }
    if (node->type == MS_TREE_REDIRECTION)
        free_token(ll_shift(&node->children));
    while (node->children)
        free_ast(ll_shift(&node->children));
    free(node);
}
