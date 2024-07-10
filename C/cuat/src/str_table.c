/**
 * @file str_table.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Functions for string table handlings
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "cuat.h"

/**
 * @brief append an array of string to a table of string (2D array)
 * 
 * @param str_table_address address of the table of string
 * @param new_str_arr string array appended
 * @return Returns -1 if it encounters an error but 0 if it encounters none
 */
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
