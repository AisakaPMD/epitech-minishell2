/*
** EPITECH PROJECT, 2025
** My Printf
** File description:
** My Printf Public Functions
*/

#ifndef MY_PRINTF_H
    #define MY_PRINTF_H
    #include <stdarg.h>
    #include <stddef.h>
    #include <stdio.h>

int my_printf(char const *format, ...);
int my_fprintf(FILE *stream, char const *format, ...);
int my_dprintf(int fd, char const *format, ...);
int my_sprintf(char *str, char const *format, ...);
int my_snprintf(char *str, size_t size, char const *format, ...);

int my_vprintf(char const *format, va_list ap);
int my_vfprintf(FILE *stream, char const *format, va_list ap);
int my_vdprintf(int fd, char const *format, va_list ap);
int my_vsprintf(char *str, char const *format, va_list ap);
int my_vsnprintf(char *str, size_t size, char const *format, va_list ap);

#endif
