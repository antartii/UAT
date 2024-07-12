/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** ptr_arr
*/

#include "epiuat.h"

int get_ptr_arr_size(const void **array)
{
    int count = 0;

    if (!array)
        return 0;
    for (; array[count] != NULL; count += 1);
    return count;
}

int free_ptr_arr_content(void **array)
{
    if (!array)
        return -1;
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    return 0;
}

int free_ptr_arr(void **array)
{
    if (!array)
        return -1;
    free_ptr_arr_content(array);
    free(array);
    return 0;
}

int free_ptr_table(void ***table)
{
    if (!table)
        return -1;
    for (int i = 0; table[i]; i += 1)
        free_ptr_arr(table[i]);
    free(table);
    return 0;
}
