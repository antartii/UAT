class Pyuat :
    def uat_string_to_table(uat_string):
        uat_table = []
        row_separator = uat_string[0]
        col_separator = uat_string[1]
        reading_a_row = False
        reading_a_col = False
        row_index = 0
        col_index = 0

        for i in range(2, len(uat_string)):
            if uat_string[i] == row_separator and not reading_a_col:
                reading_a_row = not reading_a_row
                if not reading_a_row:
                    row_index += 1
                    col_index = 0
                else : uat_table.append([])
            if uat_string[i] == col_separator and reading_a_row:
                reading_a_col = not reading_a_col
                if not reading_a_col: col_index += 1
                else : uat_table[row_index].append("")
            if reading_a_row and reading_a_col and uat_string[i] != col_separator:
                uat_table[row_index][col_index] += uat_string[i]
        return uat_table
    
    def table_to_uat_string(table, row_separator, col_separator):
        uat_string = row_separator + col_separator

        for row in table:
            uat_string += row_separator
            for cell in row:
                uat_string += col_separator + cell + col_separator
            uat_string += row_separator
        return uat_string