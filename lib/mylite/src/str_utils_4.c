/*
** EPITECH PROJECT, 2025
** C Pool - My Lib
** File description:
** String Utils 4
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"

int my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return 0;
}

static char is_alphanum(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z');
}

static void count_word_size(int *wordsize, int nb_words, char const *str)
{
    int word = 0;
    int current_length = 0;
    int inWord = 0;

    for (int i = 0; str[i]; i++) {
        if (!is_alphanum(str[i]) && inWord) {
            wordsize[word] = current_length;
            current_length = 0;
            word++;
            inWord = 0;
        }
        if (is_alphanum(str[i])) {
            inWord = 1;
            current_length++;
        }
    }
    wordsize[word] = current_length;
}

static int count_words(char const *str)
{
    int words = 0;
    int inWord = 0;

    for (int i = 0; str[i]; i++) {
        if (is_alphanum(str[i]))
            inWord = 1;
        if (!is_alphanum(str[i]) && inWord) {
            words++;
            inWord = 0;
        }
    }
    if (inWord)
        words++;
    return words;
}

static int find_alphanum(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (is_alphanum(str[i]))
            return i;
    }
    return 0;
}

char **my_str_to_word_array(char const *str)
{
    int current_length = find_alphanum(str);
    int words = count_words(str);
    char **res;
    int *wordsize;

    res = malloc(sizeof(char *) * words + 1);
    res[words] = NULL;
    wordsize = malloc(sizeof(int) * words);
    count_word_size(wordsize, words, str);
    for (int i = 0; i < words; i++){
        res[i] = my_strndup(str + current_length, wordsize[i]);
        current_length += wordsize[i] + 1;
        current_length += find_alphanum(str + current_length);
    }
    free(wordsize);
    return res;
}

char *my_strdup(char const *src)
{
    int strlen = my_strlen(src);
    char *dst = malloc(sizeof(char) * (strlen + 1));

    my_strcpy(dst, src);
    return dst;
}

char *my_strndup(char const *src, int nb)
{
    int strlen = my_strlen(src);
    char *dst;

    if (nb > strlen)
        nb = strlen;
    dst = malloc(sizeof(char) * (nb + 1));
    my_strncpy(dst, src, nb);
    dst[nb] = '\0';
    return dst;
}

int my_fputs(int fd, char const *str)
{
    return write(fd, str, my_strlen(str));
}
