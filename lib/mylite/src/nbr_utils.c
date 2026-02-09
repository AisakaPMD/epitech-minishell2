/*
** EPITECH PROJECT, 2025
** C Pool - MyLib
** File description:
** Int base conversion utils
*/

#include "my.h"

static int my_putnbr_rec(int nbr, char const *base, int baselen)
{
    if (nbr >= baselen)
        my_putnbr_rec(nbr / baselen, base, baselen);
    my_putchar(base[nbr % baselen]);
    return 0;
}

int my_putnbr_base(int nbr, char const *base)
{
    int baselen = my_strlen(base);
    int abs = nbr < 0 ? -nbr : nbr;

    if (baselen < 2)
        return 0;
    if (nbr < 0)
        my_putchar('-');
    return my_putnbr_rec(abs, base, baselen);
}
