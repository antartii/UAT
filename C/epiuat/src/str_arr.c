/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** str_arr
*/

#include "epiuat.h"

int append_str_arr(char ***str_arr_address, const char *new_str)
{
    char **str_arr_copy = NULL;
    int str_arr_size = 0;

    if (!str_arr_address || !new_str)
        return -1;
    str_arr_size = get_ptr_arr_size((const void **) *str_arr_address);
    str_arr_copy = malloc(sizeof(char *) * (str_arr_size + 2));
    for (int i = 0; i < str_arr_size; i += 1)
        str_arr_copy[i] = (*str_arr_address)[i];
    str_arr_copy[str_arr_size] = strdup(new_str);
    str_arr_copy[str_arr_size + 1] = NULL;
    free(*str_arr_address);
    *str_arr_address = str_arr_copy;
    return 0;
}

char **str_arr_dup(const char **str_arr)
{
    char **duplicate = NULL;
    int arr_size = 0;

    if (!str_arr)
        return NULL;
    arr_size = get_ptr_arr_size((const void **) str_arr);
    duplicate = malloc(sizeof(char *) * (arr_size + 1));
    for (int i = 0; i < arr_size; i += 1)
        duplicate[i] = strdup(str_arr[i]);
    duplicate[arr_size] = NULL;
    return duplicate;
}
