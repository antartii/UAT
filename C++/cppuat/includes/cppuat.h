#ifndef CPPUAT
    #define CUAT

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Uat {
    public :
        static std::vector<std::string> row_to_cells(std::string uat_row, char col_separator);
        static std::vector<std::string> string_to_row(std::string uat_string);
        static std::vector<std::vector<std::string>> string_to_table(std::string uat_string);
        static std::string table_to_string(std::vector<std::vector<std::string>> table, char row_separator, char col_separator);
};

#endif
