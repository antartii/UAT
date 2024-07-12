/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** convert_uat
*/

#include "epiuat.h"

char **uat_rows_from_str(char *uat_str, char row_separator, char col_separator)
{
    char **uat_rows = NULL;
    int is_in_cell = 0;
    int stamp = 0;
    char *temp_row = NULL;

    if (!uat_str)
        return NULL;
    for (int i = 2; uat_str[i]; i += 1) {
        if (uat_str[i] == col_separator && stamp)
            is_in_cell = !is_in_cell;
        if (uat_str[i] == row_separator && !is_in_cell && stamp) {
            temp_row = strndup(uat_str + stamp, i - stamp);
            append_str_arr(&uat_rows, temp_row);
            free(temp_row);
            stamp = 0;
        } else if (uat_str[i] == row_separator && !is_in_cell && !stamp) // C1 conditional branching
            stamp = i + 1;
    }
    return uat_rows;
}

char **uat_cells_from_row(char *uat_row, char col_separator)
{
    char **uat_cells = NULL;
    int stamp = 0;
    char *temp_cell = NULL;

    if (!uat_row)
        return NULL;
    for (int i = 0; uat_row[i]; i += 1) {
        if (uat_row[i] == col_separator && stamp) {
            temp_cell = strndup(uat_row + stamp, i - stamp);
            append_str_arr(&uat_cells, temp_cell);
            free(temp_cell);
            stamp = -1;
        }
        if (uat_row[i] == col_separator && !stamp)
            stamp = i + 1;
        if (stamp == -1)
            stamp = 0;
    }
    return uat_cells;
}

char ***uat_string_to_table(char *uat_str)
{
    char ***uat_table = NULL;
    char **uat_rows = NULL;
    char **temp_row = NULL;
    char row_separator = '\0';
    char col_separator = '\0';

    if (!uat_str)
        return NULL;
    row_separator = uat_str[0];
    col_separator = uat_str[1];
    uat_rows = uat_rows_from_str(uat_str, row_separator, col_separator);
    for (int i = 0; uat_rows[i]; i += 1) {
        temp_row = uat_cells_from_row(uat_rows[i], '`');
        append_str_table(&uat_table, temp_row);
        free_ptr_arr(temp_row);
        free(uat_rows[i]);
    }
    free(uat_rows);
    return uat_table;
}

char *table_to_uat_str(char ***table, char row_separator, char col_separator)
{
    char *uat_str = NULL;
    int len_str = 0;

    uat_str = char_to_string(row_separator);
    uat_str = strcat_char(uat_str, col_separator);
    len_str += 2;
    for (int i = 0; table[i]; i += 1) {
        uat_str = strcat_char(uat_str, row_separator);
        len_str += 1;
        for (int j = 0; table[i][j]; j += 1) {
            uat_str = strcat_char(uat_str, col_separator);
            len_str += 2 + strlen(table[i][j]);
            uat_str = realloc(uat_str, len_str);
            strcat(uat_str, table[i][j]);
            uat_str = strcat_char(uat_str, col_separator);
        }
        uat_str = strcat_char(uat_str, row_separator);
        len_str += 1;
    }
    return uat_str;
}
