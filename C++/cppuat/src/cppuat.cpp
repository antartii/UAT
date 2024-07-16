#include "cppuat.h"

std::vector<std::string> Uat::row_to_cells(std::string uat_row, char col_separator)
{
    std::vector<std::string> uat_cells = {};
    std::string temp_cell = "";
    size_t uat_row_len = 0;
    bool is_reading_cell = false;

    if (uat_row.empty())
        return {};

    for (int i = 0; uat_row[i]; i += 1) {
        if (uat_row[i] == col_separator) {
            is_reading_cell = !is_reading_cell;
            if (!is_reading_cell) {
                uat_cells.push_back(temp_cell);
                temp_cell.clear();
            }
        } else if (is_reading_cell)
            temp_cell += uat_row[i];
    }
    return uat_cells;
}

std::vector<std::string> Uat::string_to_row(std::string uat_string)
{
    std::vector<std::string> uat_rows = {};
    std::string temp_row = "";
    char row_separator = '\0';
    char col_separator = '\0';
    bool is_reading_cell = false;
    bool is_reading_row = false;

    if (uat_string.empty())
        return {};
    row_separator = uat_string[0];
    col_separator = uat_string[1];

    for (int i = 2; uat_string[i]; i += 1) {
        if (uat_string[i] == col_separator && is_reading_row)
            is_reading_cell = !is_reading_cell;
        if (uat_string[i] == row_separator && !is_reading_cell) {
            is_reading_row = !is_reading_row;
            if (!is_reading_row) {
                uat_rows.push_back(temp_row);
                temp_row.clear();
            }
        }
        else if (is_reading_row)
            temp_row += uat_string[i];
    }
    return uat_rows;
}

std::vector<std::vector<std::string>> Uat::string_to_table(std::string uat_string)
{
    char row_separator = '\0';
    char col_separator = '\0';
    std::vector<std::string> uat_rows = {};
    std::vector<std::vector<std::string>> uat_table = {};

    if (uat_string.empty())
        return {};
    row_separator = uat_string[0];
    col_separator = uat_string[1];
    uat_rows = Uat::string_to_row(uat_string);
    for (int i = 0; i < uat_rows.size(); i += 1)
        uat_table.push_back(Uat::row_to_cells(uat_rows[i], col_separator));
    return uat_table;
}

std::string Uat::table_to_string(std::vector<std::vector<std::string>> table, char row_separator, char col_separator)
{
    std::string uat_string = {row_separator, col_separator};

    std::cout << uat_string << std::endl;
    for (int i = 0; i < table.size(); i += 1) {
        uat_string += row_separator;
        for (int j = 0; j < table[i].size(); j += 1)
            uat_string += col_separator + table[i][j] + col_separator;
        uat_string += row_separator;
    }
    return uat_string;
}
