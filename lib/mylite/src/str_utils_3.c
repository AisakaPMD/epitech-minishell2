/*
** EPITECH PROJECT, 2025
** C Pool Day 7
** File description:
** MyLib String Utils 3
*/

#include "my.h"
#include <stddef.h>

char *my_strcat(char *dest, char const *src)
{
    my_strcpy(dest + my_strlen(dest), src);
    return dest;
}

char *my_strncat(char *dest, char const *src, int nb)
{
    int dstlen = my_strlen(dest);

    my_strncpy(dest + dstlen, src, nb);
    dest[dstlen + nb] = 0;
    return dest;
}

static int is_printable(char c)
{
    char sr[] = {c, 0};

    return my_str_isprintable(sr);
}

int my_showstr(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (is_printable(str[i]))
            my_putchar(str[i]);
        else {
            my_putchar('\\');
            my_putchar(str[i] / 16 + '0');
            my_putchar(("0123456789abcdef")[str[i] % 16]);
        }
    }
    return 0;
}

static int put_hex(int nbr, int n)
{
    if (n > 1)
        put_hex(nbr / 16, n - 1);
    my_putchar(("0123456789abcdef")[nbr % 16]);
    return 0;
}

static void write_hex(int nbr, int places)
{
    if (nbr < 0)
        return;
    put_hex(nbr, places);
}

static void showmem_line(char const *str, int line, int size)
{
    int remaining = size - line * 16;

    for (int i = 0; i < 16; i++) {
        if (i < remaining)
            write_hex(str[line * 16 + i], 2);
        else
            my_putstr("  ");
        if (i % 2)
            my_putchar(' ');
    }
    for (int i = 0; i < 16; i++) {
        if (i < remaining && is_printable(str[line * 16 + i]))
            my_putchar(str[line * 16 + i]);
        else
            my_putchar('.');
    }
    my_putchar('\n');
}

int my_showmem(char const *str, int size)
{
    for (int line = 0; line < (size - 1) / 16 + 1; line++) {
        write_hex(line * 16, 8);
        my_putstr(": ");
        showmem_line(str, line, size);
    }
    return 0;
}
