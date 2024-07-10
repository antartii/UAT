/**
 * @file ptr_arr.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Functions for array of pointers handlings
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "cuat.h"

/**
 * @brief Get the count of elements inside of an array of pointers.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return returns an int of the count of elements inside of the array
 */
int get_ptr_arr_size(const void **array)
{
    int count = 0;

    if (!array)
        return 0;
    for (; array[count] != NULL; count += 1);
    return count;
}

/**
 * @brief free every elements of an array of pointers.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return Returns 0 if the free encounters no errors. -1 if it encounter some.
 */
int free_ptr_arr_content(void **array)
{
    if (!array)
        return -1;
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    return 0;
}

/**
 * @brief Free an array of pointers and the content of it's elements.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return Returns 0 for no errors, but -1 if it encounters at least one.
 */
int free_ptr_arr(void **array)
{
    if (!array)
        return -1;
    free_ptr_arr_content(array);
    free(array);
    return 0;
}

/**
 * @brief free a table (2D array) of pointers and the subcontent of it.
 * 
 * @param table table of pointer, the last row and last column should be terminated by a NULL element.
 * @return Returns 0 if it encounters no error but -1 if it encounters at least one.
 */
int free_ptr_table(void ***table)
{
    if (!table)
        return -1;
    for (int i = 0; table[i]; i += 1)
        free_ptr_arr(table[i]);
    free(table);
    return 0;
}
