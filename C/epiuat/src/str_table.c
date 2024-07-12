/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** str_table
*/

#include "epiuat.h"

int append_str_table(char ****str_table_address, const char **new_str_arr)
{
    char ***new_str_table = NULL;
    int curr_size = 0;

    if (!str_table_address || !new_str_arr)
        return -1;
    curr_size = get_ptr_arr_size((const void **) *str_table_address);
    new_str_table = malloc(sizeof(char **) * (curr_size + 2));
    for (int i = 0; i < curr_size; i += 1)
        new_str_table[i] = (*str_table_address)[i];
    new_str_table[curr_size] = str_arr_dup(new_str_arr);
    new_str_table[curr_size + 1] = NULL;
    free(*str_table_address);
    *str_table_address = new_str_table;
    return 0;
}
