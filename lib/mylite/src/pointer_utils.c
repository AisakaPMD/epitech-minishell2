/*
** EPITECH PROJECT, 2025
** C Pool Day 7
** File description:
** MyLib Pointer Utils
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int c = *a;

    *a = *b;
    *b = c;
}

void my_sort_int_array(int *array, int size)
{
    int *lowest = array;

    if (size < 2)
        return;
    for (int i = 1; i < size; i++) {
        if (array[i] < *lowest)
            lowest = array + i;
    }
    my_swap(lowest, array);
    my_sort_int_array(array + 1, size - 1);
}
