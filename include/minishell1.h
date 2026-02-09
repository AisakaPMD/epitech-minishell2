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


// Explode utility
char **my_explode(char const *str, char const *separator);
void free_str_arr(char **str_arr);
char *my_join(char const *separator, char **str_arr);

// Miscellaneous Utils
void *my_calloc(size_t count, size_t unit_size);


#endif