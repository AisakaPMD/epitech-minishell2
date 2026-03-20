/*
** EPITECH PROJECT, 2025
** Linked List Libs
** File description:
** Include file for linked list functions
** Author:
** Amélie Ambleton--Guth
*/

#include "minishell2.h"

ms_stringbuffer_t *sb_new(char *content)
{
    ms_stringbuffer_t *sb = calloc(1, sizeof(ms_stringbuffer_t));

    if (!sb)
        return NULL;
    if (content) {
        sb->buffer = my_strdup(content);
        if (!sb->buffer) {
            free(sb);
            return NULL;
        }
        sb->size = my_strlen(sb->buffer);
        return sb;
    }
    sb->size = PATH_MAX;
    sb->buffer = calloc(sb->size + 1, sizeof(char));
    if (!sb->buffer) {
        free(sb);
        return NULL;
    }
    return sb;
}

static bool sb_extend(ms_stringbuffer_t *sb, size_t extra)
{
    char *tmp = NULL;
    size_t new_size;

    if (!sb || extra <= 0)
        return false;
    new_size = sb->size + extra;
    tmp = realloc(sb->buffer, new_size + 1);
    if (!tmp)
        return false;
    sb->size = new_size;
    sb->buffer = tmp;
    return true;
}

static void sb_move(ms_stringbuffer_t *sb, size_t start, size_t length,
    ssize_t amount)
{
    if (!sb || start + length > sb->size || length <= 0 || start < 0
        || start > sb->size || amount == 0)
        return;
    if (amount > 0) {
        for (size_t i = start + length - 1; i >= start + length; i--) {
            sb->buffer[i + amount] = sb->buffer[i];
        }
    } else {
        for (size_t i = start; i < start + length; i++) {
            sb->buffer[i + amount] = sb->buffer[i];
        }
    }
}

void sb_free(ms_stringbuffer_t *sb)
{
    if (!sb)
        return;
    if (sb->buffer)
        free(sb->buffer);
    free(sb);
}

bool sb_append(ms_stringbuffer_t *sb, char *content)
{
    if (!sb || !content)
        return NULL;
    if (sb_extend(sb, sb->size + my_strlen(content))) {
        my_strcat(sb->buffer, content);
        return true;
    }
    return false;
}

bool sb_prepend(ms_stringbuffer_t *sb, char *content)
{
    char *tmp = NULL;
    size_t new_size;

    if (!sb || !content)
        return NULL;
    new_size = sb->size + my_strlen(content);
    tmp = calloc(new_size + 1, sizeof(char));
    if (!tmp)
        return false;
    my_strcpy(tmp, content);
    my_strcat(tmp, sb->buffer);
    free(sb->buffer);
    sb->size = new_size;
    sb->buffer = tmp;
    return true;
}

bool sb_insert(ms_stringbuffer_t *sb, char *content, size_t index)
{
    char *tmp = NULL;
    size_t new_size;

    if (!sb || !content)
        return NULL;
    if (index == 0)
        return sb_prepend(sb, content);
    if (index >= sb->size)
        return sb_append(sb, content);
    new_size = sb->size + my_strlen(content);
    tmp = calloc(new_size + 1, sizeof(char));
    if (!tmp)
        return false;
    my_strcpy(tmp, content);
    my_strcat(tmp, sb->buffer);
    free(sb->buffer);
    sb->size = new_size;
    sb->buffer = tmp;
    return true;
}
