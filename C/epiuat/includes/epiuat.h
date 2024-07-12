/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** cuat
*/

#ifndef CUAT
    #define CUAT

    #include <stddef.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <string.h>

// conversions
char *table_to_uat_str(char ***table, char row_separator, char col_separator);
char **uat_rows_from_str(char *uat_str,
    char row_separator, char col_separator);
char **uat_cells_from_row(char *uat_row, char col_separator);
char ***uat_string_to_table(char *uat_str);

// array of pointers
int get_ptr_arr_size(const void **array);
int free_ptr_arr_content(void **array);
int free_ptr_arr(void **array);
int free_ptr_table(void ***table);

// str array
int append_str_arr(char ***str_arr_address, const char *new_str);
char **str_arr_dup(const char **str_arr);

// str table
int append_str_table(char ****str_table_address, const char **new_str_arr);

char *strcat_char(char *str, char c);
char *char_to_string(const unsigned char c);

#endif
