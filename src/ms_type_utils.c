/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** MiniShell utils
** Author:
** Amélie Ambleton--Guth
*/

#include "minishell2.h"
#include "benjalib.h"

char *ms_tree_type_to_str(ms_tree_type_t type)
{
    switch (type) {
        case MS_TREE_SEQUENCE:
            return "sequence";
        case MS_TREE_AND_OR:
            return "and_or";
        case MS_TREE_PIPELINE:
            return "pipeline";
        case MS_TREE_SIMPLE_COMMAND:
            return "simple_command";
        case MS_TREE_REDIRECTION:
            return "redirection";
        case MS_TREE_COMMAND:
            return "command";
        default:
            return "unknown";
    }
}

static char *ms_token_type_to_str(ms_token_type_t type)
{
    char *str[] = {"-", "|", ";", "&", "<", ">", "(", ")", "<<", ">>",
        "||", "&&", "EOF"};

    return str[type];
}

char *ms_token_to_str(ms_token_t *token)
{
    switch (token->type) {
        case MS_TOKEN_WORD:
            return token->word_value;
        default:
            return ms_token_type_to_str(token->type);
    }
}

void print_tree(ms_syntax_tree_t *tree, int depth)
{
    ms_token_t *tk;

    if (!tree)
        return;
    if (tree->type == MS_TREE_WORD) {
        my_printf("%*s > WORD [%s]\n", depth, " ",
            (char *) ll_shift(&tree->children));
        return;
    }
    my_printf("%*s > %s\n", depth, "", ms_tree_type_to_str(tree->type));
    if (tree->type == MS_TREE_REDIRECTION) {
        tk = ll_shift(&tree->children);
        my_printf("%*s > Type: [%s]\n", depth, " ", ms_token_to_str(tk));
    }
    while (tree->children) {
        print_tree(ll_shift(&tree->children), depth + 2);
    }
}
