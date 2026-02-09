/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** MiniShell utility managing
** the ENV (setting, getting...)
** its values from the linked
** list in the shell context
** Author:
** Amélie Ambleton--Guth
** February 2026
*/

#include <stdlib.h>
#include <string.h>

#include "minishell1.h"

void ms_populate_env_from_dump(char **env_dump, ms_shell_context_t *context)
{
    ms_env_entry_t *entry;
    char *save_ptr;

    for (char **env_val = env_dump; *env_val; env_val += 1) {
        entry = malloc(sizeof(ms_env_entry_t));
        save_ptr = *env_val;
        if (!entry)
            break;
        entry->key = my_strdup(strtok_r(*env_val, "=", &save_ptr));
        entry->value = my_strdup(save_ptr);
        ll_unshift(&context->env, entry);
    }
}

char *ms_get_env_value(char *key, ms_shell_context_t *context)
{
    ms_env_entry_t *entry;

    for (list_t *env = context->env; env; env = env->next) {
        entry = env->data;
        if (!my_strcmp(entry->key, key))
            return entry->value;
    }
    return "";
}

void ms_set_env_value(char *key, char *value, ms_shell_context_t *context)
{
    ms_env_entry_t *entry;
    list_t **env;

    for (env = &context->env; *env; env = &(*env)->next) {
        entry = (*env)->data;
        if (!my_strcmp(entry->key, key)) {
            free(entry->value);
            entry->value = my_strdup(value);
            return;
        }
    }
    entry = malloc(sizeof(ms_env_entry_t));
    entry->key = my_strdup(key);
    entry->value = my_strdup(value);
    ll_unshift(env, entry);
}

void ms_unset_env_value(char *key, ms_shell_context_t *context)
{
    ms_env_entry_t *entry;

    for (list_t **env = &context->env; *env; env = &(*env)->next) {
        entry = (*env)->data;
        if (!my_strcmp(entry->key, key)) {
            free(entry->value);
            free(entry->key);
            free(entry);
            ll_shift(env);
            return;
        }
    }
}

char **ms_dump_env(ms_shell_context_t *context)
{
    size_t list_size = ll_size(context->env);
    char **env_dump = malloc(sizeof(char *) * (list_size + 1));
    int index = 0;
    ms_env_entry_t *entry;

    for (list_t *cur = context->env; cur; cur = cur->next) {
        entry = cur->data;
        env_dump[index] = my_calloc(my_strlen(entry->key) +
            my_strlen(entry->value) + 2, sizeof(char));
        if (!env_dump[index])
            break;
        my_strcat(env_dump[index], entry->key);
        my_strcat(env_dump[index], "=");
        my_strcat(env_dump[index], entry->value);
        index++;
    }
    env_dump[index] = NULL;
    return env_dump;
}
