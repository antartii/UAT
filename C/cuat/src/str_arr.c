/**
 * @file str_arr.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Functions for string array handlings
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "cuat.h"

/**
 * @brief Append an str into an array of str
 * 
 * @param str_arr_address address of the destination
 * @param new_str str appended
 * @return Returns -1 if it encounters an error, but 0 if everything goes well
 */
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

/**
 * @brief duplicate the content of a string array
 * 
 * @param str_arr array of string to duplicate
 * @return Returns a duplicate of the string array
 */
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
