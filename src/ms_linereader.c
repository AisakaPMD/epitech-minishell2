/*
** EPITECH PROJECT, 2026
** LineReader
** File description:
** LineReader utility's translation unit
** Author:
** Amelie Ambleton--Guth
** Mar 2026
*/

#include <stdio.h>
#include <stdlib.h>

#include "minishell2.h"

// Unimplemented due to limitations
linereader_t *lr_new(const char *filename)
{
    return NULL;
}

linereader_t *lr_from_stream(FILE *stream)
{
    linereader_t *lr;

    if (!stream)
        return NULL;
    lr = malloc(sizeof(linereader_t));
    if (!lr)
        return NULL;
    lr->stream = stream;
    lr->line = 0;
    lr->buf = NULL;
    lr->size = 0;
    lr->open_by_linereader = false;
    return lr;
}

void lr_close(linereader_t *fr)
{
    if (!fr)
        return;
    free(fr->buf);
    free(fr);
}

char *lr_read(linereader_t *fr)
{
    ssize_t read_count;
    char *dup = NULL;

    if (!fr)
        return NULL;
    read_count = getline(&fr->buf, &fr->size, fr->stream);
    if (read_count == -1)
        return NULL;
    dup = my_strndup(fr->buf, read_count);
    if (!dup)
        return NULL;
    if (dup[read_count - 1] == '\n')
        dup[read_count - 1] = '\0';
    fr->line++;
    return dup;
}
