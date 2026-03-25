/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** MiniShell utils
** Author:
** Amélie Ambleton--Guth
*/


// We want the general grammar to be left-recursive.

// LEXEMES RULES
// A lexeme is defined by any sequence of
// letters or symbols that is neither a space, a tab,
// nor a newline, unless they're escaped or quoted.
// A backslash escapes the next character except when
// enclosed by single quotes.
// Unescaped quotes and backslashes are not included in the lexeme.
// Any unescaped/unquoted token (besides 'word's) also breaks
// the lexeme they're in the middle of, if any, emitting
// a token for the part of the lexeme before it,
// then emitting its own token. A new lexeme begins
// right after (or at the first non-blank following).

// TOKENS RULES - First match stops further matching attempts

// 'EOF' - End of input (no associated lexeme)
// '&&' - literal &&
// '||' - literal ||
// '>>' - literal >>
// '<<' - literal <<
// '&' - literal &
// '|' - literal |
// '>' - literal >
// '<' - literal <
// ';' - literal ;
// '(' - literal (
// ')' - literal )
// WORD - any other lexeme



// GRAMMAR RULES
//   Legend:
//     '?' means the previous token can be omitted
//     '*' matches the token between 0 and unlimited times
//     '+' matches the token between 1 and unlimited times

// root:             'sequence' - top-level node
// simple_command:   '( sequence )'
// redirection:      '< WORD'
// redirection:      '<< WORD'
// redirection:      '> WORD'
// redirection:      '>> WORD'
// sequence:         'sequence ; and_or'
// sequence:         'and_or'
// and_or:           'and_or && pipeline'
// and_or:           'and_or || pipeline'
// and_or:           'pipeline'
// pipeline:         'pipeline | simple_command'
// pipeline:         'simple_command'
// simple_command:   'redirection* command redirection*'
// command:          'WORD+'

// Any remaining token that does not fit in
// the grammar ruleset will trigger an error
// and prevent the execution of the input.

#include "minishell2.h"
#include "benjalib.h"

static bool perform_checks(int pipesin, int pipesout, bool empty,
    ms_shell_context_t *ctx)
{
    if ((pipesin > 0 || pipesout > 0) && empty) {
        ms_fail(ctx, MSE_NULL_COMMAND);
        return false;
    }
    if (pipesin > 1) {
        ms_fail(ctx, MSE_AMBIGUOUS_INPUT);
        return false;
    }
    if (pipesout > 1) {
        ms_fail(ctx, MSE_AMBIGUOUS_OUTPUT);
        return false;
    }
    return true;
}

static bool verify_command(ms_syntax_tree_t *command, int pipesin, int pipesout)
{
    list_t *children = command->children;
    ms_syntax_tree_t *child;
    bool empty = true;
    ms_token_t *tok;

    for (; children; children = children->next) {
        child = children->data;
        if (child->type == MS_TREE_REDIRECTION) {
            tok = child->children->data;
            pipesin += RD_IN(tok->type);
            pipesout += RD_OUT(tok->type);
            continue;
        }
        if (child->children != NULL)
            empty = false;
    }
    return perform_checks(pipesin, pipesout, empty, command->ctx_ref);
}

bool verify_pipeline(ms_syntax_tree_t *pipeline)
{
    list_t *children = pipeline->children;
    bool first = true;

    while (children) {
        if (!verify_command(children->data, !first, children->next != NULL))
            return false;
        first = false;
        children = children->next;
    }
    return true;
}
