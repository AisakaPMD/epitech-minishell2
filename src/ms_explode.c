/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Project's entry point
** Auto-Generated with Episetup by Amélie
** Author:
** Amélie Ambleton--Guth
*/

#include <stdlib.h>
#include <string.h>

#include "minishell1.h"

static int is_word(char c, char const *separator)
{
    for (; separator[0]; separator++)
        if (separator[0] == c)
            return 0;
    return 1;
}

static int wordlen(char const *begin, char const *separator)
{
    int len = 0;

    for (; begin[len] && is_word(begin[len], separator); len++);
    return len;
}

static int count_words_loop(int is_word, int *in_word)
{
    int nb_words = 0;

    if (is_word) {
        if (!(*in_word))
            nb_words++;
        *in_word = 1;
    } else
        *in_word = 0;
    return nb_words;
}

static int count_words(char const *str, char const *separator)
{
    int in_word = 0;
    int nb_words = 0;

    for (int i = 0; str[i]; i++) {
        nb_words += count_words_loop(is_word(str[i], separator), &in_word);
    }
    return nb_words;
}

char **my_explode(char const *str, char const *separator)
{
    int word_len = 0;
    int cur_word = 0;
    int words = count_words(str, separator);
    char **array = malloc(sizeof(char *) * (words + 1));

    for (int i = 0; str[i]; i++) {
        if (is_word(str[i], separator)) {
            word_len = wordlen(str + i, separator);
            array[cur_word] = strndup(str + i, word_len);
            cur_word++;
            i += word_len - 1;
        }
    }
    array[words] = NULL;
    return array;
}

static size_t joined_length(char const *separator, char **str_arr)
{
    size_t len = 0;
    int first = 1;

    for (int i = 0; str_arr[i]; i++) {
        if (!first)
            len += strlen(separator);
        first = 0;
        len += strlen(str_arr[i]);
    }
    return len;
}

char *my_join(char const *separator, char **str_arr)
{
    size_t len = joined_length(separator, str_arr);
    int first = 1;
    char *str = my_calloc(len + 1, sizeof(char));

    if (!str)
        return NULL;
    for (int i = 0; str_arr[i]; i++) {
        if (!first)
            my_strcat(str, separator);
        first = 0;
        my_strcat(str, str_arr[i]);
    }
    str[len] = 0;
    return str;
}

void free_str_arr(char **str_arr)
{
    for (int i = 0; str_arr[i]; i++) {
        free(str_arr[i]);
    }
    free(str_arr);
}
