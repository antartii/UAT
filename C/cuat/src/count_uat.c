/**
 * @file count_uat.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Functions for counting values inside of uat datas
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "cuat.h"

/**
 * @brief Count the number of cells into a uat row
 * 
 * @param uat_row uat row from a uat table
 * @param column_separator character for the column separator
 * @return Returns an int of the number of cells.
 */
int count_uat_cells_from_row(const char *uat_row, unsigned char column_separator)
{
    int count = 0;
    int is_reading_cell = 0;

    if (!uat_row)
        return 0;
    for (int i = 0; uat_row[i]; i += 1) {
        if (uat_row[i] == column_separator) {
            is_reading_cell = !is_reading_cell;
            count += 1;
        }
    }
    return (int) count / 2;
}

/**
 * @brief Count the number of rows inside of a uat file.
 * 
 * @param uat_string uat string where the rows will be count
 * @return Returns an int of the number of rows inside of the uat string.
 */
int count_uat_row(const char *uat_string)
{
    char row_container = '\0';
    char column_separator = '\0';
    int is_reading_row = 0;
    int is_reading_cell = 0;
    int count = 0;

    if (!uat_string)
        return -1;
    row_container = uat_string[0];
    column_separator = uat_string[1];
    for (int i = 2; uat_string[i] != '\0'; i += 1) {
        if (uat_string[i] == row_container && !is_reading_cell) {
            if (is_reading_row)
                count += 1;
            is_reading_row = !is_reading_row;
        }
        if (uat_string[i] == column_separator && is_reading_row)
            is_reading_cell = !is_reading_cell;
    }
    return count;
}
