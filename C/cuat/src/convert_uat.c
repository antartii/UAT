/**
 * @file convert_uat.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Diverses functions to convert or parse uat datas
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "cuat.h"

/**
 * @brief Convert a str table into a uat string.
 * 
 * @param table table of string (2D string array) read table[rows][columns]. The last row and last column should be `NULL`.
 * @param row_separator character for the rows separators
 * @param column_separator character for the columns separators
 * @return Returns a malloced string of the uat table or `NULL` if value_table is `NULL` from the start.
 */
char *table_to_uat(const char ***table, const unsigned char row_separator, const unsigned char column_separator)
{
    char *uat_string = NULL;
    int arr_size = 0;

    if (!table)
        return NULL;
    arr_size = get_ptr_arr_size((const void **) table);
    uat_string = char_to_string(row_separator);
    uat_string = strcat_char(uat_string, column_separator);
    for (int i = 0; table[i]; i += 1) {
        uat_string = strcat_char(uat_string, row_separator);
        for (int j = 0; table[i][j]; j += 1) {
            uat_string = strcat_char(uat_string, column_separator);
            uat_string = realloc(uat_string, strlen(uat_string) + strlen(table[i][j]) + 1);
            strcat(uat_string, table[i][j]);
            uat_string = strcat_char(uat_string, column_separator);
        }
        uat_string = strcat_char(uat_string, row_separator);
    }
    return uat_string;
}

/**
 * @brief Split a uat row into cells
 * 
 * @param uat_row string of a row from an uat table.
 * @param column_separator character for the columns separators
 * @return Returns a malloced array of string containing all of the cells from a uat row or `NULL`, if `uat_row` is `NULL` from the start.
 */
char **uat_row_to_cells(const char *uat_row, unsigned char column_separator)
{
    char **uat_cells = NULL;
    int index = 0;
    int cell_count = count_uat_cells_from_row(uat_row, column_separator);
    int is_reading_cell = 0;
    int first_stamp = 0;

    if (!uat_row)
        return NULL;
    uat_cells = malloc(sizeof(char *) * (cell_count + 1));
    uat_cells[cell_count] = NULL;
    for (int i = 0; uat_row[i] != '\0'; i += 1) {
        if (uat_row[i] == column_separator) {
            if (!is_reading_cell)
                first_stamp = i + 1;
            else {
                uat_cells[index] = strndup(uat_row + first_stamp, i - first_stamp);
                index += 1;
            }
            is_reading_cell = !is_reading_cell;
        }
    }
    return uat_cells;
}

/**
 * @brief Split a uat string into an array of string each element representing an uat row.
 * 
 * @param uat_string uat string that will be parsed
 * @return a malloced array of string of the rows from the uat string or `NULL` if uat_string is `NULL`.
 */
char **uat_string_to_rows(const char *uat_string)
{
    char **uat_row = NULL;
    char row_container = '\0';
    char column_separator = '\0';
    int is_reading_row = 0;
    int is_reading_cell = 0;
    int first_stamp = 0;
    int index = 0;

    if (!uat_string)
        return NULL;
    row_container = uat_string[0];
    column_separator = uat_string[1];
    uat_row = malloc(sizeof(char *) * (count_uat_row(uat_string) + 1));
    uat_row[count_uat_row(uat_string)] = NULL;
    for (int i = 2; uat_string[i] != '\0'; i += 1) {
        if (uat_string[i] == row_container && !is_reading_cell) {
            if (!is_reading_row)
                first_stamp = i + 1;
            else {
                uat_row[index] = strndup(uat_string + first_stamp, i - first_stamp);
                index += 1;
            }
            is_reading_row = !is_reading_row;
        }
        if (uat_string[i] == column_separator && is_reading_row)
            is_reading_cell = !is_reading_cell;
    }
    return uat_row;
}

/**
 * @brief Split an uat string into a table of string represented by table[rows][columns]. The last column and the last row is always `NULL`.
 * 
 * @param uat_string uat string that will be parsed
 * @return Returns a malloced table of string of the uat data.
 */
char ***uat_string_to_table(char *uat_string)
{
    char **uat_rows = NULL;
    char ***table = NULL;
    char column_separator = '\0';

    if (!uat_string)
        return NULL;
    uat_rows = uat_string_to_rows(uat_string);
    column_separator = uat_string[1];
    table = malloc(sizeof(char **) * (count_uat_row(uat_string) + 1));
    table[count_uat_row(uat_string)] = NULL;
    for (int i = 0; uat_rows[i] != NULL; i += 1)
        table[i] = uat_row_to_cells(uat_rows[i], column_separator);
    free_ptr_arr((void **) uat_rows);
    return table;
}