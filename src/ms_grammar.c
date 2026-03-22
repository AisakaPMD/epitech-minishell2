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

static void push_word(ms_grammar_parser_t *grammar, ms_syntax_tree_t *parent)
{
    ms_syntax_tree_t *word_node = malloc(sizeof(ms_syntax_tree_t));

    if (!word_node)
        return;
    word_node->children = NULL;
    word_node->type = MS_TREE_WORD;
    ll_push(&parent->children, word_node);
    ll_push(&word_node->children, gr_consume(grammar)->word_value);
}

static bool parse_redirection(ms_grammar_parser_t *grammar,
    ms_syntax_tree_t *parent)
{
    ms_syntax_tree_t *redir_node;

    if (!(gr_testfor(grammar, MS_TOKEN_GREATER) ||
            gr_testfor(grammar, MS_TOKEN_LESS) ||
            gr_testfor(grammar, MS_TOKEN_DOUBLE_GREATER) ||
            gr_testfor(grammar, MS_TOKEN_DOUBLE_LESS)))
        return false;
    if (!gr_testahead(grammar, MS_TOKEN_WORD)) {
        fprintf(stderr, "ParseError: line %d: expected word\n", 1);
        return false;
    }
    redir_node = malloc(sizeof(ms_syntax_tree_t));
    if (!redir_node)
        return false;
    redir_node->children = NULL;
    redir_node->type = MS_TREE_REDIRECTION;
    ll_push(&parent->children, redir_node);
    ll_push(&redir_node->children, gr_consume(grammar));
    push_word(grammar, redir_node);
    return true;
}

static void parse_simple_command(ms_grammar_parser_t *grammar,
    ms_syntax_tree_t *parent)
{
    ms_syntax_tree_t *command_node = malloc(sizeof(ms_syntax_tree_t));

    if (!command_node)
        return;
    command_node->children = NULL;
    command_node->type = MS_TREE_COMMAND;
    ll_push(&parent->children, command_node);
    if (gr_at_end(grammar))
        return;
    while (1) {
        if (parse_redirection(grammar, parent))
            continue;
        if (gr_testfor(grammar, MS_TOKEN_WORD))
            push_word(grammar, command_node);
        else
            break;
    }
}

static void parse_pipeline(ms_grammar_parser_t *grammar,
    ms_syntax_tree_t *parent)
{
    ms_syntax_tree_t *node;

    if (gr_at_end(grammar))
        return;
    while (1) {
        node = malloc(sizeof(ms_syntax_tree_t));
        node->children = NULL;
        node->type = MS_TREE_SIMPLE_COMMAND;
        parse_simple_command(grammar, node);
        ll_push(&parent->children, node);
        if (!gr_match(grammar, MS_TOKEN_PIPE))
            break;
    }
}

static void parse_and_or(ms_grammar_parser_t *grammar, ms_syntax_tree_t *parent)
{
    ms_syntax_tree_t *node;

    if (gr_at_end(grammar))
        return;
    while (1) {
        node = malloc(sizeof(ms_syntax_tree_t));
        node->children = NULL;
        node->type = MS_TREE_PIPELINE;
        parse_pipeline(grammar, node);
        ll_push(&parent->children, node);
        if (gr_testfor(grammar, MS_TOKEN_AND) ||
            gr_testfor(grammar, MS_TOKEN_OR))
            ll_push(&parent->children, gr_consume(grammar));
        else
            break;
    }
}

static void parse_sequence(ms_grammar_parser_t *grammar, ms_syntax_tree_t *root)
{
    ms_syntax_tree_t *node;
    ms_token_t *token;

    while (!gr_at_end(grammar)) {
        if (gr_match(grammar, MS_TOKEN_SEMICOLON))
            continue;
        node = malloc(sizeof(ms_syntax_tree_t));
        node->children = NULL;
        node->type = MS_TREE_AND_OR;
        parse_and_or(grammar, node);
        ll_push(&root->children, node);
        if (!gr_match(grammar, MS_TOKEN_SEMICOLON) && !gr_at_end(grammar)) {
            token = gr_consume(grammar);
            fprintf(stderr, "ParseError: line %d: unexpected token 0x%02X "
                "[%s]\n", 1, token->type, token->word_value);
            grammar->errored = true;
            break;
        }
    }
}

// TODO free the tree!!
ms_syntax_tree_t *ms_generate_ast(list_t *tokens)
{
    ms_grammar_parser_t grammar = {0};
    ms_syntax_tree_t *root = malloc(sizeof(ms_syntax_tree_t));

    if (!root)
        return NULL;
    grammar.tokens = tokens;
    root->children = NULL;
    root->type = MS_TREE_SEQUENCE;
    parse_sequence(&grammar, root);
    if (grammar.errored) {
        fprintf(stderr, "-- Terminating.\n");
        return NULL;
    }
    return root;
}
