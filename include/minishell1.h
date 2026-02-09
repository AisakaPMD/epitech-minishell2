/*
** EPITECH PROJECT, 2025
** Linked List Libs
** File description:
** Include file for linked list functions
** Author:
** Amélie Ambleton--Guth
*/

#ifndef MINISHELL1_H
    #define MINISHELL1_H

    #include "my.h"
    #include "linked_list.h"
    #include "my_printf.h"

typedef struct ms_shell_context_s ms_shell_context_t;

struct ms_shell_context_s {
    unsigned char last_exit_status;
    char *history[50];
    int history_index;

};

// Explode utility
char **my_explode(char const *str, char const *separator);
void free_str_arr(char **str_arr);
char *my_join(char const *separator, char **str_arr);

// Miscellaneous Utils
void *my_calloc(size_t count, size_t unit_size);


#endif
