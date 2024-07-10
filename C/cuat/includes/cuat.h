/**
 * @file cuat.h
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief header for the uat C library
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CUAT
    #define CUAT

#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// UAT CONVERSION

/**
 * @brief Convert a str table into a uat string.
 * 
 * @param values_table table of string (2D string array) read values_table[rows][columns]. The last row and last column should be `NULL`.
 * @param row_separator character for the rows separators
 * @param column_separator character for the columns separators
 * @return Returns a malloced string of the uat table or `NULL` if value_table is `NULL` from the start.
 */
char *table_to_uat(const char ***values_table, const unsigned char row_separator, const unsigned char column_separator);

/**
 * @brief Split a uat row into cells
 * 
 * @param uat_row string of a row from an uat table.
 * @param column_separator character for the columns separators
 * @return Returns a malloced array of string containing all of the cells from a uat row or `NULL`, if `uat_row` is `NULL` from the start.
 */
char **uat_row_to_cells(const char *uat_row, unsigned char column_separator);

/**
 * @brief Split a uat string into an array of string each element representing an uat row.
 * 
 * @param uat_string uat string that will be parsed
 * @return a malloced array of string of the rows from the uat string or `NULL` if uat_string is `NULL`.
 */
char **uat_string_to_rows(const char *uat_string);

/**
 * @brief Split an uat string into a table of string represented by table[rows][columns]. The last column and the last row is always `NULL`.
 * 
 * @param uat_string uat string that will be parsed
 * @return Returns a malloced table of string of the uat data.
 */
char ***uat_string_to_table(char *uat_string);


// UAT COUNT

/**
 * @brief Count the number of cells into a uat row
 * 
 * @param uat_row uat row from a uat table
 * @param column_separator character for the column separator
 * @return Returns an int of the number of cells.
 */
int count_uat_cells_from_row(const char *uat_row, unsigned char column_separator);

/**
 * @brief Count the number of rows inside of a uat file.
 * 
 * @param uat_string uat string where the rows will be count
 * @return Returns an int of the number of rows inside of the uat string.
 */
int count_uat_row(const char *uat_string);


// OTHER

/**
 * @brief write a string into a file
 * 
 * @param path path of the file
 * @param content content that will be written into the file
 * @param open_type open type of the file (usually "w+")
 * @return Returns 0 if the string has correctly been written, -1 if it encounters an error.
 */
int write_in_file(const char *path, const char *content, const char *open_type);

/**
 * @brief Output the content of a file.
 * 
 * @param file_path path of the file
 * @return Returns a malloced string of the content from the file given, or NULL if it encounters an error.
 */
char *read_file_content(const char *file_path);

/**
 * @brief Get the count of elements inside of an array of pointers.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return returns an int of the count of elements inside of the array
 */
int get_ptr_arr_size(const void **array);

/**
 * @brief free every elements of an array of pointers.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return Returns 0 if the free encounters no errors. -1 if it encounter some.
 */
int free_ptr_arr_content(void **array);

/**
 * @brief Free an array of pointers and the content of it's elements.
 * 
 * @param array array of pointers, should be terminated by a NULL element.
 * @return Returns 0 for no errors, but -1 if it encounters at least one.
 */
int free_ptr_arr(void **array);

/**
 * @brief free a table (2D array) of pointers and the subcontent of it.
 * 
 * @param table table of pointer, the last row and last column should be terminated by a NULL element.
 * @return Returns 0 if it encounters no error but -1 if it encounters at least one.
 */
int free_ptr_table(void ***table);

/**
 * @brief Append an str into an array of str
 * 
 * @param str_arr_address address of the destination
 * @param new_str str appended
 * @return Returns -1 if it encounters an error, but 0 if everything goes well
 */
int append_str_arr(char ***str_arr_address, const char *new_str);

/**
 * @brief duplicate the content of a string array
 * 
 * @param str_arr array of string to duplicate
 * @return Returns a duplicate of the string array
 */
char **str_arr_dup(const char **str_arr);

/**
 * @brief append an array of string to a table of string (2D array)
 * 
 * @param str_table_address address of the table of string
 * @param new_str_arr string array appended
 * @return Returns -1 if it encounters an error but 0 if it encounters none
 */
int append_str_table(char ****str_table_address, const char **new_str_arr);

/**
 * @brief append a char to a string
 * 
 * @param str source string
 * @param c character appended
 * @return Returns the string with the character appended or NULL if str is NULL from the start.
 */
char *strcat_char(char *str, char c);

/**
 * @brief convert a char to a malloced string
 * 
 * @param c character that will be converted
 * @return malloced string of the character, it ends with '\0' terminator.
 */
char *char_to_string(const unsigned char c);

#endif
